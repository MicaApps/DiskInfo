#include "pch.h"
#include <iostream>
#include <span>
#include <fstream>
using namespace winrt;
using namespace Windows::Foundation;

auto f()
{
	return std::wifstream{ LR"(C:\Users\Peter\Desktop\Diskinfo\smart\KXG60ZNV512G NVMe TOSHIBA 512GB691F71FBF6JN\Temperature.csv)" };
}

int main()
{
	winrt::DiskInfoLibWinRT::Class obj;
	auto firmware = obj.Info();
	auto info1 = firmware.GetAt(0);

	for (auto const& obj : info1.Attributes())
	{
		auto attr = obj.as<winrt::DiskInfoLibWinRT::SmartAttribute>();
		std::wcout << attr.Id.data() << "\t" << attr.Name.data() << '\t' << attr.RawValue.data() << '\n';
	}
	info1.Update();
	for (auto const& obj : info1.Attributes())
	{
		auto attr = obj.as<winrt::DiskInfoLibWinRT::SmartAttribute>();
		std::wcout << attr.Id.data() << "\t" << attr.Name.data() << '\t' << attr.RawValue.data() << '\n';
	}

	auto tData = info1.TemperatureData();
	for (auto const& point : tData)
	{
		auto tPoint = winrt::unbox_value<winrt::DiskInfoLibWinRT::GraphDataPoint>(point);
		std::cout << tPoint.XValue() << '\t' << tPoint.YValue() << '\n';
	}


}
