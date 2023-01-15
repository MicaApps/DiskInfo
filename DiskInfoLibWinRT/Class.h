// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Class.g.h"

namespace winrt::DiskInfoLibWinRT::implementation
{
    struct Class : ClassT<Class>
    {
        Class();

        winrt::hstring Firmware();
        int DriveNum();
        double DiskStatus();
        winrt::hstring AtaAtapi();
        winrt::hstring BufferSize();
        winrt::hstring Feature();
        winrt::hstring FirmwareRev();
        winrt::hstring DriveMap();
    };
}

namespace winrt::DiskInfoLibWinRT::factory_implementation
{
    struct Class : ClassT<Class, implementation::Class>
    {
    };
}
