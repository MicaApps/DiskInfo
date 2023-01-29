#include "GraphData.h"
#include "PathManager.h"
#include <filesystem>

constexpr static auto SMART_INI = L"Smart.ini";
static BOOL AppendLog(CString dir, CString disk, CString file, CTime time, int value, BOOL flagFirst, int threshold = 0)
{
	TCHAR str[256];

	// First Time
	if (flagFirst)
	{
		wsprintf(str, _T("%d"), value);
		WritePrivateProfileStringFx(disk + _T("FIRST"), file, str, dir + _T("\\") + SMART_INI);

		if (file.GetLength() == 2)
		{
			wsprintf(str, _T("%d"), threshold);
			WritePrivateProfileStringFx(disk + _T("THRESHOLD"), file, str, dir + _T("\\") + SMART_INI);
		}
	}

	GetPrivateProfileStringFx(disk, file, _T("-1"), str, 256, dir + _T("\\") + SMART_INI);
	int pre = _tstoi(str);

	if (pre != value)
	{
		// Update
		wsprintf(str, _T("%d"), value);
		WritePrivateProfileStringFx(disk, file, str, dir + _T("\\") + SMART_INI);

		CString line;
		line.Format(_T("%s,%d\n"), time.Format(_T("%Y/%m/%d %H:%M:%S")).GetString(), value);

		CStdioFile outFile;
		if (outFile.Open(dir + _T("\\") + file + _T(".csv"),
			CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite | CFile::typeText))
		{
			ULONGLONG fileLength = outFile.GetLength();
			try
			{
				if (outFile.SeekToEnd() == fileLength)
				{
					outFile.WriteString(line);
				}
			}
			catch (CFileException* e)
			{
				DebugPrint(L"CFileException");
				e->Delete();
			}
			outFile.Close();
			return TRUE;
		}
	}
	return FALSE;
}

static void CreateDirectoryRecursive(std::wstring_view path)
{
	auto parent = path.substr(0, path.substr(0, path.rfind(L"\\")).rfind(L"\\"));
	std::filesystem::create_directory(std::filesystem::path{ parent });
	std::filesystem::create_directory(std::filesystem::path{ path });
}


void GraphData::SetDataSource(DataSourceType const& source)
{
	m_dataSource = &source;
}

