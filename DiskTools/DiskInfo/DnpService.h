// http://www.dinop.com/vc/service_ctrl.html (ja)

#pragma once

#include <winsvc.h>
#include "atlstr.h"

class	CDnpService
{
	//
	//	���`�ӥ�����ӣ�ֹͣ�å���åɥ��饹
	//
	class CServiceThread
	{
	public:
		CServiceThread()
		{
			_bCancel = false;
		}

	private:

		bool					_bCancel;			//���`�ӥ�����ӣ�ֹͣ�I���ж��É�����true�ʤ��ж��_ʼ
		CComAutoCriticalSection	_secbCancel;		//���`�ӥ�����ӣ�ֹͣ�I���ж��å���ƥ����륻�������

	public:

		//
		//	���`�ӥ�����ӣ�ֹͣ�I���ж����v��
		//
		//	�жϤ��������Ϥ�IsCancel(true,true)���ӳ���
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
		//	���`�ӥ��κ��ץ���ȥ�`��
		//
		//	���Τޤ޺�ӳ����ȥ��`�ӥ�����ӣ�ֹͣ����ޤǟo�ޥ�`�פǴ��C���롣
		//	����å��ФǺ�ӳ�����IsCancel()�����ä��뤳�Ȥǟo�ޥ�`�פ�ꈤ�ʤ�
		//	����ȥ�`�뤬���ܡ�
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

			//���`�ӥ��_ʼҪ��
			DebugPrint(_T("StartService - 1"));
			bRet = ::StartService(hService, NULL, NULL);

			//�_ʼ�ޤǟo�ޥ�`�פǴ��C
			DebugPrint(_T("QueryServiceStatus - 1"));
			int count = 0;
			while (::QueryServiceStatus(hService, &sStatus))
			{
				// �o�ޥ�`�פ�ر� (��� 1 ���g WMI �γ��ڻ������)
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

			// ���`�ӥ�����ӥ�`�ɤ� auto �ˏ��Ɖ��
			ShellExecute(NULL, NULL, _T("sc"), _T("config Winmgmt start= auto"), NULL, SW_HIDE);
			count = 0;
			DebugPrint(_T("QueryServiceStatus - 2"));
			while (::QueryServiceStatus(hService, &sStatus))
			{
				//���`�ӥ��_ʼҪ��
				DebugPrint(_T("StartService - 2"));
				::StartService(hService, NULL, NULL);

				// �o�ޥ�`�פ�ر� (��� 5 ���g WMI �γ��ڻ������)
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
	//	���`�ӥ��κ��ץ���ȥ�`��
	//
	//	���`�ӥ������/ֹͣ����ޤǟo�ޥ�`�פǴ��C���롣
	//
	bool	EasyStartStop(LPCTSTR pszName, bool bStart)
	{
		CServiceThread	cThread;

		return	cThread.EasyStartStop(pszName, bStart);
	}


	//
	//	���`�ӥ��κ������
	//
	//	���`�ӥ�����Ӥ���ޤǟo�ޥ�`�פǴ��C���롣
	//
	bool	EasyStart(LPCTSTR pszName)
	{
		return	EasyStartStop(pszName, true);
	}

	//
	//	���`�ӥ��κ���ֹͣ
	//
	//	���`�ӥ���ֹͣ����ޤǟo�ޥ�`�פǴ��C���롣
	//
	bool	EasyStop(LPCTSTR pszName)
	{
		return	EasyStartStop(pszName, false);
	}


	//
	//	���`�ӥ��κ��������
	//
	//	���`�ӥ�������Ӥ���ޤǟo�ޥ�`�פǴ��C���롣
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
	//	ָ�����륵�`�ӥ����Ӥ��Ƥ��뤫�Υ����å�
	//
	//	false�Έ��Ϥ�"ֹͣ"�Ȥ��ޤ�ʤ������`�ӥ������ڤ��ʤ����Ϥʤɤ�false�Ȥʤ롣
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
		while (1)			//�o�ޥ�`�פǤϤʤ���
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

			break;		//���
		}

		if (hService)
			::CloseServiceHandle(hService);
		if (hManager)
			::CloseServiceHandle(hManager);
		return	ret;
	}
};
