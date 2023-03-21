#pragma once
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Storage.h>
class PathManager
{
	winrt::Windows::Storage::ApplicationData m_appData{ nullptr };

	PathManager();

	static std::wstring const& CurrentExeDir();
public:
	winrt::hstring SmartDir();
	static winrt::hstring const& DefaultLangPath();
	static winrt::hstring const& CurrentLangPath();

	static PathManager& GetInstance();
};