void GraphData::SaveSmartInfo(unsigned long i)
{
	if (!CAtaSmart::get_instance().vars[i].IsSmartCorrect)
	{
		return;
	}

	//确保两次保存时间间隔的逻辑，这里先去掉
	//static CTime preTime[CAtaSmart::MAX_DISK] = { 0 };
	CTime time = CTime::GetTickCount();

	//if (time - preTime[i] < SAVE_SMART_PERIOD)
	//{
	//	return;
	//}
	//else
	//{
	//	preTime[i] = time;
	//}

	CString line;
	CString cstr;
	CStdioFile outFile;
	CString dir;
	CString disk;
	CString path;
	BOOL flagFirst = FALSE;
	TCHAR str[256];

	dir = PathManager::GetInstance().SmartDir().data();
	CreateDirectoryRecursive(dir.GetBuffer());

	disk = CAtaSmart::get_instance().vars[i].ModelSerial;
	dir += disk;
	std::filesystem::create_directory(std::filesystem::path{ dir.GetBuffer() });


	// Computer Name
	// 
	DWORD length = 256;
	GetComputerNameW(str, &length);
	WritePrivateProfileStringFx(L"PC", L"ComputerName", str, dir + _T("\\") + SMART_INI);

	GetPrivateProfileStringFx(disk, _T("Date"), _T(""), str, 256, dir + _T("\\") + SMART_INI);
	cstr = str;
	if (cstr.IsEmpty())
	{
		flagFirst = TRUE;
		_stprintf_s(str, 256, _T("%s"), time.Format(_T("%Y/%m/%d %H:%M:%S")).GetBuffer());
		WritePrivateProfileStringFx(disk + _T("FIRST"), _T("Date"), str, dir + _T("\\") + SMART_INI);

		_stprintf_s(str, 256, _T("%d"), CAtaSmart::get_instance().vars[i].DiskStatus);
		WritePrivateProfileStringFx(disk + _T("FIRST"), _T("HealthStatus"), str, dir + _T("\\") + SMART_INI);
	}

	// Check Threshold of Reallocated Sectors Count
	GetPrivateProfileStringFx(disk + _T("THRESHOLD"), _T("05"), _T(""), str, 256, dir + _T("\\") + SMART_INI);
	cstr = str;
	if (cstr.IsEmpty())
	{
		flagFirst = TRUE;
	}

	_stprintf_s(str, 256, _T("%s"), time.Format(_T("%Y/%m/%d %H:%M:%S")).GetBuffer());
	WritePrivateProfileStringFx(disk, _T("Date"), str, dir + _T("\\") + SMART_INI);

	_stprintf_s(str, 256, _T("%d"), CAtaSmart::get_instance().vars[i].DiskStatus);
	WritePrivateProfileStringFx(disk, _T("HealthStatus"), str, dir + _T("\\") + SMART_INI);

	if (CAtaSmart::get_instance().vars[i].Temperature > -300)
	{
		AppendLog(dir, disk, _T("Temperature"), time, CAtaSmart::get_instance().vars[i].Temperature, flagFirst);
	}

	if (CAtaSmart::get_instance().vars[i].MeasuredPowerOnHours > 0/* && m_NowDetectingUnitPowerOnHours == FALSE*/)
	{
		AppendLog(dir, disk, _T("PowerOnHours"), time, CAtaSmart::get_instance().vars[i].MeasuredPowerOnHours, flagFirst);
	}

	if (CAtaSmart::get_instance().vars[i].PowerOnCount >= 0)
	{
		AppendLog(dir, disk, _T("PowerOnCount"), time, CAtaSmart::get_instance().vars[i].PowerOnCount, flagFirst);
	}

	if (CAtaSmart::get_instance().vars[i].Life >= 0)
	{
		AppendLog(dir, disk, _T("Life"), time, CAtaSmart::get_instance().vars[i].Life, flagFirst);
	}

	if (CAtaSmart::get_instance().vars[i].HostWrites >= 0)
	{
		AppendLog(dir, disk, _T("HostWrites"), time, CAtaSmart::get_instance().vars[i].HostWrites, flagFirst);
	}

	if (CAtaSmart::get_instance().vars[i].HostReads >= 0)
	{
		AppendLog(dir, disk, _T("HostReads"), time, CAtaSmart::get_instance().vars[i].HostReads, flagFirst);
	}

	if (CAtaSmart::get_instance().vars[i].NandWrites >= 0)
	{
		AppendLog(dir, disk, _T("NandWrites"), time, CAtaSmart::get_instance().vars[i].NandWrites, flagFirst);
	}

	if (CAtaSmart::get_instance().vars[i].GBytesErased >= 0)
	{
		AppendLog(dir, disk, _T("GBytesErased"), time, CAtaSmart::get_instance().vars[i].GBytesErased, flagFirst);
	}

	if (CAtaSmart::get_instance().vars[i].WearLevelingCount >= 0)
	{
		AppendLog(dir, disk, _T("WearLevelingCount"), time, CAtaSmart::get_instance().vars[i].WearLevelingCount, flagFirst);
	}

	for (DWORD j = 0; j < CAtaSmart::get_instance().vars[i].AttributeCount; j++)
	{
		cstr.Format(_T("%02X"), CAtaSmart::get_instance().vars[i].Attribute[j].Id);
		AppendLog(dir, disk, cstr, time, CAtaSmart::get_instance().vars[i].Attribute[j].CurrentValue,
			flagFirst, CAtaSmart::get_instance().vars[i].Threshold[j].ThresholdValue);

		switch (CAtaSmart::get_instance().vars[i].Attribute[j].Id)
		{
		case 0x05: // Reallocated Sectors Count
			AppendLog(dir, disk, _T("ReallocatedSectorsCount"), time,
				MAKEWORD(CAtaSmart::get_instance().vars[i].Attribute[j].RawValue[0], CAtaSmart::get_instance().vars[i].Attribute[j].RawValue[1]), flagFirst);
			break;
		case 0xC4: // Reallocation Event Count
			AppendLog(dir, disk, _T("ReallocationEventCount"), time,
				MAKEWORD(CAtaSmart::get_instance().vars[i].Attribute[j].RawValue[0], CAtaSmart::get_instance().vars[i].Attribute[j].RawValue[1]), flagFirst);
			break;
		case 0xC5: // Current Pending Sector Count
			AppendLog(dir, disk, _T("CurrentPendingSectorCount"), time,
				MAKEWORD(CAtaSmart::get_instance().vars[i].Attribute[j].RawValue[0], CAtaSmart::get_instance().vars[i].Attribute[j].RawValue[1]), flagFirst);
			break;
		case 0xC6: // Off-Line Scan Uncorrectable Sector Count
			AppendLog(dir, disk, _T("UncorrectableSectorCount"), time,
				MAKEWORD(CAtaSmart::get_instance().vars[i].Attribute[j].RawValue[0], CAtaSmart::get_instance().vars[i].Attribute[j].RawValue[1]), flagFirst);
			break;
		default:
			break;
		}
	}
}

