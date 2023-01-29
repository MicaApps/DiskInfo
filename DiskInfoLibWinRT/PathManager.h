#pragma once
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Storage.h>
class PathManager
{
	winrt::Windows::Storage::ApplicationData m_appData{ nullptr };

	PathManager();
public:
	winrt::hstring SmartDir();
	winrt::hstring DefaultLangPath();
	winrt::hstring CurrentLangPath();

	static PathManager& GetInstance();
};

