// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Class.g.h"
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Storage.h>

namespace winrt::DiskInfoLibWinRT::implementation
{
    struct Class : ClassT<Class>
    {
        Class();

        winrt::Windows::Foundation::Collections::IVector<winrt::DiskInfoLibWinRT::AtaSmartInfo> Info() { return m_info; }

        void UpdateAll();
    private:
        winrt::Windows::Foundation::Collections::IVector<winrt::DiskInfoLibWinRT::AtaSmartInfo> m_info
        {
            winrt::single_threaded_vector<winrt::DiskInfoLibWinRT::AtaSmartInfo>()
        };
        std::vector<SmartAttribute> m_attributes;
        void SaveSmartInfo(unsigned long i);
        static inline bool m_NowDetectingUnitPowerOnHours = false;
        static inline int SAVE_SMART_PERIOD{};
    };
}

namespace winrt::DiskInfoLibWinRT::factory_implementation
{
    struct Class : ClassT<Class, implementation::Class>
    {
    };
}
