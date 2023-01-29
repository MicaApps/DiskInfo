// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Class.g.h"
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Storage.h>
#include "pch2.h"

namespace winrt::DiskInfoLibWinRT::implementation
{
    struct Class : ClassT<Class>
    {
        Class();

        winrt::Windows::Foundation::Collections::IVector<winrt::DiskInfoLibWinRT::AtaSmartInfo> Info() { return m_info; }

        void UpdateAll();
        void SaveText(winrt::hstring fileName);

        bool AsciiView() { return m_bAsciiView; }
        void AsciiView(bool value) { m_bAsciiView = value; }

        bool DumpSmartReadData() { return m_bDumpSmartReadData; }
        void DumpSmartReadData(bool value) { m_bDumpSmartReadData = value; }

        bool DumpSmartReadThreshold() { return m_bDumpSmartReadThreshold; }
        void DumpSmartReadThreshold(bool value) { m_bDumpSmartReadThreshold = value; }

        bool DumpIdentifyDevice() { return m_bDumpIdentifyDevice; }
        void DumpIdentifyDevice(bool value) { m_bDumpIdentifyDevice = value; }
    private:
        winrt::Windows::Foundation::Collections::IVector<winrt::DiskInfoLibWinRT::AtaSmartInfo> m_info
        {
            winrt::single_threaded_vector<winrt::DiskInfoLibWinRT::AtaSmartInfo>()
        };
        std::vector<SmartAttribute> m_attributes;

        static inline bool m_NowDetectingUnitPowerOnHours = false;
        static inline int SAVE_SMART_PERIOD{};
        CString i18n(CString section, CString key, BOOL inEnglish = false);
        CString __Number(DWORD value);
        CHAR AsciiFilter(BYTE ch);
        CString GetDiskStatus(DWORD statusCode);
        

        bool m_bDumpIdentifyDevice{};
        bool m_bAsciiView{};
        bool m_bDumpSmartReadData{};
        bool m_bDumpSmartReadThreshold{};
        
        //other options
        bool m_bHideSerialNumber{};
        bool m_bSmartEnglish = true;
        CString m_DefaultLangPath;
        CString m_CurrentLangPath;
    };
}

namespace winrt::DiskInfoLibWinRT::factory_implementation
{
    struct Class : ClassT<Class, implementation::Class>
    {
    };
}