std::wifstream GraphData::GetDataFile(DWORD attributeId, unsigned long i)
{
	if (i >= m_dataSource->GetCount())
		return {};
	std::wstring fileName;

	switch (attributeId)
	{
		case SMART_TEMPERATURE:                  fileName = _T("Temperature");				break;
		case SMART_POWER_ON_HOURS:               fileName = _T("PowerOnHours");				break;
		case SMART_POWER_ON_COUNT:               fileName = _T("PowerOnCount");				break;
		case SMART_REALLOCATED_SECTORS_COUNT:    fileName = _T("ReallocatedSectorsCount");	break;
		case SMART_REALLOCATED_EVENT_COUNT:      fileName = _T("ReallocationEventCount");	break;
		case SMART_CURRENT_PENDING_SECTOR_COUNT: fileName = _T("CurrentPendingSectorCount");break;
		case SMART_UNCORRECTABLE_SECTOR_COUNT:   fileName = _T("UncorrectableSectorCount");	break;
		case SMART_HOST_WRITES:                  fileName = _T("HostWrites");				break;
		case SMART_HOST_READS:                   fileName = _T("HostReads");				break;
		case SMART_NAND_WRITES:                  fileName = _T("NandWrites");				break;
		case SMART_NAND_ERASED:                  fileName = _T("GBytesErased");				break;
		case SMART_WEAR_LEVELING_COUNT:          fileName = _T("WearLevelingCount");		break;
		case SMART_LIFE:                         fileName = _T("Life");						break;
		default: throw std::exception{ "Unknown attribute id" };
	}

	auto filePath = PathManager::GetInstance().SmartDir()
		+ (*m_dataSource)[i].ModelSerial
		+ L"\\" 
		+ fileName
		+ L".csv";
	return std::wifstream{ filePath.data()};
}

GraphData& GraphData::GetInstance()
{
	static GraphData s_instance;
	return s_instance;
}

time_t GraphDataUtil::GetTimeT(CString time)
{
	CString token;
	int currentPosition = 0;
	int index = 0;
	tm t = { 0 };

	token = time.Tokenize(_T(" :/"), currentPosition);
	while (token != _T(""))
	{
		switch (index)
		{
		case 0:
			t.tm_year = _ttoi(token) - 1900;
			break;
		case 1:
			t.tm_mon = _ttoi(token) - 1;
			break;
		case 2:
			t.tm_mday = _ttoi(token);
			break;
		case 3:
			t.tm_hour = _ttoi(token);
			break;
		case 4:
			t.tm_min = _ttoi(token);
			break;
		case 5:
			t.tm_sec = _ttoi(token);
			break;
		default:
			break;
		}
		token = time.Tokenize(_T(" :/"), currentPosition);
		index++;
	}

	return mktime(&t);
}

uint32_t GraphDataUtil::GetValue(CString line)
{
	return _tstoi(line);
}

CString GraphDataUtil::GetModelSerial(CString const model, CString const serialNumber)
{
	CString modelSerial;
	modelSerial = model + serialNumber;
	modelSerial.Replace(_T("\\"), _T(""));
	modelSerial.Replace(_T("/"), _T(""));
	modelSerial.Replace(_T(":"), _T(""));
	modelSerial.Replace(_T("*"), _T(""));
	modelSerial.Replace(_T("?"), _T(""));
	modelSerial.Replace(_T("\""), _T(""));
	modelSerial.Replace(_T("<"), _T(""));
	modelSerial.Replace(_T(">"), _T(""));
	modelSerial.Replace(_T("|"), _T(""));

	return modelSerial;
}
