// http://www.dinop.com/vc/service_ctrl.html (ja)

#pragma once

#include <winsvc.h>
#include "atlstr.h"

class	CDnpService
{
	//
	//	锟斤拷锟絗锟接ワ拷锟斤拷锟斤拷樱锟酵Ｖ癸拷氓锟斤拷锟矫ドワ拷锟介ス
	//
	class CServiceThread
	{
	public:
		CServiceThread()
		{
			_bCancel = false;
		}

	private:

		bool					_bCancel;			//锟斤拷锟絗锟接ワ拷锟斤拷锟斤拷樱锟酵Ｖ癸拷I锟斤拷锟叫讹拷锟矫夛拷锟斤拷锟斤拷true锟绞わ拷锟叫讹拷锟絖始
		CComAutoCriticalSection	_secbCancel;		//锟斤拷锟絗锟接ワ拷锟斤拷锟斤拷樱锟酵Ｖ癸拷I锟斤拷锟叫讹拷锟矫ワ拷锟斤拷匹锟斤拷锟斤拷毳伙拷锟斤拷锟斤拷锟斤拷

	public:

		//
		//	锟斤拷锟絗锟接ワ拷锟斤拷锟斤拷樱锟酵Ｖ癸拷I锟斤拷锟叫讹拷锟斤拷锟絭锟斤拷
		//
		//	锟叫断わ拷锟斤拷锟斤拷锟斤拷锟较わ拷IsCancel(true,true)锟斤拷锟接筹拷锟斤拷
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
		//	锟斤拷锟絗锟接ワ拷锟轿猴拷锟阶ワ拷锟斤拷去锟絗锟斤拷
		//
		//	锟斤拷锟轿まま猴拷映锟斤拷锟斤拷去锟斤拷`锟接ワ拷锟斤拷锟斤拷樱锟酵Ｖ癸拷锟斤拷锟睫で無锟睫ワ拷`锟阶で达拷锟紺锟斤拷锟诫。
		//	锟斤拷锟斤拷氓锟斤拷肖呛锟接筹拷锟斤拷锟斤拷IsCancel()锟斤拷锟斤拷锟矫わ拷锟诫こ锟饺で無锟睫ワ拷`锟阶わ拷陥わ拷胜锟�
		//	锟斤拷锟斤拷去锟絗锟诫が锟斤拷锟杰★拷
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

			//锟斤拷锟絗锟接ワ拷锟絖始要锟斤拷
			DebugPrint(_T("StartService - 1"));
			bRet = ::StartService(hService, NULL, NULL);

			//锟絖始锟睫で無锟睫ワ拷`锟阶で达拷锟紺
			DebugPrint(_T("QueryServiceStatus - 1"));
			int count = 0;
			while (::QueryServiceStatus(hService, &sStatus))
			{
				// 锟給锟睫ワ拷`锟阶わ拷乇锟� (锟斤拷锟� 1 锟斤拷锟絞 WMI 锟轿筹拷锟节伙拷锟斤拷锟斤拷锟�)
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

			// 锟斤拷锟絗锟接ワ拷锟斤拷锟斤拷鹰锟絗锟缴わ拷 auto 锟剿忥拷锟狡夛拷锟�
			ShellExecute(NULL, NULL, _T("sc"), _T("config Winmgmt start= auto"), NULL, SW_HIDE);
			count = 0;
			DebugPrint(_T("QueryServiceStatus - 2"));
			while (::QueryServiceStatus(hService, &sStatus))
			{
				//锟斤拷锟絗锟接ワ拷锟絖始要锟斤拷
				DebugPrint(_T("StartService - 2"));
				::StartService(hService, NULL, NULL);

				// 锟給锟睫ワ拷`锟阶わ拷乇锟� (锟斤拷锟� 5 锟斤拷锟絞 WMI 锟轿筹拷锟节伙拷锟斤拷锟斤拷锟�)
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
	//	锟斤拷锟絗锟接ワ拷锟轿猴拷锟阶ワ拷锟斤拷去锟絗锟斤拷
	//
	//	锟斤拷锟絗锟接ワ拷锟斤拷锟斤拷锟�/停止锟斤拷锟斤拷蓼菬o锟睫ワ拷`锟阶で达拷锟紺锟斤拷锟诫。
	//
	bool	EasyStartStop(LPCTSTR pszName, bool bStart)
	{
		CServiceThread	cThread;

		return	cThread.EasyStartStop(pszName, bStart);
	}


	//
	//	锟斤拷锟絗锟接ワ拷锟轿猴拷锟斤拷锟斤拷锟�
	//
	//	锟斤拷锟絗锟接ワ拷锟斤拷锟斤拷婴锟斤拷锟睫で無锟睫ワ拷`锟阶で达拷锟紺锟斤拷锟诫。
	//
	bool	EasyStart(LPCTSTR pszName)
	{
		return	EasyStartStop(pszName, true);
	}

	//
	//	锟斤拷锟絗锟接ワ拷锟轿猴拷锟斤拷停止
	//
	//	锟斤拷锟絗锟接ワ拷锟斤拷停止锟斤拷锟斤拷蓼菬o锟睫ワ拷`锟阶で达拷锟紺锟斤拷锟诫。
	//
	bool	EasyStop(LPCTSTR pszName)
	{
		return	EasyStartStop(pszName, false);
	}


	//
	//	锟斤拷锟絗锟接ワ拷锟轿猴拷锟斤拷锟斤拷锟斤拷锟�
	//
	//	锟斤拷锟絗锟接ワ拷锟斤拷锟斤拷锟斤拷婴锟斤拷锟睫で無锟睫ワ拷`锟阶で达拷锟紺锟斤拷锟诫。
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
	//	指锟斤拷锟斤拷锟诫サ锟絗锟接ワ拷锟斤拷锟接わ拷锟狡わ拷锟诫か锟轿ワ拷锟斤拷锟矫ワ拷
	//
	//	false锟轿堬拷锟较わ拷"停止"锟饺わ拷锟睫わ拷胜锟斤拷锟斤拷锟斤拷`锟接ワ拷锟斤拷锟斤拷锟节わ拷锟绞わ拷锟斤拷锟较などわ拷false锟饺なる。
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
		while (1)			//锟給锟睫ワ拷`锟阶ではなわ拷锟斤拷
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

			break;		//锟斤拷锟�
		}

		if (hService)
			::CloseServiceHandle(hService);
		if (hManager)
			::CloseServiceHandle(hManager);
		return	ret;
	}
};
