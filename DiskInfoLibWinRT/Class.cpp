// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "Class.h"
#if __has_include("Class.g.cpp")
#include "Class.g.cpp"
#endif

#include "pch2.h"
#include "AtaSmart.h"
#include <cassert>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.UI.Xaml.Interop.h>
#include <ranges>
#include <filesystem>
#include "PathManager.h"
#include "GraphData.h"
#include <iostream>

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.


namespace winrt::DiskInfoLibWinRT::implementation
{
	constexpr static auto SMART_INI = L"Smart.ini";
	BOOL AppendLog(CString dir, CString disk, CString file, CTime time, int value, BOOL flagFirst, int threshold = 0)
	{
		TCHAR str[256];

		// First Time
		if (flagFirst)
		{
			wsprintf(str, _T("%d"), value);
			WritePrivateProfileStringFx(disk + _T("FIRST"), file, str, dir + _T("\\") + SMART_INI);

			if (file.GetLength() == 2)
			{
				wsprintf(str, _T("%d"), threshold);
				WritePrivateProfileStringFx(disk + _T("THRESHOLD"), file, str, dir + _T("\\") + SMART_INI);
			}
		}

		GetPrivateProfileStringFx(disk, file, _T("-1"), str, 256, dir + _T("\\") + SMART_INI);
		int pre = _tstoi(str);

		if (pre != value)
		{
			// Update
			wsprintf(str, _T("%d"), value);
			WritePrivateProfileStringFx(disk, file, str, dir + _T("\\") + SMART_INI);

			CString line;
			line.Format(_T("%s,%d\n"), time.Format(_T("%Y/%m/%d %H:%M:%S")).GetString(), value);

			CStdioFile outFile;
			if (outFile.Open(dir + _T("\\") + file + _T(".csv"),
				CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite | CFile::typeText))
			{
				ULONGLONG fileLength = outFile.GetLength();
				try
				{
					if (outFile.SeekToEnd() == fileLength)
					{
						outFile.WriteString(line);
					}
				}
				catch (CFileException* e)
				{
					DebugPrint(L"CFileException");
					e->Delete();
				}
				outFile.Close();
				return TRUE;
			}
		}
		return FALSE;
	}

	static void CreateDirectoryRecursive(std::wstring_view path)
	{
		auto parent = path.substr(0, path.substr(0, path.rfind(L"\\")).rfind(L"\\"));
		std::filesystem::create_directory(std::filesystem::path{ parent });
		std::filesystem::create_directory(std::filesystem::path{ path });
	}

