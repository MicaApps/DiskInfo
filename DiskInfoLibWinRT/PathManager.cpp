#include "PathManager.h"

#include <Windows.h>
#include <ShlObj_core.h>

PathManager::PathManager()
{
	try
	{
		m_appData = winrt::Windows::Storage::ApplicationData::Current();
	}
	catch (...)
	{
		m_appData = nullptr;
	}
}

winrt::hstring PathManager::SmartDir()
{
	if (m_appData)
		return m_appData.LocalFolder().Path() + L"\\";

	wchar_t path[MAX_PATH]{};
	SHGetSpecialFolderPath(NULL, path, CSIDL_DESKTOP, true); //create if not exist
	return winrt::hstring{ path } + LR"(\Diskinfo\smart\)";
}

winrt::hstring PathManager::DefaultLangPath()
{
	if (m_appData)
		return m_appData.LocalFolder().Path() + LR"(\Assets\English.lang)";
	return LR"(C:\Users\Peter\Desktop\diskInfo\DiskTools\DiskTools\Assets\English.lang)";
}

winrt::hstring PathManager::CurrentLangPath()
{
	if (m_appData)
		return m_appData.LocalFolder().Path() + LR"(\Assets\English.lang)";
	return LR"(C:\Users\Peter\Desktop\diskInfo\DiskTools\DiskTools\Assets\English.lang)";
}



PathManager& PathManager::GetInstance()
{
	static PathManager s_instance;
	return s_instance;
}
