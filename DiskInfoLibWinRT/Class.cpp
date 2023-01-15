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

		auto& instance = CAtaSmart::get_instance();
		auto const size = instance.vars.GetSize();
		for (auto i = 0; i < size; ++i)
		{
			auto const& original = instance.vars[i];
			winrt::DiskInfoLibWinRT::AtaSmartInfo info{};
			info.Firmware = original.FirmwareRev;
			info.SerialNumber = original.SerialNumber;
			info.Interface = original.Interface;
			info.CurrentTransferMode = original.CurrentTransferMode;
			info.MaxTransferMode = original.MaxTransferMode;
			info.DriveMap = original.DriveMap;
			info.HostReads = original.HostReads;
			info.HostWrites = original.HostWrites;
			info.Rotation = original.NominalMediaRotationRate;
			info.PowerOnCount = original.PowerOnCount;
			info.PowerOnTime = original.PowerOnRawValue;
			info.Standard = original.MajorVersion + L" | " + original.MinorVersion;
			m_info.Append(std::move(info));
		}
	}

}
