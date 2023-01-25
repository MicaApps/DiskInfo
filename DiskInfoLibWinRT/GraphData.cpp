#include "GraphData.h"
#include "PathManager.h"

void GraphData::SetDataSource(DataSourceType const& source)
{
	m_dataSource = &source;
}

void GraphData::SaveSmartInfo(unsigned long i)
{
}

std::wifstream GraphData::GetDataFile(DWORD attributeId, unsigned long i)
{
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

	auto filePath = PathManager::SmartDir() 
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