	void Class::SaveSmartInfo(unsigned long i)
	{
		if (!CAtaSmart::get_instance().vars[i].IsSmartCorrect)
		{
			return;
		}

		static CTime preTime[CAtaSmart::MAX_DISK] = { 0 };
		CTime time = CTime::GetTickCount();

		if (time - preTime[i] < SAVE_SMART_PERIOD)
		{
			return;
		}
		else
		{
			preTime[i] = time;
		}

		CString line;
		CString cstr;
		CStdioFile outFile;
		CString dir;
		CString disk;
		CString path;
		BOOL flagFirst = FALSE;
		TCHAR str[256];

		dir = PathManager::SmartDir().data();
		CreateDirectoryRecursive(dir.GetBuffer());

		disk = CAtaSmart::get_instance().vars[i].ModelSerial;
		dir += disk;
		std::filesystem::create_directory(std::filesystem::path{ dir.GetBuffer() });


		// Computer Name
		// 
		DWORD length = 256;
		GetComputerNameW(str, &length);
		WritePrivateProfileStringFx(L"PC", L"ComputerName", str, dir + _T("\\") + SMART_INI);

		GetPrivateProfileStringFx(disk, _T("Date"), _T(""), str, 256, dir + _T("\\") + SMART_INI);
		cstr = str;
		if (cstr.IsEmpty())
		{
			flagFirst = TRUE;
			_stprintf_s(str, 256, _T("%s"), time.Format(_T("%Y/%m/%d %H:%M:%S")).GetBuffer());
			WritePrivateProfileStringFx(disk + _T("FIRST"), _T("Date"), str, dir + _T("\\") + SMART_INI);

			_stprintf_s(str, 256, _T("%d"), CAtaSmart::get_instance().vars[i].DiskStatus);
			WritePrivateProfileStringFx(disk + _T("FIRST"), _T("HealthStatus"), str, dir + _T("\\") + SMART_INI);
		}

		// Check Threshold of Reallocated Sectors Count
		GetPrivateProfileStringFx(disk + _T("THRESHOLD"), _T("05"), _T(""), str, 256, dir + _T("\\") + SMART_INI);
		cstr = str;
		if (cstr.IsEmpty())
		{
			flagFirst = TRUE;
		}

		_stprintf_s(str, 256, _T("%s"), time.Format(_T("%Y/%m/%d %H:%M:%S")).GetBuffer());
		WritePrivateProfileStringFx(disk, _T("Date"), str, dir + _T("\\") + SMART_INI);

		_stprintf_s(str, 256, _T("%d"), CAtaSmart::get_instance().vars[i].DiskStatus);
		WritePrivateProfileStringFx(disk, _T("HealthStatus"), str, dir + _T("\\") + SMART_INI);

		if (CAtaSmart::get_instance().vars[i].Temperature > -300)
		{
			AppendLog(dir, disk, _T("Temperature"), time, CAtaSmart::get_instance().vars[i].Temperature, flagFirst);
		}

		if (CAtaSmart::get_instance().vars[i].MeasuredPowerOnHours > 0 && m_NowDetectingUnitPowerOnHours == FALSE)
		{
			AppendLog(dir, disk, _T("PowerOnHours"), time, CAtaSmart::get_instance().vars[i].MeasuredPowerOnHours, flagFirst);
		}

		if (CAtaSmart::get_instance().vars[i].PowerOnCount >= 0)
		{
			AppendLog(dir, disk, _T("PowerOnCount"), time, CAtaSmart::get_instance().vars[i].PowerOnCount, flagFirst);
		}

		if (CAtaSmart::get_instance().vars[i].Life >= 0)
		{
			AppendLog(dir, disk, _T("Life"), time, CAtaSmart::get_instance().vars[i].Life, flagFirst);
		}

		if (CAtaSmart::get_instance().vars[i].HostWrites >= 0)
		{
			AppendLog(dir, disk, _T("HostWrites"), time, CAtaSmart::get_instance().vars[i].HostWrites, flagFirst);
		}

		if (CAtaSmart::get_instance().vars[i].HostReads >= 0)
		{
			AppendLog(dir, disk, _T("HostReads"), time, CAtaSmart::get_instance().vars[i].HostReads, flagFirst);
		}

		if (CAtaSmart::get_instance().vars[i].NandWrites >= 0)
		{
			AppendLog(dir, disk, _T("NandWrites"), time, CAtaSmart::get_instance().vars[i].NandWrites, flagFirst);
		}

		if (CAtaSmart::get_instance().vars[i].GBytesErased >= 0)
		{
			AppendLog(dir, disk, _T("GBytesErased"), time, CAtaSmart::get_instance().vars[i].GBytesErased, flagFirst);
		}

		if (CAtaSmart::get_instance().vars[i].WearLevelingCount >= 0)
		{
			AppendLog(dir, disk, _T("WearLevelingCount"), time, CAtaSmart::get_instance().vars[i].WearLevelingCount, flagFirst);
		}

		for (DWORD j = 0; j < CAtaSmart::get_instance().vars[i].AttributeCount; j++)
		{
			cstr.Format(_T("%02X"), CAtaSmart::get_instance().vars[i].Attribute[j].Id);
			AppendLog(dir, disk, cstr, time, CAtaSmart::get_instance().vars[i].Attribute[j].CurrentValue,
				flagFirst, CAtaSmart::get_instance().vars[i].Threshold[j].ThresholdValue);

			switch (CAtaSmart::get_instance().vars[i].Attribute[j].Id)
			{
			case 0x05: // Reallocated Sectors Count
				AppendLog(dir, disk, _T("ReallocatedSectorsCount"), time,
					MAKEWORD(CAtaSmart::get_instance().vars[i].Attribute[j].RawValue[0], CAtaSmart::get_instance().vars[i].Attribute[j].RawValue[1]), flagFirst);
				break;
			case 0xC4: // Reallocation Event Count
				AppendLog(dir, disk, _T("ReallocationEventCount"), time,
					MAKEWORD(CAtaSmart::get_instance().vars[i].Attribute[j].RawValue[0], CAtaSmart::get_instance().vars[i].Attribute[j].RawValue[1]), flagFirst);
				break;
			case 0xC5: // Current Pending Sector Count
				AppendLog(dir, disk, _T("CurrentPendingSectorCount"), time,
					MAKEWORD(CAtaSmart::get_instance().vars[i].Attribute[j].RawValue[0], CAtaSmart::get_instance().vars[i].Attribute[j].RawValue[1]), flagFirst);
				break;
			case 0xC6: // Off-Line Scan Uncorrectable Sector Count
				AppendLog(dir, disk, _T("UncorrectableSectorCount"), time,
					MAKEWORD(CAtaSmart::get_instance().vars[i].Attribute[j].RawValue[0], CAtaSmart::get_instance().vars[i].Attribute[j].RawValue[1]), flagFirst);
				break;
			default:
				break;
			}
		}
	}

