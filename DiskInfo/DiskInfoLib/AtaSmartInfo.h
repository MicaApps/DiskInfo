#pragma once

#include "AtaSmartInfo.g.h"
#include <winrt/Windows.Foundation.Collections.h>
#include "GraphData.h"
#include <format>
#include <timeapi.h>

namespace winrt::DiskInfoLibWinRT::implementation
{
    struct AtaSmartInfo : AtaSmartInfoT<AtaSmartInfo>
    {
        AtaSmartInfo() = default;

        winrt::hstring Model();
        void Model(winrt::hstring value);

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

        int Life();
        void Life(int value);

        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> Attributes();

        winrt::Windows::Foundation::Collections::IVector<winrt::DiskInfoLibWinRT::GraphDataPoint> TemperatureData() { return readCsv(GraphData::SMART_TEMPERATURE); }
        winrt::Windows::Foundation::Collections::IVector<winrt::DiskInfoLibWinRT::GraphDataPoint> ReallocatedSectorsData() { return readCsv(GraphData::SMART_REALLOCATED_SECTORS_COUNT); }
        winrt::Windows::Foundation::Collections::IVector<winrt::DiskInfoLibWinRT::GraphDataPoint> PowerOnHoursData() { return readCsv(GraphData::SMART_POWER_ON_HOURS); }
        winrt::Windows::Foundation::Collections::IVector<winrt::DiskInfoLibWinRT::GraphDataPoint> PowerCycleData() { return readCsv(GraphData::SMART_POWER_ON_COUNT); }
        winrt::Windows::Foundation::Collections::IVector<winrt::DiskInfoLibWinRT::GraphDataPoint> ReallocationEventData() { return readCsv(GraphData::SMART_REALLOCATED_EVENT_COUNT); }
        winrt::Windows::Foundation::Collections::IVector<winrt::DiskInfoLibWinRT::GraphDataPoint> PendingSectorData() { return readCsv(GraphData::SMART_CURRENT_PENDING_SECTOR_COUNT); }
        winrt::Windows::Foundation::Collections::IVector<winrt::DiskInfoLibWinRT::GraphDataPoint> UncorrectableSectorData() { return readCsv(GraphData::SMART_UNCORRECTABLE_SECTOR_COUNT); }
        winrt::Windows::Foundation::Collections::IVector<winrt::DiskInfoLibWinRT::GraphDataPoint> RemainingLifeData() { return readCsv(GraphData::SMART_LIFE); }
        winrt::Windows::Foundation::Collections::IVector<winrt::DiskInfoLibWinRT::GraphDataPoint> TotalHostWritesData() { return readCsv(GraphData::SMART_HOST_WRITES); }
        winrt::Windows::Foundation::Collections::IVector<winrt::DiskInfoLibWinRT::GraphDataPoint> TotalHostReadsData() { return readCsv(GraphData::SMART_HOST_READS); }
        winrt::Windows::Foundation::Collections::IVector<winrt::DiskInfoLibWinRT::GraphDataPoint> TotalNandWritesData() { return readCsv(GraphData::SMART_NAND_WRITES); }
        winrt::Windows::Foundation::Collections::IVector<winrt::DiskInfoLibWinRT::GraphDataPoint> GigabytesErasedData() { return readCsv(GraphData::SMART_NAND_ERASED); }
        winrt::Windows::Foundation::Collections::IVector<winrt::DiskInfoLibWinRT::GraphDataPoint> WearLevelingCountData() { return readCsv(GraphData::SMART_WEAR_LEVELING_COUNT); }

        void Update();

        int Index();
        void Index(int index);

        winrt::Windows::Foundation::IAsyncOperation<int> SeqReadSpd();
        winrt::Windows::Foundation::IAsyncOperation<int> SeqWriteSpd();
        winrt::Windows::Foundation::IAsyncOperation<int> RandomReadSpd();
        winrt::Windows::Foundation::IAsyncOperation<int> RandomWriteSpd();
    private:
        static int execAndWait(TCHAR* pszCmd);
        static std::wstring currentPath();

        class TestFileGuard
        {
            //std::wstring m_testFileDir = std::format(LR"(C:\CrystalDiskMark{})", timeGetTime());
            std::wstring m_testFilePath;
        public:
            TestFileGuard(std::wstring_view testFilePath);
            ~TestFileGuard();
        };

        int m_index = -1;
        winrt::hstring m_model;
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
        int m_life{};
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> m_attributes
        {
            winrt::single_threaded_vector<winrt::Windows::Foundation::IInspectable>()
        };
        winrt::Windows::Foundation::Collections::IVector<winrt::DiskInfoLibWinRT::GraphDataPoint> readCsv(int dataType);
    };
}

namespace winrt::DiskInfoLibWinRT::factory_implementation
{
    struct AtaSmartInfo : AtaSmartInfoT<AtaSmartInfo, implementation::AtaSmartInfo>
    {
    };
}
