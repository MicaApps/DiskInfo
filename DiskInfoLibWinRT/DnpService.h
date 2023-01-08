// http://www.dinop.com/vc/service_ctrl.html (ja)

#pragma once

#include <winsvc.h>
#include "atlstr.h"

class	CDnpService
{
	//
	//	サービスの起動／停止用スレッドクラス
	//
	class CServiceThread
	{
	public:
		CServiceThread()
		{
			_bCancel = false;
		}

	private:

		bool					_bCancel;			//サービスの起動／停止処理中断用変数、trueなら中断開始
		CComAutoCriticalSection	_secbCancel;		//サービスの起動／停止処理中断用クリティカルセクション

	public:

		//
		//	サービスの起動／停止処理中断用関数
		//
		//	中断したい場合はIsCancel(true,true)を呼び出す
		//
		bool	IsCancel(bool bSave = false, bool bNewValue = false)
		{
			bool	ret;

			_secbCancel.Lock();
			if (bSave)
			{
				_bCancel = bNewValue;
				ret = true;
			}
			else
				ret = _bCancel;
			_secbCancel.Unlock();

			return	ret;
		}



		//
		//	サービスの簡易コントロール
		//
		//	そのまま呼び出すとサービスが起動／停止するまで無限ループで待機する。
		//	スレッド中で呼び出し、IsCancel()を利用することで無限ループに陥らない
		//	コントロールが可能。
		//
		bool EasyStartStop(LPCTSTR pszName, bool b)
		{
			//bool			ret = false;
			BOOL			bRet = FALSE;
			SC_HANDLE		hManager = NULL;
			SC_HANDLE		hService = NULL;
			SERVICE_STATUS	sStatus;

			hManager = ::OpenSCManager(NULL, NULL, GENERIC_EXECUTE);
			if (hManager == NULL)
			{
				return false;
			}

			hService = ::OpenService(hManager, pszName, SERVICE_START | SERVICE_QUERY_STATUS);
			if (hService == NULL)
			{
				if (hManager) { ::CloseServiceHandle(hManager); }
				return false;
			}

			::ZeroMemory(&sStatus, sizeof(SERVICE_STATUS));
			bRet = ::QueryServiceStatus(hService, &sStatus);
			if (bRet == FALSE)
			{
				if (hService) { ::CloseServiceHandle(hService); }
				if (hManager) { ::CloseServiceHandle(hManager); }
				return false;
			}

			if (sStatus.dwCurrentState == SERVICE_RUNNING)
			{
				if (hService) { ::CloseServiceHandle(hService); }
				if (hManager) { ::CloseServiceHandle(hManager); }
				return true;
			}

			CString cstr;
			cstr.Format(_T("sStatus.dwCurrentState:%08X"), sStatus.dwCurrentState);
			DebugPrint(cstr);

			//サービス開始要求
			DebugPrint(_T("StartService - 1"));
			bRet = ::StartService(hService, NULL, NULL);

			//開始まで無限ループで待機
			DebugPrint(_T("QueryServiceStatus - 1"));
			int count = 0;
			while (::QueryServiceStatus(hService, &sStatus))
			{
				// 無限ループを回避 (最大 1 秒間 WMI の初期化を待つ)
				if (count >= 4)
				{
					break;
				}

				if (sStatus.dwCurrentState == SERVICE_RUNNING)
				{
					DebugPrint(_T("StartService Completed : SERVICE_RUNNING"));
					if (hService) { ::CloseServiceHandle(hService); }
					if (hManager) { ::CloseServiceHandle(hManager); }
					return true;
				}

				::Sleep(100 * count);
				DebugPrint(_T("Sleep"));
				count++;
			}

			// サービスの起動モードを auto に強制変更
			ShellExecute(NULL, NULL, _T("sc"), _T("config Winmgmt start= auto"), NULL, SW_HIDE);
			count = 0;
			DebugPrint(_T("QueryServiceStatus - 2"));
			while (::QueryServiceStatus(hService, &sStatus))
			{
				//サービス開始要求
				DebugPrint(_T("StartService - 2"));
				::StartService(hService, NULL, NULL);

				// 無限ループを回避 (最大 5 秒間 WMI の初期化を待つ)
				if (count >= 10)
				{
					break;
				}

				if (sStatus.dwCurrentState == SERVICE_RUNNING)
				{
					DebugPrint(_T("StartService Completed : SERVICE_RUNNING"));
					if (hService) { ::CloseServiceHandle(hService); }
					if (hManager) { ::CloseServiceHandle(hManager); }
					return true;
				}

				::Sleep(500);
				DebugPrint(_T("Sleep"));
				count++;
			}

			if (hService) { ::CloseServiceHandle(hService); }
			if (hManager) { ::CloseServiceHandle(hManager); }
			return false;
		}
	};


public:


	//
	//	サービスの簡易コントロール
	//
	//	サービスが起動/停止するまで無限ループで待機する。
	//
	bool	EasyStartStop(LPCTSTR pszName, bool bStart)
	{
		CServiceThread	cThread;

		return	cThread.EasyStartStop(pszName, bStart);
	}


	//
	//	サービスの簡易起動
	//
	//	サービスが起動するまで無限ループで待機する。
	//
	bool	EasyStart(LPCTSTR pszName)
	{
		return	EasyStartStop(pszName, true);
	}

	//
	//	サービスの簡易停止
	//
	//	サービスが停止するまで無限ループで待機する。
	//
	bool	EasyStop(LPCTSTR pszName)
	{
		return	EasyStartStop(pszName, false);
	}


	//
	//	サービスの簡易再起動
	//
	//	サービスが再起動するまで無限ループで待機する。
	//
	bool	EasyRestart(LPCTSTR pszName)
	{
		bool			ret;
		CServiceThread	cThread;

		ret = cThread.EasyStartStop(pszName, false);
		if (ret)
			ret = cThread.EasyStartStop(pszName, true);

		return	ret;
	}



	//
	//	指定するサービスが動いているかのチェック
	//
	//	falseの場合は"停止"とは限らない。サービスが存在しない場合などもfalseとなる。
	//
	bool	IsServiceRunning(LPCTSTR pszName)
	{
		bool			ret;
		BOOL			bRet;
		SC_HANDLE		hManager;
		SC_HANDLE		hService;
		SERVICE_STATUS	sStatus;

		ret = false;
		hManager = NULL;
		hService = NULL;
		while (1)			//無限ループではない！
		{
			hManager = ::OpenSCManager(NULL, NULL, GENERIC_EXECUTE);
			ATLASSERT(hManager);
			if (hManager == NULL)
				break;

			hService = ::OpenService(hManager, pszName, SERVICE_QUERY_STATUS);
			ATLASSERT(hService);
			if (hService == NULL)
				break;

			::ZeroMemory(&sStatus, sizeof(SERVICE_STATUS));
			bRet = ::QueryServiceStatus(hService, &sStatus);
			ATLASSERT(bRet);
			if (bRet == FALSE)
				break;

			if (sStatus.dwCurrentState == SERVICE_RUNNING)
				ret = true;

			break;		//必須
		}

		if (hService)
			::CloseServiceHandle(hService);
		if (hManager)
			::CloseServiceHandle(hManager);
		return	ret;
	}
};
