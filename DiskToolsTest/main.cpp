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

	for (auto const& attr : info1.Attributes())
	{
		std::wcout << attr.Id << "\t" << attr.Name.data() << '\t' << attr.RawValue.data() << '\n';
	}

}