	Class::Class()
	{
		BOOL flagChangeDisk = false;
		AtaSmartInit(
			true,
			false,
			&flagChangeDisk,
			false,
			true,
			false);

		auto& instance = CAtaSmart::get_instance();
		auto const size = instance.vars.GetSize();
		for (auto i = 0; i < size; ++i)
		{
			auto const& original = instance.vars[i];
			winrt::DiskInfoLibWinRT::AtaSmartInfo info;
			info.Firmware(original.FirmwareRev.GetString());
			info.SerialNumber(original.SerialNumber.GetString());
			info.Interface(original.Interface.GetString());
			info.CurrentTransferMode(
				(original.CurrentTransferMode + L" | " + original.MaxTransferMode)
				.GetString());
			//info.MaxTransferMode(original.MaxTransferMode.AllocSysString());
			info.DriveMap(original.DriveMap.GetString());
			info.HostReads(original.HostReads);
			info.HostWrites(original.HostWrites);
			info.Rotation(original.NominalMediaRotationRate);
			info.PowerOnCount(original.PowerOnCount);
			info.PowerOnTime(original.PowerOnRawValue);
			info.Standard((original.MajorVersion + L" | " + original.MinorVersion).GetString());
			info.Index(i);
			//attributes
			for (auto j = 0; j < std::size(original.Attribute); ++j)
			{
				auto const& attribute = original.Attribute[j];
				auto const& threshold = original.Threshold[j];

				SmartAttribute attr{};
				attr.Id = std::format(L"{:0>2x}", attribute.Id);

				wchar_t buf[256]{};
				static winrt::hstring const path{ [] {
					TCHAR currentExePath[MAX_PATH]{};
					GetModuleFileName(NULL, currentExePath, MAX_PATH);
					MessageBox(NULL, currentExePath, L"", 0);
					std::wstring_view view{ currentExePath };
					view = view.substr(0, view.rfind(L"\\"));
					return std::wstring{ view } + LR"(\Assets\English.lang)";
				}() };

				GetPrivateProfileStringFx(
					original.SmartKeyName,
					attr.Id.data(),
					L"",
					buf,
					sizeof(buf) / sizeof(wchar_t),
					path.data()
				);

				attr.Name = buf;

				std::wstring rawValue;
				for (auto byte : std::ranges::reverse_view(attribute.RawValue))
					rawValue += std::format(L"{:0>2x}", byte);

				attr.RawValue = rawValue;
				attr.Threshold = std::format(L"{:0>2x}", threshold.ThresholdValue);

				info.Attributes().Append(winrt::box_value(attr));
			}
			m_info.Append(info);
		}

		//log
		//SaveSmartInfo(0);

		//set data source
		GraphData::GetInstance().SetDataSource(CAtaSmart::get_instance().vars);
	}

	void Class::UpdateAll()
	{
		for (int i = 0; i < m_info.Size(); ++i)
		{
			auto disk = m_info.GetAt(i);
			disk.Update();
			SaveSmartInfo(i);
		}
	}
}
