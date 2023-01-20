// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Class.g.h"
#include <winrt/Windows.Foundation.Collections.h>

namespace winrt::DiskInfoLibWinRT::implementation
{
    struct Class : ClassT<Class>
    {
        Class();

        winrt::Windows::Foundation::Collections::IVector<winrt::DiskInfoLibWinRT::AtaSmartInfo> Info() { return m_info; }
    private:
        winrt::Windows::Foundation::Collections::IVector<winrt::DiskInfoLibWinRT::AtaSmartInfo> m_info = winrt::single_threaded_vector<winrt::DiskInfoLibWinRT::AtaSmartInfo>();
        std::vector<SmartAttribute> m_attributes;
    };
}

namespace winrt::DiskInfoLibWinRT::factory_implementation
{
    struct Class : ClassT<Class, implementation::Class>
    {
    };
}
