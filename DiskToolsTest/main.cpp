#include "pch.h"
#include <iostream>
#include <span>
using namespace winrt;
using namespace Windows::Foundation;

int main()
{
	winrt::DiskInfoLibWinRT::Class obj;
	auto firmware = obj.Info();
	auto info1 = firmware.GetAt(2);

	for (auto const& obj : info1.Attributes())
	{
		auto attr = obj.as<winrt::DiskInfoLibWinRT::SmartAttribute>();
		std::wcout << attr.Id.data() << "\t" << attr.Name.data() << '\t' << attr.RawValue.data() << '\n';
	}
	info1.Update(2);
	for (auto const& obj : info1.Attributes())
	{
		auto attr = obj.as<winrt::DiskInfoLibWinRT::SmartAttribute>();
		std::wcout << attr.Id.data() << "\t" << attr.Name.data() << '\t' << attr.RawValue.data() << '\n';
	}
}
