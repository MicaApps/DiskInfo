
#include "AtaSmartInfo.h"
#if __has_include("AtaSmartInfo.g.cpp")
#include "AtaSmartInfo.g.cpp"
#endif

#include "pch2.h"
#include "AtaSmart.h"
#include "GraphData.h"
#include <ppltasks.h>
#include <pplawait.h>
#include <PathCch.h>
#include <filesystem>
#pragma comment(lib, "pathcch.lib")

namespace winrt::DiskInfoLibWinRT::implementation
{
    winrt::hstring AtaSmartInfo::Model()
    {
        return m_model;
    }
    void AtaSmartInfo::Model(winrt::hstring value)
    {
        m_model = value;
    }
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
    int AtaSmartInfo::Life()
    {
        return m_life;
    }
    void AtaSmartInfo::Life(int value)
    {
        m_life = value;
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> AtaSmartInfo::Attributes()
    {
        return m_attributes;
    }
    void AtaSmartInfo::Update()
    {
        CAtaSmart::get_instance().UpdateSmartInfo(m_index);
    }
    int AtaSmartInfo::Index()
    {
        return m_index;
    }
    void AtaSmartInfo::Index(int index)
    {
        m_index = index;
    }

    winrt::Windows::Foundation::IAsyncOperation<int> AtaSmartInfo::SeqReadSpd()
    {
        auto result = co_await concurrency::create_task(
            [this]
            {
                std::wstring testFile = std::format(LR"({}:\test.dat)", m_driveMap[0]);
                TestFileGuard guard{ testFile };
                auto cmd = currentPath() + std::format(LR"(\DiskSpd64.exe -b1024K -o8 -t1 -W0 -S -w0 -ag -d5 "{}")", testFile);
                return execAndWait(cmd.data());
            }
            );
        co_return result;
    }

    winrt::Windows::Foundation::IAsyncOperation<int> AtaSmartInfo::SeqWriteSpd()
    {
        auto result = co_await concurrency::create_task(
            [this]
            {
                std::wstring testFile = std::format(LR"({}:\test.dat)", m_driveMap[0]);
                TestFileGuard guard{ testFile };
                auto cmd = currentPath() + std::format(LR"(\DiskSpd64.exe -b1024K -o8 -t1 -W0 -S -w100 -ag -d5 "{}")", testFile);
                return execAndWait(cmd.data());
            }
            );
        co_return result;
    }

    winrt::Windows::Foundation::IAsyncOperation<int> AtaSmartInfo::RandomReadSpd()
    {
        auto result = co_await concurrency::create_task(
            [this]
            {
                std::wstring testFile = std::format(LR"({}:\test.dat)", m_driveMap[0]);
                TestFileGuard guard{ testFile };
                auto cmd = currentPath() + std::format(LR"(\DiskSpd64.exe -b4K -o1 -t1 -W0 -S -w0 -r -ag -d5 -A{} "{}")", GetCurrentProcessId(), testFile);
                return execAndWait(cmd.data());
            }
            );
        co_return result;
    }

    winrt::Windows::Foundation::IAsyncOperation<int> AtaSmartInfo::RandomWriteSpd()
    {
        auto result = co_await concurrency::create_task(
            [this]
            {
                std::wstring testFile = std::format(LR"({}:\test.dat)", m_driveMap[0]);
                TestFileGuard guard{ testFile };
                auto cmd = currentPath() + std::format(LR"(\DiskSpd64.exe -b4K -o1 -t1 -W0 -S -w100 -r -ag -d5 -A{} "{}")", GetCurrentProcessId(), testFile);
                return execAndWait(cmd.data());
            }
            );
        co_return result;
    }

    int AtaSmartInfo::execAndWait(TCHAR* pszCmd)
    {
        DWORD Code = 0;
        BOOL bSuccess;
        STARTUPINFO si;

        memset(&si, 0, sizeof(STARTUPINFO));
        si.cb = sizeof(STARTUPINFO);

        PROCESS_INFORMATION pi{};
        si.dwFlags = STARTF_USESHOWWINDOW;
        si.wShowWindow = SW_HIDE;

        bSuccess = CreateProcess(NULL, pszCmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
        if (bSuccess != TRUE)
        {
            MessageBox(NULL, std::to_wstring(GetLastError()).data(), L"", 0);
            return -1;
        }

        WaitForInputIdle(pi.hProcess, INFINITE);
        WaitForSingleObject(pi.hProcess, INFINITE);
        GetExitCodeProcess(pi.hProcess, &Code);

        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);

        pi.hProcess = NULL;
        return Code;
    }

    std::wstring AtaSmartInfo::currentPath()
    {
        wchar_t path[MAX_PATH]{};
        GetModuleFileName(NULL, path, std::size(path));
        PathCchRemoveFileSpec(path, std::size(path));
        return path;
    }

    static auto MakeFakeData(int numData = 5)
    {
        auto data = winrt::single_threaded_vector<winrt::DiskInfoLibWinRT::GraphDataPoint>();
        for (int i = 0; i < numData; ++i)
        {
            data.Append(winrt::DiskInfoLibWinRT::GraphDataPoint{
                static_cast<uint64_t>(winrt::clock::to_time_t(winrt::clock::now() - std::chrono::days{numData - i})),
                static_cast<uint32_t>(i * i)
                });
        }
        return data;
    }

    winrt::Windows::Foundation::Collections::IVector<winrt::DiskInfoLibWinRT::GraphDataPoint> AtaSmartInfo::readCsv(int dataType)
    {
        auto data = winrt::single_threaded_vector<winrt::DiskInfoLibWinRT::GraphDataPoint>();

        constexpr static auto timeOffset = 19;
        constexpr static auto valueOffset = 20;

        auto f = GraphData::GetInstance().GetDataFile(dataType, m_index);
        if (f.is_open())
        {
            std::wstring stdLine;
            while (std::getline(f, stdLine))
            {
                CString line = stdLine.data();
                auto time = GraphDataUtil::GetTimeT(line.Left(timeOffset));
                auto value = GraphDataUtil::GetValue(line.Mid(valueOffset));
                data.Append(
                    winrt::DiskInfoLibWinRT::GraphDataPoint
                    {
                        static_cast<uint64_t>(time),
                        static_cast<uint32_t>(value)
                    }
                );
            }
        }
#ifdef _DEBUG
        if (data.Size() == 0)
            return MakeFakeData();
#endif
        return data;
    }

    AtaSmartInfo::TestFileGuard::TestFileGuard(std::wstring_view testFile) : m_testFilePath{ testFile }
    {
        assert(!testFile.empty());
        //CreateDirectory(m_testFileDir.data(), NULL);
        //::CreateFile(m_testFilePath.data(), GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
        //    FILE_ATTRIBUTE_NORMAL | FILE_FLAG_NO_BUFFERING | FILE_FLAG_SEQUENTIAL_SCAN, NULL);

        auto hFile = ::CreateFile(m_testFilePath.data(), GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
            FILE_ATTRIBUTE_NORMAL | FILE_FLAG_NO_BUFFERING | FILE_FLAG_SEQUENTIAL_SCAN, NULL);

        LARGE_INTEGER nFileSize;
        nFileSize.QuadPart = 1024 * 1024 * 1024;

        LARGE_INTEGER nStart;
        nStart.QuadPart = 0;

        SetFilePointerEx(hFile, nFileSize, NULL, FILE_BEGIN);
        SetEndOfFile(hFile);
        SetFilePointerEx(hFile, nStart, NULL, FILE_BEGIN);

        USHORT lpInBuffer = COMPRESSION_FORMAT_NONE;
        DWORD lpBytesReturned = 0;
        DeviceIoControl(hFile, FSCTL_SET_COMPRESSION, (LPVOID)&lpInBuffer,
            sizeof(USHORT), NULL, 0, (LPDWORD)&lpBytesReturned, NULL);

        constexpr static auto bufSize = 1024 * 1024;
        std::vector<char> buf;
        buf.reserve(bufSize);
        std::generate_n(
            std::back_inserter(buf),
            bufSize,
            [] {return (char)rand() % 256; }
        );
        DWORD writeSize{};
        for (int i = 0; i < 1024; ++i)
        {
            WriteFile(hFile, buf.data(), bufSize, &writeSize, nullptr);
        }
        CloseHandle(hFile);
    }

    AtaSmartInfo::TestFileGuard::~TestFileGuard()
    {
        try
        {
            std::filesystem::remove(m_testFilePath);
        }
        catch (...)
        {

        }
    }
}
