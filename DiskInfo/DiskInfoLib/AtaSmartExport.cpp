#include "pch2.h"
#include "AtaSmart.h"

extern "C" IMPORT_DLL void AtaSmartInit(BOOL useWmi, BOOL advancedDiskSearch, PBOOL flagChangeDisk, BOOL workaroundHD204UI, BOOL workaroundAdataSsd, BOOL flagHideNoSmartDisk)
{
	CString m_Ini = _T("\\DiskInfo.ini");
	// USB/IEEE1394 Support
	SetDebugMode(1);

	INITCOMMONCONTROLSEX InitCtrls = { sizeof(INITCOMMONCONTROLSEX) };
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	SetErrorMode(SEM_FAILCRITICALERRORS);

	CAtaSmart::get_instance().FlagUsbSat = !GetPrivateProfileInt(_T("USB"), _T("SAT"), 1, m_Ini);
	CAtaSmart::get_instance().FlagUsbIodata = !GetPrivateProfileInt(_T("USB"), _T("IODATA"), 1, m_Ini);
	CAtaSmart::get_instance().FlagUsbSunplus = !GetPrivateProfileInt(_T("USB"), _T("Sunplus"), 1, m_Ini);
	CAtaSmart::get_instance().FlagUsbLogitec = !GetPrivateProfileInt(_T("USB"), _T("Logitec"), 1, m_Ini);
	CAtaSmart::get_instance().FlagUsbProlific = !GetPrivateProfileInt(_T("USB"), _T("Prolific"), 1, m_Ini);
	CAtaSmart::get_instance().FlagUsbJmicron = !GetPrivateProfileInt(_T("USB"), _T("JMicron"), 1, m_Ini);
	CAtaSmart::get_instance().FlagUsbCypress = !GetPrivateProfileInt(_T("USB"), _T("Cypress"), 1, m_Ini);
	CAtaSmart::get_instance().FlagUsbASM1352R = !GetPrivateProfileInt(_T("USB"), _T("ASM1352R"), 1, m_Ini);
	CAtaSmart::get_instance().FlagUsbMemory = !GetPrivateProfileInt(_T("USB"), _T("UsbMemory"), 0, m_Ini);
	//	m_Ata.FlagUsbSat16 = !GetPrivateProfileInt(_T("USB"), _T("UsbSAT16"), 1, m_Ini);
	CAtaSmart::get_instance().FlagUsbNVMeJMicron = !GetPrivateProfileInt(_T("USB"), _T("NVMeJMicron"), 1, m_Ini);
	CAtaSmart::get_instance().FlagUsbNVMeASMedia = !GetPrivateProfileInt(_T("USB"), _T("NVMeASMedia"), 1, m_Ini);
	CAtaSmart::get_instance().FlagUsbNVMeRealtek = !GetPrivateProfileInt(_T("USB"), _T("NVMeRealtek"), 1, m_Ini);
	CAtaSmart::get_instance().FlagMegaRAID = !GetPrivateProfileInt(_T("Setting"), _T("MegaRAID"), 1, m_Ini);

	BOOL m_bAtaPassThroughSmart = (BOOL)GetPrivateProfileInt(_T("Setting"), _T("AtaPassThroughSmart"), 1, m_Ini);
	if (m_bAtaPassThroughSmart)
	{
		CAtaSmart::get_instance().SetAtaPassThroughSmart(TRUE);
	}
	else
	{
		CAtaSmart::get_instance().SetAtaPassThroughSmart(FALSE);
	}
	CAtaSmart::get_instance().CsmiType = GetPrivateProfileInt(_T("Setting"), _T("CsmiType"), CAtaSmart::get_instance().CSMI_TYPE_ENABLE_AUTO, m_Ini);
	CAtaSmart::get_instance().Init(useWmi, advancedDiskSearch, flagChangeDisk, workaroundHD204UI, workaroundAdataSsd, flagHideNoSmartDisk);
}
