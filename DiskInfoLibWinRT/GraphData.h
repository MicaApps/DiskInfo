#pragma once
#include "pch2.h"
#include "AtaSmart.h"
#include <fstream>

namespace GraphDataUtil
{
	time_t GetTimeT(CString line);

	uint32_t GetValue(CString line);

	CString GetModelSerial(CString const model, CString const serialNumber);
}

class GraphData
{
public:
	using DataSourceType = decltype(CAtaSmart::get_instance().vars);
private:
	DataSourceType const* m_dataSource{};
	GraphData() = default;
public:
	constexpr static inline auto SMART_TEMPERATURE = 300;
	constexpr static inline auto SMART_POWER_ON_HOURS = 301;
	constexpr static inline auto SMART_POWER_ON_COUNT = 302;
	constexpr static inline auto SMART_REALLOCATED_SECTORS_COUNT = 303;
	constexpr static inline auto SMART_REALLOCATED_EVENT_COUNT = 304;
	constexpr static inline auto SMART_CURRENT_PENDING_SECTOR_COUNT = 305;
	constexpr static inline auto SMART_UNCORRECTABLE_SECTOR_COUNT = 306;
	constexpr static inline auto SMART_HOST_WRITES = 307;
	constexpr static inline auto SMART_HOST_READS = 308;
	constexpr static inline auto SMART_NAND_WRITES = 309;
	constexpr static inline auto SMART_NAND_ERASED = 310;
	constexpr static inline auto SMART_WEAR_LEVELING_COUNT = 311;
	constexpr static inline auto SMART_LIFE = 312;

	void SetDataSource(DataSourceType const& source);

	void SaveSmartInfo(unsigned long i);
	
	std::wifstream GetDataFile(DWORD attributeId, unsigned long i);


	static GraphData& GetInstance();
};

