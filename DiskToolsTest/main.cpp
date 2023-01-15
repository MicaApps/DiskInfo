#include "pch.h"
#include <iostream>
using namespace winrt;
using namespace Windows::Foundation;

int main()
{
	winrt::DiskInfoLibWinRT::Class obj;
	auto firmware = obj.Info();
	std::wcout << firmware.Size() << '\n';
}
