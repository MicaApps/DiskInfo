#include "pch.h"
#include <iostream>
using namespace winrt;
using namespace Windows::Foundation;

int main()
{
	winrt::DiskInfoLibWinRT::Class obj;
	auto firmware = obj.Firmware();
	std::wcout << firmware.data() << '\n';
}
