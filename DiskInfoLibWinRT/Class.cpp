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

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::DiskInfoLibWinRT::implementation
{
	//DWORD GetPrivateProfileStringFx(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpDefault, LPTSTR  lpReturnedString, DWORD nSize, LPCTSTR lpFileName)
	//{
	//	DWORD result = 0;
	//	CString key = lpKeyName;
	//	key.Replace(L"=", L"%#3D");
	//	key.Replace(L"\"", L"%#22");
	//	result = GetPrivateProfileString(lpAppName, key, lpDefault, lpReturnedString, nSize, lpFileName);

	//	CString value = lpReturnedString;
	//	value.Replace(L"%#3D", L"=");
	//	value.Replace(L"%#22", L"\"");
	//	_tcscpy_s(lpReturnedString, nSize, value.GetString());

	//	return result;
	//}

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
				for(auto byte : std::ranges::reverse_view(attribute.RawValue))
					rawValue += std::format(L"{:0>2x}", byte);

				attr.RawValue = rawValue;
				attr.Threshold = std::format(L"{:0>2x}", threshold.ThresholdValue);

				info.Attributes().Append(winrt:: box_value(attr));
			}
			m_info.Append(info);
		}
	}

}
