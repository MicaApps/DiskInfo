
#include "AtaSmartInfo.h"
#if __has_include("AtaSmartInfo.g.cpp")
#include "AtaSmartInfo.g.cpp"
#endif

#include "pch2.h"
#include "AtaSmart.h"

namespace winrt::DiskInfoLibWinRT::implementation
{
    winrt::hstring AtaSmartInfo::Firmware()
    {
        return m_firmware;
    }
    void AtaSmartInfo::Firmware(winrt::hstring value)
    {
        m_firmware = value;
    }
    winrt::hstring AtaSmartInfo::SerialNumber()
    {
        return m_serialNumber;
    }
    void AtaSmartInfo::SerialNumber(winrt::hstring value)
    {
        m_serialNumber = value;
    }
    winrt::hstring AtaSmartInfo::Interface()
    {
        return m_interface;
    }
    void AtaSmartInfo::Interface(winrt::hstring value)
    {
        m_interface = value;
    }
    winrt::hstring AtaSmartInfo::CurrentTransferMode()
    {
        return m_currentTransferMode;
    }
    void AtaSmartInfo::CurrentTransferMode(winrt::hstring value)
    {
        m_currentTransferMode = value;
    }
    winrt::hstring AtaSmartInfo::DriveMap()
    {
        return m_driveMap;
    }
    void AtaSmartInfo::DriveMap(winrt::hstring value)
    {
        m_driveMap = value;
    }
    int AtaSmartInfo::HostReads()
    {
        return m_hostReads;
    }
    void AtaSmartInfo::HostReads(int value)
    {
        m_hostReads = value;
    }
    int AtaSmartInfo::HostWrites()
    {
        return m_hostWrites;
    }
    void AtaSmartInfo::HostWrites(int value)
    {
        m_hostWrites = value;
    }
    int AtaSmartInfo::Rotation()
    {
        return m_rotation;
    }
    void AtaSmartInfo::Rotation(int value)
    {
        m_rotation = value;
    }
    uint32_t AtaSmartInfo::PowerOnCount()
    {
        return m_powerOnCount;
    }
    void AtaSmartInfo::PowerOnCount(uint32_t value)
    {
        m_powerOnCount = value;
    }
    uint32_t AtaSmartInfo::PowerOnTime()
    {
        return m_powerOnTime;
    }
    void AtaSmartInfo::PowerOnTime(uint32_t value)
    {
        m_powerOnTime = value;
    }
    winrt::hstring AtaSmartInfo::Features()
    {
        return m_features;
    }
    void AtaSmartInfo::Features(winrt::hstring value)
    {
        m_features = value;
    }
    winrt::hstring AtaSmartInfo::Standard()
    {
        return m_standard;
    }
    void AtaSmartInfo::Standard(winrt::hstring value)
    {
        m_standard = value;
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> AtaSmartInfo::Attributes()
    {
        return m_attributes;
    }
    void AtaSmartInfo::Update(int index)
    {
        CAtaSmart::get_instance().UpdateSmartInfo(index);
    }
}
