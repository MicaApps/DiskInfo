#include "PathManager.h"
#include <winrt/Windows.Storage.h>
#include <Windows.h>
#include <ShlObj_core.h>

winrt::hstring PathManager::SmartDir()
{
	try
	{
		auto currentApplicationData = winrt::Windows::Storage::ApplicationData::Current();
		if (currentApplicationData)
			return currentApplicationData.LocalFolder().Path();
	}
	catch (...)
	{
		wchar_t path[MAX_PATH]{};
		SHGetSpecialFolderPath(NULL, path, CSIDL_DESKTOP, true); //create if not exist
		return winrt::hstring{ path } + LR"(\Diskinfo\smart\)";
	}
}
