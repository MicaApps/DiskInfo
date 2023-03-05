#include "PathManager.h"
#include <winrt/Windows.System.UserProfile.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <Windows.h>
#include <ShlObj_core.h>
#include <filesystem>
#include <format>
#include <winrt/Windows.Globalization.h>
#include <ranges>

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

std::wstring const& PathManager::CurrentExeDir()
{
	static std::wstring const path{ [] {
		TCHAR currentExePath[MAX_PATH]{};
		GetModuleFileName(NULL, currentExePath, MAX_PATH);
		std::wstring_view view{ currentExePath };
		view = view.substr(0, view.rfind(L"\\"));
		return std::wstring{ view };
	}() };
	return path;
}

winrt::hstring PathManager::SmartDir()
{
	if (m_appData)
		return m_appData.LocalFolder().Path() + L"\\";

	wchar_t path[MAX_PATH]{};
	SHGetSpecialFolderPath(NULL, path, CSIDL_DESKTOP, true); //create if not exist
	return winrt::hstring{ path } + LR"(\Diskinfo\smart\)";
}

winrt::hstring const& PathManager::DefaultLangPath()
{
	static winrt::hstring result{ CurrentExeDir() + LR"(\Assets\CrystalDiskInfoLangFiles\Simplified Chinese.lang)" };
	return result;
}

static auto ToLower(std::string_view original)
{
	std::string ret;
	std::ranges::transform(original, std::back_inserter(ret), [](int c) {return std::tolower(c); });
	return ret;
}

winrt::hstring const& PathManager::CurrentLangPath()
{
	static winrt::hstring result{
		[]
		{
			/*
				Match the current Display Language for "best" effort, eg:
					currentLanaguageName					File
					English (United State)					English
					Chinese (Simpified, China)				Simplified
					Chinese (Traditional, Hong Kong SAR)	Traditional
			*/
			auto const currentLanguageCode = winrt::Windows::System::UserProfile::GlobalizationPreferences::Languages().GetAt(0);
			auto const currentLanguageName = winrt::to_string(winrt::Windows::Globalization::Language{ currentLanguageCode }.DisplayName());
			
			std::string const currentLanguageNameLower = ToLower(currentLanguageName);
			for (auto iter : std::filesystem::directory_iterator{ CurrentExeDir() + LR"(\Assets\CrystalDiskInfoLangFiles)" })
			{
				auto path = iter.path();
				auto fileName = path.stem().string();
				if (currentLanguageNameLower.find(ToLower(fileName)) != std::string::npos)
					return winrt::to_hstring(path.string());
			}
			return DefaultLangPath();
		}()
	};
	return result;
}



PathManager& PathManager::GetInstance()
{
	static PathManager s_instance;
	return s_instance;
}
