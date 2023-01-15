#include "pch2.h"
#include "AtaSmart.h"
static DWORD selectedDrive;
	extern "C" IMPORT_DLL int Add(int a, int b)
	{
		return a + b;
	}

	extern "C" IMPORT_DLL BOOL SelectDrive(DWORD i)
	{
		if (i >= (DWORD)CAtaSmart::get_instance().vars.GetCount())
		{
			return FALSE;
		}

		//CWaitCursor wait;
		static int preFlagFahrenheit = -1;

		switch (CAtaSmart::get_instance().UpdateSmartInfo(i))
		{
		case CAtaSmart::SMART_STATUS_MAJOR_CHANGE:
		case CAtaSmart::SMART_STATUS_MINOR_CHANGE:
			//SaveSmartInfo(i);
			//AlertSound(0, AS_PLAY_SOUND);
			//UpdateShareInfo();
			break;
		default:
			//if (m_SelectDisk == i)
			//{
			//	if (preFlagFahrenheit == m_bFahrenheit)
			//	{
			//		//	return ;
			//	}
			//	else
			//	{
			//		preFlagFahrenheit = m_bFahrenheit;
			//	}
			//}
			break;
		}
		selectedDrive = i;
		return TRUE;
	}

	extern "C" IMPORT_DLL DWORD GetSelectedDrive()
	{
		DWORD i = selectedDrive;
		return i;
	}

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
		SelectDrive(0);
	}

	extern "C" IMPORT_DLL int GetDriveNum() { return (int)CAtaSmart::get_instance().vars.GetCount(); }

	extern "C" IMPORT_DLL wchar_t* GetFirmware() {
		auto& instance = CAtaSmart::get_instance();
		CString cstrStr = CAtaSmart::get_instance().vars[selectedDrive].FirmwareRev;
		return cstrStr.AllocSysString();
	}

	extern "C" IMPORT_DLL wchar_t* GetModel() {
		CString cstrStr = CAtaSmart::get_instance().vars[selectedDrive].Model;	//Ӳ������
		return cstrStr.AllocSysString();
	}

	extern "C" IMPORT_DLL wchar_t* GetSerialNumber() {
		CString cstrStr = CAtaSmart::get_instance().vars[selectedDrive].SerialNumber;
		return cstrStr.AllocSysString();
	}

	extern "C" IMPORT_DLL wchar_t* GetFirmwareRev() {
		CString cstrStr = CAtaSmart::get_instance().vars[selectedDrive].FirmwareRev;
		return cstrStr.AllocSysString();
	}

	extern "C" IMPORT_DLL wchar_t* GetBufferSize() {
		CString m_BufferSize;
		if (CAtaSmart::get_instance().vars[selectedDrive].HostReads >= 0)
		{
			m_BufferSize.Format(_T("%d GB"), CAtaSmart::get_instance().vars[selectedDrive].HostReads);
		}
		else if (CAtaSmart::get_instance().vars[selectedDrive].BufferSize == 0xFFFF * 512)
		{
			m_BufferSize.Format(_T(">= 32 MB"));
		}
		else if (CAtaSmart::get_instance().vars[selectedDrive].BufferSize > 0)
		{
			m_BufferSize.Format(_T("%d KB"), CAtaSmart::get_instance().vars[selectedDrive].BufferSize / 1024);
		}
		else
		{
			m_BufferSize = _T("----");
		}
		return m_BufferSize.AllocSysString();
	}

	extern "C" IMPORT_DLL wchar_t* GetNvCacheSize() {
		CString m_NvCacheSize;
		if (CAtaSmart::get_instance().vars[selectedDrive].HostWrites >= 0)
		{
			m_NvCacheSize.Format(_T("%d GB"), CAtaSmart::get_instance().vars[selectedDrive].HostWrites);
		}
		else if (CAtaSmart::get_instance().vars[selectedDrive].NvCacheSize > 0)
		{
			m_NvCacheSize.Format(_T("%d MB"), (DWORD)(CAtaSmart::get_instance().vars[selectedDrive].NvCacheSize / 1024 / 1024));
		}
		else
		{
			m_NvCacheSize = _T("----");
		}
		return m_NvCacheSize.AllocSysString();
	}

	extern "C" IMPORT_DLL wchar_t* GetRotationRate() {
		CString m_RotationRate;
		if (CAtaSmart::get_instance().vars[selectedDrive].NandWrites >= 0)
		{
			m_RotationRate.Format(_T("%d GB"), CAtaSmart::get_instance().vars[selectedDrive].NandWrites);
		}
		else if (CAtaSmart::get_instance().vars[selectedDrive].GBytesErased >= 0)
		{
			m_RotationRate.Format(_T("%d GB"), CAtaSmart::get_instance().vars[selectedDrive].GBytesErased);
		}
		else if (CAtaSmart::get_instance().vars[selectedDrive].NominalMediaRotationRate == 1) // SSD
		{
			m_RotationRate = _T("---- (SSD)");
		}
		else if (CAtaSmart::get_instance().vars[selectedDrive].NominalMediaRotationRate > 0)
		{
			m_RotationRate.Format(_T("%d RPM"), CAtaSmart::get_instance().vars[selectedDrive].NominalMediaRotationRate);
		}
		else
		{
			m_RotationRate = _T("----");
		}
		return m_RotationRate.AllocSysString();
	}

	extern "C" IMPORT_DLL wchar_t* GetLbaSize() {
		CString m_LbaSize;
		if (CAtaSmart::get_instance().vars[selectedDrive].DiskSizeLba48 >= CAtaSmart::get_instance().vars[selectedDrive].DiskSizeLba28)
		{
			m_LbaSize.Format(_T("%.1f GB"), CAtaSmart::get_instance().vars[selectedDrive].DiskSizeLba48 / 1000.0);
		}
		else if (CAtaSmart::get_instance().vars[selectedDrive].DiskSizeLba28 > 0)
		{
			m_LbaSize.Format(_T("%.1f GB"), CAtaSmart::get_instance().vars[selectedDrive].DiskSizeLba28 / 1000.0);
		}
		else if (CAtaSmart::get_instance().vars[selectedDrive].DiskSizeChs > 0)
		{
			m_LbaSize.Format(_T("%.1f GB"), CAtaSmart::get_instance().vars[selectedDrive].DiskSizeChs / 1000.0);
		}
		else
		{
			m_LbaSize = _T("----");
		}
		return m_LbaSize.AllocSysString();
	}


	extern "C" IMPORT_DLL wchar_t* GetTransferMode() {
		CString m_TransferMode;
		if (CAtaSmart::get_instance().vars[selectedDrive].CurrentTransferMode.IsEmpty() && CAtaSmart::get_instance().vars[selectedDrive].MaxTransferMode.IsEmpty())
		{
			m_TransferMode = L"";
		}
		else
		{
			m_TransferMode = CAtaSmart::get_instance().vars[selectedDrive].CurrentTransferMode + _T(" | ") + CAtaSmart::get_instance().vars[selectedDrive].MaxTransferMode;
		}
		return m_TransferMode.AllocSysString();
	}

	extern "C" IMPORT_DLL wchar_t* GetInterface() {
		CString cstrStr = CAtaSmart::get_instance().vars[selectedDrive].Interface;;
		return cstrStr.AllocSysString();
	}

	extern "C" IMPORT_DLL wchar_t* GetAtaAtapi() {
		CString m_AtaAtapi;
		if (!CAtaSmart::get_instance().vars[selectedDrive].MinorVersion.IsEmpty())
		{
			m_AtaAtapi = CAtaSmart::get_instance().vars[selectedDrive].MajorVersion + _T(" | ") + CAtaSmart::get_instance().vars[selectedDrive].MinorVersion;
		}
		else
		{
			m_AtaAtapi = CAtaSmart::get_instance().vars[selectedDrive].MajorVersion;
		}
		return m_AtaAtapi.AllocSysString();
	}

	extern "C" IMPORT_DLL wchar_t* GetFeature() {
		CString m_Feature;
		if (CAtaSmart::get_instance().vars[selectedDrive].IsSmartSupported)
		{
			m_Feature += _T("S.M.A.R.T., ");
		}

		if (CAtaSmart::get_instance().vars[selectedDrive].IsApmSupported)
		{
			m_Feature += _T("APM, ");
		}

		if (CAtaSmart::get_instance().vars[selectedDrive].IsAamSupported)
		{
			m_Feature += _T("AAM, ");
		}

		if (CAtaSmart::get_instance().vars[selectedDrive].IsNcqSupported)
		{
			m_Feature += _T("NCQ, ");
		}

		if (CAtaSmart::get_instance().vars[selectedDrive].IsTrimSupported)
		{
			m_Feature += _T("TRIM, ");
		}

		if (CAtaSmart::get_instance().vars[selectedDrive].IsDeviceSleepSupported)
		{
			m_Feature += _T("DevSleep, ");
		}

		if (CAtaSmart::get_instance().vars[selectedDrive].IsStreamingSupported)
		{
			m_Feature += _T("Streaming, ");
		}

		if (CAtaSmart::get_instance().vars[selectedDrive].IsGplSupported)
		{
			m_Feature += _T("GPL, ");
		}

		if (CAtaSmart::get_instance().vars[selectedDrive].IsVolatileWriteCachePresent)
		{
			m_Feature += _T("VolatileWriteCache, ");
		}
		if (!m_Feature.IsEmpty())
		{
			m_Feature.Delete(m_Feature.GetLength() - 2, 2);
		}

		if (CAtaSmart::get_instance().vars[selectedDrive].CommandType == CAtaSmart::get_instance().CMD_TYPE_AMD_RC2)
		{
			m_Feature = L"";
		}
		return m_Feature.AllocSysString();
	}

	extern "C" IMPORT_DLL wchar_t* GetDriveMap() {
		CString m_DriveMap = CAtaSmart::get_instance().vars[selectedDrive].DriveMap;
		return m_DriveMap.AllocSysString();
	}

	extern "C" IMPORT_DLL wchar_t* GetListInfo() {
		CString AllListInfo = _T("");
		CString cstr;
		CString m_Ini = _T("\\DiskInfo.ini");
		DWORD m_RawValues = GetPrivateProfileInt(_T("Setting"), _T("RawValues"), 0, m_Ini);
		BOOL m_bGreenMode = (BOOL)GetPrivateProfileInt(_T("Setting"), _T("GreenMode"), 0, m_Ini);
		DWORD caution = 0;

		for (DWORD j = 0; j < CAtaSmart::get_instance().vars[selectedDrive].AttributeCount; j++)
		{
			if (CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id == 0x00 || CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id == 0xFF)
			{
				continue;
			}

			if (CAtaSmart::get_instance().vars[selectedDrive].IsNVMe)
			{
				UINT icon = ICON_GOOD + m_bGreenMode;

				if (CAtaSmart::get_instance().vars[selectedDrive].Model.Find(_T("Parallels")) == 0
					|| CAtaSmart::get_instance().vars[selectedDrive].Model.Find(_T("VMware")) == 0
					|| CAtaSmart::get_instance().vars[selectedDrive].Model.Find(_T("QEMU")) == 0
					)
				{
					icon = ICON_UNKNOWN;
				}
				else if (CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id == 0x01 && CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[0])
				{
					icon = ICON_BAD;
				}
				else if (CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id == 0x02)
				{
					if ((MAKEWORD(CAtaSmart::get_instance().vars[selectedDrive].Attribute[1].RawValue[0], CAtaSmart::get_instance().vars[selectedDrive].Attribute[1].RawValue[1]) - 273) >= CAtaSmart::get_instance().vars[selectedDrive].AlarmTemperature)
					{
						icon = ICON_BAD;
					}
					else if ((MAKEWORD(CAtaSmart::get_instance().vars[selectedDrive].Attribute[1].RawValue[0], CAtaSmart::get_instance().vars[selectedDrive].Attribute[1].RawValue[1]) - 273) == CAtaSmart::get_instance().vars[selectedDrive].AlarmTemperature)
					{
						icon = ICON_CAUTION;
					}
				}
				// 2022/10/02 Workaround for no support Available Spare Threshold devices
				// https://github.com/hiyohiyo/CrystalDiskInfo/issues/186
				else if (CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id == 0x03 && CAtaSmart::get_instance().vars[selectedDrive].Attribute[3].RawValue[0] > 100)
				{
					icon = ICON_GOOD;
				}
				// 2022/03/26 Workaround for WD_BLACK AN1500 (No support Available Spare/Available Spare Threshold)
				else if (CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id == 0x03 && (CAtaSmart::get_instance().vars[selectedDrive].Attribute[2].RawValue[0] == 0 && CAtaSmart::get_instance().vars[selectedDrive].Attribute[3].RawValue[0] == 0))
				{
					icon = ICON_GOOD;
				}
				else if (CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id == 0x03 && (CAtaSmart::get_instance().vars[selectedDrive].Attribute[2].RawValue[0] < CAtaSmart::get_instance().vars[selectedDrive].Attribute[3].RawValue[0]))
				{
					icon = ICON_BAD;
				}
				else if (CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id == 0x03 && (CAtaSmart::get_instance().vars[selectedDrive].Attribute[2].RawValue[0] == CAtaSmart::get_instance().vars[selectedDrive].Attribute[3].RawValue[0] && CAtaSmart::get_instance().vars[selectedDrive].Attribute[3].RawValue[0] != 100))
				{
					icon = ICON_CAUTION;
				}
				else if (CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id == 0x05 && ((100 - CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[0]) <= CAtaSmart::get_instance().vars[selectedDrive].ThresholdFF))
				{
					icon = ICON_CAUTION;
				}

				/*if (flag)
				{
					m_List.SetItem(k, 0, mask, _T(""), icon, 0, 0, 0, 0);
				}
				else
				{
					m_List.InsertItem(k, _T(""), icon);
				}*/
				cstr.Format(_T("%d"), icon);
				AllListInfo += cstr + _T(" ");
			}
			else if (CAtaSmart::get_instance().vars[selectedDrive].IsSmartCorrect && CAtaSmart::get_instance().vars[selectedDrive].IsThresholdCorrect && !CAtaSmart::get_instance().vars[selectedDrive].IsThresholdBug)
			{
				if (!CAtaSmart::get_instance().vars[selectedDrive].IsSsd &&
					(CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id == 0x05 // Reallocated Sectors Count
						|| CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id == 0xC5 // Current Pending Sector Count
						|| CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id == 0xC6 // Off-Line Scan Uncorrectable Sector Count
						))
				{
					WORD raw = MAKEWORD(CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[0], CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[1]);
					WORD threshold = 0;
					switch (CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id)
					{
					case 0x05:
						threshold = CAtaSmart::get_instance().vars[selectedDrive].Threshold05;
						break;
					case 0xC5:
						threshold = CAtaSmart::get_instance().vars[selectedDrive].ThresholdC5;
						break;
					case 0xC6:
						threshold = CAtaSmart::get_instance().vars[selectedDrive].ThresholdC6;
						break;
					}
					if (threshold > 0 && raw >= threshold)
					{
						caution = 1;
					}
					else
					{
						caution = 0;
					}

					if (CAtaSmart::get_instance().vars[selectedDrive].Threshold[j].ThresholdValue != 0
						&& CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].CurrentValue < CAtaSmart::get_instance().vars[selectedDrive].Threshold[j].ThresholdValue)
					{
						/*if (flag)
						{
							m_List.SetItem(k, 0, mask, _T(""), ICON_BAD, 0, 0, 0, 0);
						}
						else
						{
							m_List.InsertItem(k, _T(""), ICON_BAD);
						}*/
						cstr.Format(_T("%d"), ICON_BAD);
						AllListInfo += cstr + _T(" ");
					}
					else if (caution > 0)
					{
						/*if (flag)
						{
							m_List.SetItem(k, 0, mask, _T(""), ICON_CAUTION, 0, 0, 0, 0);
						}
						else
						{
							m_List.InsertItem(k, _T(""), ICON_CAUTION);
						}*/
						cstr.Format(_T("%d"), ICON_CAUTION);
						AllListInfo += cstr + _T(" ");
					}
					else
					{
						/*if (flag)
						{
							m_List.SetItem(k, 0, mask, _T(""), ICON_GOOD + m_bGreenMode, 0, 0, 0, 0);
						}
						else
						{
							m_List.InsertItem(k, _T(""), ICON_GOOD + m_bGreenMode);
						}*/
						cstr.Format(_T("%d"), ICON_GOOD + m_bGreenMode);
						AllListInfo += cstr + _T(" ");
					}
				}
				// [2021/12/15] Workaround for SanDisk USB Memory
				else if (CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id == 0xE8 && CAtaSmart::get_instance().vars[selectedDrive].FlagLifeSanDiskUsbMemory)
				{
					/*if (flag)
					{
						m_List.SetItem(k, 0, mask, _T(""), ICON_GOOD + m_bGreenMode, 0, 0, 0, 0);
					}
					else
					{
						m_List.InsertItem(k, _T(""), ICON_GOOD + m_bGreenMode);
					}*/
					cstr.Format(_T("%d"), ICON_GOOD + m_bGreenMode);
					AllListInfo += cstr + _T(" ");
				}
				// Temperature
				else if (CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id == 0xC2)
				{
					/*if (flag)
					{
						m_List.SetItem(k, 0, mask, _T(""), ICON_GOOD + m_bGreenMode, 0, 0, 0, 0);
					}
					else
					{
						m_List.InsertItem(k, _T(""), ICON_GOOD + m_bGreenMode);
					}*/
					cstr.Format(_T("%d"), ICON_GOOD + m_bGreenMode);
					AllListInfo += cstr + _T(" ");
				}
				// End-to-End Error
				// https://crystalmark.info/bbs/c-board.cgi?cmd=one;no=1090;id=diskinfo#1090
				// http://h20000.www2.hp.com/bc/docs/support/SupportManual/c01159621/c01159621.pdf
				else if (CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id == 0xB8)
				{
					/*if (flag)
					{
						m_List.SetItem(k, 0, mask, _T(""), ICON_GOOD + m_bGreenMode, 0, 0, 0, 0);
					}
					else
					{
						m_List.InsertItem(k, _T(""), ICON_GOOD + m_bGreenMode);
					}*/
					cstr.Format(_T("%d"), ICON_GOOD + m_bGreenMode);
					AllListInfo += cstr + _T(" ");
				}
				// Life for WDC/SanDisk
				else if (CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id == 0xE6 && (CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_WDC || CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_SANDISK))
				{
					int life = -1;

					if (CAtaSmart::get_instance().vars[selectedDrive].FlagLifeSanDiskUsbMemory)
					{
						life = -1;
					}
					else if (CAtaSmart::get_instance().vars[selectedDrive].FlagLifeSanDisk0_1)
					{
						life = 100 - (CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[1] * 256 + CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[0]) / 100;
					}
					else if (CAtaSmart::get_instance().vars[selectedDrive].FlagLifeSanDisk1)
					{
						life = 100 - CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[1];
					}
					else if (CAtaSmart::get_instance().vars[selectedDrive].FlagLifeSanDiskLenovo)
					{
						life = CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].CurrentValue;
					}
					else
					{
						life = 100 - CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[1];
					}

					if (life <= 0) { life = 0; }

					if (CAtaSmart::get_instance().vars[selectedDrive].FlagLifeSanDiskUsbMemory)
					{
						/*if (flag)
						{
							m_List.SetItem(k, 0, mask, _T(""), ICON_GOOD + m_bGreenMode, 0, 0, 0, 0);
						}
						else
						{
							m_List.InsertItem(k, _T(""), ICON_GOOD + m_bGreenMode);
						}*/
						cstr.Format(_T("%d"), ICON_GOOD + m_bGreenMode);
						AllListInfo += cstr + _T(" ");
					}
					else if (life == 0)
					{
						/*if (flag)
						{
							m_List.SetItem(k, 0, mask, _T(""), ICON_BAD, 0, 0, 0, 0);
						}
						else
						{
							m_List.InsertItem(k, _T(""), ICON_BAD);
						}*/
						cstr.Format(_T("%d"), ICON_BAD);
						AllListInfo += cstr + _T(" ");
					}
					else if (life <= CAtaSmart::get_instance().vars[selectedDrive].ThresholdFF)
					{
						/*if (flag)
						{
							m_List.SetItem(k, 0, mask, _T(""), ICON_CAUTION, 0, 0, 0, 0);
						}
						else
						{
							m_List.InsertItem(k, _T(""), ICON_CAUTION);
						}*/
						cstr.Format(_T("%d"), ICON_CAUTION);
						AllListInfo += cstr + _T(" ");
					}
					else
					{
						/*if (flag)
						{
							m_List.SetItem(k, 0, mask, _T(""), ICON_GOOD + m_bGreenMode, 0, 0, 0, 0);
						}
						else
						{
							m_List.InsertItem(k, _T(""), ICON_GOOD + m_bGreenMode);
						}*/
						cstr.Format(_T("%d"), ICON_GOOD + m_bGreenMode);
						AllListInfo += cstr + _T(" ");
					}
				}
				// Life
				else if (
					(CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id == 0xA9 && (CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_REALTEK || (CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_KINGSTON && CAtaSmart::get_instance().vars[selectedDrive].HostReadsWritesUnit == CAtaSmart::get_instance().HOST_READS_WRITES_32MB) || CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_SILICONMOTION))
					|| (CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id == 0xAD && (CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_TOSHIBA || CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_KIOXIA))
					|| (CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id == 0xB1 && CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_SAMSUNG)
					|| (CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id == 0xBB && CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_MTRON)
					|| (CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id == 0xCA && (CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_MICRON || CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_MICRON_MU03 || CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_INTEL_DC))
					|| (CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id == 0xD1 && CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_INDILINX)
					|| (CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id == 0xE7 && (CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_SANDFORCE || CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_CORSAIR || CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_KINGSTON || CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_SKHYNIX
						|| CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_REALTEK || CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_SANDISK || CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_SSSTC || CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_APACER
						|| CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_JMICRON || CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_SEAGATE || CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_MAXIOTEK
						|| CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_YMTC || CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_SCY || CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_RECADATA))
					|| (CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id == 0xE8 && CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_PLEXTOR)
					|| (CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id == 0xE9 && (CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_INTEL || CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_OCZ || CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_OCZ_VECTOR || CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_SKHYNIX))
					|| (CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id == 0xE9 && CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_SANDISK_LENOVO_HELEN_VENUS)
					|| (CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id == 0xE6 && (CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_SANDISK_LENOVO || CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_SANDISK_DELL))
					|| (CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id == 0xC9 && (CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_SANDISK_HP || CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_SANDISK_HP_VENUS))

					)
				{
					if (CAtaSmart::get_instance().vars[selectedDrive].FlagLifeRawValue || CAtaSmart::get_instance().vars[selectedDrive].FlagLifeRawValueIncrement)
					{
						/*if (flag)
						{
							m_List.SetItem(k, 0, mask, _T(""), ICON_GOOD + m_bGreenMode, 0, 0, 0, 0);
						}
						else
						{
							m_List.InsertItem(k, _T(""), ICON_GOOD + m_bGreenMode);
						}*/
						cstr.Format(_T("%d"), ICON_GOOD + m_bGreenMode);
						AllListInfo += cstr + _T(" ");
					}
					else if (CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].CurrentValue == 0
						|| CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].CurrentValue < CAtaSmart::get_instance().vars[selectedDrive].Threshold[j].ThresholdValue)
					{
						/*if (flag)
						{
							m_List.SetItem(k, 0, mask, _T(""), ICON_BAD, 0, 0, 0, 0);
						}
						else
						{
							m_List.InsertItem(k, _T(""), ICON_BAD);
						}*/
						cstr.Format(_T("%d"), ICON_BAD);
						AllListInfo += cstr + _T(" ");
					}
					else if (CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].CurrentValue <= CAtaSmart::get_instance().vars[selectedDrive].ThresholdFF)
					{
						/*if (flag)
						{
							m_List.SetItem(k, 0, mask, _T(""), ICON_CAUTION, 0, 0, 0, 0);
						}
						else
						{
							m_List.InsertItem(k, _T(""), ICON_CAUTION);
						}*/
						cstr.Format(_T("%d"), ICON_CAUTION);
						AllListInfo += cstr + _T(" ");
					}
					else
					{
						/*if (flag)
						{
							m_List.SetItem(k, 0, mask, _T(""), ICON_GOOD + m_bGreenMode, 0, 0, 0, 0);
						}
						else
						{
							m_List.InsertItem(k, _T(""), ICON_GOOD + m_bGreenMode);
						}*/
						cstr.Format(_T("%d"), ICON_GOOD + m_bGreenMode);
						AllListInfo += cstr + _T(" ");
					}
				}
				else if (CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id == 0x01 // Read Error Rate for SandForce Bug
					&& CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_SANDFORCE)
				{
					if (CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].CurrentValue == 0
						&& CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[0] == 0
						&& CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[1] == 0)
					{
						/*if (flag)
						{
							m_List.SetItem(k, 0, mask, _T(""), ICON_GOOD + m_bGreenMode, 0, 0, 0, 0);
						}
						else
						{
							m_List.InsertItem(k, _T(""), ICON_GOOD + m_bGreenMode);
						}*/
						cstr.Format(_T("%d"), ICON_GOOD + m_bGreenMode);
						AllListInfo += cstr + _T(" ");
					}
					else if (CAtaSmart::get_instance().vars[selectedDrive].Threshold[j].ThresholdValue != 0
						&& CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].CurrentValue < CAtaSmart::get_instance().vars[selectedDrive].Threshold[j].ThresholdValue)
					{
						/*if (flag)
						{
							m_List.SetItem(k, 0, mask, _T(""), ICON_BAD, 0, 0, 0, 0);
						}
						else
						{
							m_List.InsertItem(k, _T(""), ICON_BAD);
						}*/
						cstr.Format(_T("%d"), ICON_BAD);
						AllListInfo += cstr + _T(" ");
					}
					else
					{
						/*if (flag)
						{
							m_List.SetItem(k, 0, mask, _T(""), ICON_GOOD + m_bGreenMode, 0, 0, 0, 0);
						}
						else
						{
							m_List.InsertItem(k, _T(""), ICON_GOOD + m_bGreenMode);
						}*/
						cstr.Format(_T("%d"), ICON_GOOD + m_bGreenMode);
						AllListInfo += cstr + _T(" ");
					}
				}
				else if ((CAtaSmart::get_instance().vars[selectedDrive].IsSsd && !CAtaSmart::get_instance().vars[selectedDrive].IsRawValues8)
					|| ((0x01 <= CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id && CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id <= 0x0D)
						|| CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id == 0x16
						|| (0xBB <= CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id && CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id <= 0xC1)
						|| (0xC3 <= CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id && CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id <= 0xD1)
						|| (0xD3 <= CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id && CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id <= 0xD4)
						|| (0xDC <= CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id && CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id <= 0xE4)
						|| (0xE6 <= CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id && CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id <= 0xE7)
						|| CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id == 0xF0
						|| CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id == 0xFA
						|| CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id == 0xFE
						))
				{
					if (CAtaSmart::get_instance().vars[selectedDrive].Threshold[j].ThresholdValue != 0
						&& CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].CurrentValue < CAtaSmart::get_instance().vars[selectedDrive].Threshold[j].ThresholdValue)
					{
						/*if (flag)
						{
							m_List.SetItem(k, 0, mask, _T(""), ICON_BAD, 0, 0, 0, 0);
						}
						else
						{
							m_List.InsertItem(k, _T(""), ICON_BAD);
						}*/
						cstr.Format(_T("%d"), ICON_BAD);
						AllListInfo += cstr + _T(" ");
					}
					else
					{
						/*if (flag)
						{
							m_List.SetItem(k, 0, mask, _T(""), ICON_GOOD + m_bGreenMode, 0, 0, 0, 0);
						}
						else
						{
							m_List.InsertItem(k, _T(""), ICON_GOOD + m_bGreenMode);
						}*/
						cstr.Format(_T("%d"), ICON_GOOD + m_bGreenMode);
						AllListInfo += cstr + _T(" ");
					}
				}
				else
				{
					/*if (flag)
					{
						m_List.SetItem(k, 0, mask, _T(""), ICON_GOOD + m_bGreenMode, 0, 0, 0, 0);
					}
					else
					{
						m_List.InsertItem(k, _T(""), ICON_GOOD + m_bGreenMode);
					}*/
					cstr.Format(_T("%d"), ICON_GOOD + m_bGreenMode);
					AllListInfo += cstr + _T(" ");
				}
			}
			else
			{
				/*if (flag)
				{
					m_List.SetItem(k, 0, mask, _T(""), ICON_UNKNOWN, 0, 0, 0, 0);
				}
				else
				{
					m_List.InsertItem(k, _T(""), ICON_UNKNOWN);
				}*/
				cstr.Format(_T("%d"), ICON_UNKNOWN);
				AllListInfo += cstr + _T(" ");
			}

			cstr.Format(_T("%02X"), CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id);
			//m_List.SetItemText(k, 1, cstr);
			AllListInfo += cstr + _T(" ");
			//BYTE id = CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Id;

			/*if (m_bSmartEnglish)	//�����
			{
				GetPrivateProfileStringFx(CAtaSmart::get_instance().vars[selectedDrive].SmartKeyName, cstr, vendorSpecific, str, 256, m_DefaultLangPath);
			}
			else
			{
				GetPrivateProfileStringFx(CAtaSmart::get_instance().vars[selectedDrive].SmartKeyName, cstr, L"", str, 256, m_DefaultLangPath);
				CString en = str;
				if (en.IsEmpty())
				{
					GetPrivateProfileStringFx(CAtaSmart::get_instance().vars[selectedDrive].SmartKeyName, cstr, vendorSpecific, str, 256, m_CurrentLangPath);
				}
				else
				{
					GetPrivateProfileStringFx(CAtaSmart::get_instance().vars[selectedDrive].SmartKeyName, cstr, en, str, 256, m_CurrentLangPath);
				}
			}*/

			//m_List.SetItemText(k, 2, str);
			//AllListInfo += CAtaSmart::get_instance().vars[selectedDrive].SmartKeyName + _T(" ");

			if (CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_SANDFORCE)
			{
				cstr.Format(_T("%d"), CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].CurrentValue);
				cstr.Format(_T("%d"), CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].CurrentValue);
				//m_List.SetItemText(k, 3, cstr);
				AllListInfo.Append(cstr + _T(" "));
				cstr.Format(_T("%d"), CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].WorstValue);
				//m_List.SetItemText(k, 4, cstr);
				AllListInfo.Append(cstr + _T(" "));
				if (CAtaSmart::get_instance().vars[selectedDrive].IsThresholdCorrect)
				{
					cstr.Format(_T("%d"), CAtaSmart::get_instance().vars[selectedDrive].Threshold[j].ThresholdValue);
				}
				else
				{
					cstr = _T("---");
				}
				//m_List.SetItemText(k, 5, cstr);
				AllListInfo.Append(cstr + _T(" "));
				switch (m_RawValues)
				{
				case 3:
					cstr.Format(_T("%d %d %d %d %d %d %d"),
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Reserved,
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[5],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[4],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[3],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[2],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[1],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[0]);
					break;
				case 2:
					cstr.Format(_T("%d %d %d %d"),
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Reserved,
						MAKEWORD(CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[4], CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[5]),
						MAKEWORD(CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[2], CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[3]),
						MAKEWORD(CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[0], CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[1]));
					break;
				case 1:
					cstr.Format(_T("%I64u"),
						((UINT64)CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Reserved << 48) +
						((UINT64)CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[5] << 40) +
						((UINT64)CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[4] << 32) +
						((UINT64)CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[3] << 24) +
						((UINT64)CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[2] << 16) +
						((UINT64)CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[1] << 8) +
						(UINT64)CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[0]);
					break;
				case 0:
				default:
					cstr.Format(_T("%02X%02X%02X%02X%02X%02X%02X"),
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Reserved,
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[5],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[4],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[3],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[2],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[1],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[0]);
					break;
				}
				//	m_List.SetItemText(k, 6, _T("DDDDDDDDDDDDDD"));
				//m_List.SetItemText(k, 6, cstr);
				AllListInfo.Append(cstr + _T("\n"));
			}
			else if (CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_JMICRON && CAtaSmart::get_instance().vars[selectedDrive].IsRawValues8)
			{
				cstr.Format(_T("%d"), CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].CurrentValue);
				/*m_List.SetItemText(k, 3, cstr);
				m_List.SetItemText(k, 4, _T("---"));
				m_List.SetItemText(k, 5, _T("---"));*/
				AllListInfo.Append(cstr + _T(" "));
				switch (m_RawValues)
				{
				case 3:
					cstr.Format(_T("%d %d %d %d %d %d %d %d"),
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Reserved,
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[5],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[4],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[3],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[2],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[1],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[0],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].WorstValue);
					break;
				case 2:
					cstr.Format(_T("%d %d %d %d"),
						MAKEWORD(CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[5], CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Reserved),
						MAKEWORD(CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[3], CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[4]),
						MAKEWORD(CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[1], CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[2]),
						MAKEWORD(CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].WorstValue, CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[0]));
					break;
				case 1:
					cstr.Format(_T("%I64u"),
						((UINT64)CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Reserved << 56) +
						((UINT64)CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[5] << 48) +
						((UINT64)CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[4] << 40) +
						((UINT64)CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[3] << 32) +
						((UINT64)CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[2] << 24) +
						((UINT64)CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[1] << 16) +
						((UINT64)CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[0] << 8) +
						(UINT64)CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].WorstValue);
					break;
				case 0:
				default:
					cstr.Format(_T("%02X%02X%02X%02X%02X%02X%02X%02X"),
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Reserved,
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[5],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[4],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[3],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[2],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[1],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[0],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].WorstValue);
					break;
				}
				//m_List.SetItemText(k, 6, cstr);
				//	m_List.SetItemText(k, 6, _T("DDDDDDDDDDDDDDDD"));
				AllListInfo.Append(cstr + _T("\n"));
			}
			else if (CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_INDILINX)
			{
				/*m_List.SetItemText(k, 3, _T("---"));
				m_List.SetItemText(k, 4, _T("---"));
				m_List.SetItemText(k, 5, _T("---"));*/
				AllListInfo.Append(_T("--- "));
				switch (m_RawValues)
				{
				case 3:
					cstr.Format(_T("%d %d %d %d %d %d %d %d"),
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[5],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[4],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[3],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[2],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[1],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[0],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].WorstValue,
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].CurrentValue);
					break;
				case 2:
					cstr.Format(_T("%d %d %d %d"),
						MAKEWORD(CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[4], CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[5]),
						MAKEWORD(CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[2], CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[3]),
						MAKEWORD(CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[0], CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[1]),
						MAKEWORD(CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].CurrentValue, CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].WorstValue));
					break;
				case 1:
					cstr.Format(_T("%I64u"),
						((UINT64)CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[5] << 56) +
						((UINT64)CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[4] << 48) +
						((UINT64)CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[3] << 40) +
						((UINT64)CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[2] << 32) +
						((UINT64)CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[1] << 24) +
						((UINT64)CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[0] << 16) +
						((UINT64)CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].WorstValue << 8) +
						(UINT64)CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].CurrentValue);
					break;
				case 0:
				default:
					cstr.Format(_T("%02X%02X%02X%02X%02X%02X%02X%02X"),
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[5],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[4],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[3],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[2],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[1],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[0],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].WorstValue,
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].CurrentValue);
					break;
				}
				//m_List.SetItemText(k, 6, cstr);
				//	m_List.SetItemText(k, 6, _T("DDDDDDDDDDDDDDDD"));
				AllListInfo.Append(cstr + _T("\n"));
			}
			else if (CAtaSmart::get_instance().vars[selectedDrive].DiskVendorId == CAtaSmart::get_instance().SSD_VENDOR_NVME)
			{
				cstr = _T("---");
				/*m_List.SetItemText(k, 3, cstr);
				m_List.SetItemText(k, 4, cstr);
				m_List.SetItemText(k, 5, cstr);*/
				AllListInfo.Append(cstr + _T(" "));
				switch (m_RawValues)
				{
				case 3:
					cstr.Format(_T("%d %d %d %d %d %d %d"),
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Reserved,
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[5],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[4],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[3],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[2],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[1],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[0]);
					break;
				case 2:
					cstr.Format(_T("%d %d %d %d"),
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Reserved,
						MAKEWORD(CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[4], CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[5]),
						MAKEWORD(CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[2], CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[3]),
						MAKEWORD(CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[0], CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[1]));
					break;
				case 1:
					cstr.Format(_T("%I64u"),
						((UINT64)CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Reserved << 48) +
						((UINT64)CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[5] << 40) +
						((UINT64)CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[4] << 32) +
						((UINT64)CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[3] << 24) +
						((UINT64)CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[2] << 16) +
						((UINT64)CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[1] << 8) +
						(UINT64)CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[0]);
					break;
				case 0:
				default:
					cstr.Format(_T("%02X%02X%02X%02X%02X%02X%02X"),
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].Reserved,
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[5],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[4],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[3],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[2],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[1],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[0]);
					break;
				}
				//m_List.SetItemText(k, 6, cstr);
				AllListInfo.Append(cstr + _T("\n"));
			}
			else
			{
				cstr.Format(_T("%d"), CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].CurrentValue);
				//m_List.SetItemText(k, 3, cstr);
				AllListInfo.Append(cstr + _T(" "));
				cstr.Format(_T("%d"), CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].WorstValue);
				//m_List.SetItemText(k, 4, cstr);
				AllListInfo.Append(cstr + _T(" "));
				if (CAtaSmart::get_instance().vars[selectedDrive].IsThresholdCorrect)
				{
					cstr.Format(_T("%d"), CAtaSmart::get_instance().vars[selectedDrive].Threshold[j].ThresholdValue);
				}
				else
				{
					cstr = _T("---");
				}
				//m_List.SetItemText(k, 5, cstr);
				AllListInfo.Append(cstr + _T(" "));

				switch (m_RawValues)
				{
				case 3:
					cstr.Format(_T("%d %d %d %d %d %d"),
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[5],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[4],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[3],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[2],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[1],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[0]);
					break;
				case 2:
					cstr.Format(_T("%d %d %d"),
						MAKEWORD(CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[4], CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[5]),
						MAKEWORD(CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[2], CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[3]),
						MAKEWORD(CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[0], CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[1]));
					break;
				case 1:
					cstr.Format(_T("%I64u"),
						((UINT64)CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[5] << 40) +
						((UINT64)CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[4] << 32) +
						((UINT64)CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[3] << 24) +
						((UINT64)CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[2] << 16) +
						((UINT64)CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[1] << 8) +
						(UINT64)CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[0]);
					break;
				case 0:
				default:
					cstr.Format(_T("%02X%02X%02X%02X%02X%02X"),
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[5],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[4],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[3],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[2],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[1],
						CAtaSmart::get_instance().vars[selectedDrive].Attribute[j].RawValue[0]);
					break;
				}
				//	m_List.SetItemText(k, 6, _T("DDDDDDDDDDDD"));
				//m_List.SetItemText(k, 6, cstr);
				AllListInfo.Append(cstr + _T("\n"));
			}
		}
		return AllListInfo.AllocSysString();
	}

	extern "C" IMPORT_DLL double GetCapacity() {
		return CAtaSmart::get_instance().vars[selectedDrive].TotalDiskSize;
	}

	extern "C" IMPORT_DLL int GetTemperature() {
		return CAtaSmart::get_instance().vars[selectedDrive].Temperature;
	}

	extern "C" IMPORT_DLL int GetMeasuredPowerOnHours() {
		return CAtaSmart::get_instance().vars[selectedDrive].MeasuredPowerOnHours;
	}

	extern "C" IMPORT_DLL int GetPowerOnCount() {
		return CAtaSmart::get_instance().vars[selectedDrive].PowerOnCount;
	}

	extern "C" IMPORT_DLL DWORD GetDiskStatus() {
		return CAtaSmart::get_instance().vars[selectedDrive].DiskStatus;
	}


	extern "C" IMPORT_DLL DWORD UpdateInfo() {
		return CAtaSmart::get_instance().UpdateSmartInfo(selectedDrive);
	}
