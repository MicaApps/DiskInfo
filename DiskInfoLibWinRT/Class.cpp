// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "Class.h"
#if __has_include("Class.g.cpp")
#include "Class.g.cpp"
#endif

#include "pch2.h"
#include "AtaSmart.h"

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::DiskInfoLibWinRT::implementation
{
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
	}
	winrt::hstring Class::Firmware()
	{
		auto result = GetFirmware();
		return result;
	}
	int Class::DriveNum()
	{
		return 0;
	}
	double Class::DiskStatus()
	{
		return 0.0;
	}
	winrt::hstring Class::AtaAtapi()
	{
		return winrt::hstring();
	}
	winrt::hstring Class::BufferSize()
	{
		return winrt::hstring();
	}
	winrt::hstring Class::Feature()
	{
		return winrt::hstring();
	}
	winrt::hstring Class::FirmwareRev()
	{
		return winrt::hstring();
	}
	winrt::hstring Class::DriveMap()
	{
		return winrt::hstring();
	}
}
