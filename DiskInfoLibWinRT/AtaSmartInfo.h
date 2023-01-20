#pragma once

#include "AtaSmartInfo.g.h"

namespace winrt::DiskInfoLibWinRT::implementation
{
    struct AtaSmartInfo : AtaSmartInfoT<AtaSmartInfo>
    {
        AtaSmartInfo() = default;

        winrt::hstring Firmware();
        void Firmware(winrt::hstring value);

        winrt::hstring SerialNumber();
        void SerialNumber(winrt::hstring value);

        winrt::hstring Interface();
        void Interface(winrt::hstring value);

        winrt::hstring CurrentTransferMode();
        void CurrentTransferMode(winrt::hstring value);

        winrt::hstring DriveMap();
        void DriveMap(winrt::hstring value);

        int HostReads();
        void HostReads(int value);

        int HostWrites();
        void HostWrites(int value);

        int Rotation();
        void Rotation(int value);

        uint32_t PowerOnCount();
        void PowerOnCount(uint32_t value);

        uint32_t PowerOnTime();
        void PowerOnTime(uint32_t value);

        winrt::hstring Features();
        void Features(winrt::hstring value);

        winrt::hstring Standard();
        void Standard(winrt::hstring value);

        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> Attributes();
    private:
        winrt::hstring m_firmware;
        winrt::hstring m_serialNumber;
        winrt::hstring m_interface;
        winrt::hstring m_currentTransferMode;
        winrt::hstring m_maxTransferMode;
        winrt::hstring m_driveMap;
        int m_hostReads{};
        int m_hostWrites{};
        int m_rotation{};
        uint32_t m_powerOnCount{};
        uint32_t m_powerOnTime{};
        winrt::hstring m_features;
        winrt::hstring m_standard;
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> m_attributes
        {
            winrt::single_threaded_vector<winrt::Windows::Foundation::IInspectable>()
        };
    };
}

namespace winrt::DiskInfoLibWinRT::factory_implementation
{
    struct AtaSmartInfo : AtaSmartInfoT<AtaSmartInfo, implementation::AtaSmartInfo>
    {
    };
}
