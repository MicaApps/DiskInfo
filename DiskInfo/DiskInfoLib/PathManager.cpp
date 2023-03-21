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
	static winrt::hstring result{ CurrentExeDir() + LR"(\Assets\CrystalDiskInfoLangFiles\English.lang)" };
	return result;
}

static auto ToLower(std::string_view original)
{
	std::string ret;
	std::ranges::transform(original, std::back_inserter(ret), [](int c) {return std::tolower(c); });
	return ret;
}

static auto ToLower(std::wstring_view original)
{
	std::wstring ret;
	std::ranges::transform(original, std::back_inserter(ret), [](int c) {return std::tolower(c); });
	return ret;
}

winrt::hstring const& PathManager::CurrentLangPath()
{
	static winrt::hstring result{
		[]
		{
			/*
				BCP 47 <===============> Language file in Assets/CrystalDiskInfoLangFiles (without extension), eg:
				en-us						English
				zh-cn						Simplified
			*/
			static std::unordered_map<std::wstring_view, std::wstring_view> languageMap
			{
				{L"en-us", L"English"},
				{L"en-uk", L"English"},
				{L"zh-cn", L"Simplified"},
				{L"zh-hk", L"Traditional"},
			};
			auto const currentLanguageCode = winrt::Windows::System::UserProfile::GlobalizationPreferences::Languages().GetAt(0);
			
			wchar_t buf[LOCALE_NAME_MAX_LENGTH]{};
			ResolveLocaleName(currentLanguageCode.data(), buf, std::size(buf));

			std::wstring const currentLanguageCodeLower = ToLower(std::wstring_view{ buf });
			auto const iter = languageMap.find(currentLanguageCodeLower);
			if (iter != languageMap.end())
				return winrt::hstring{ std::format(LR"({}\Assets\CrystalDiskInfoLangFiles\{}.lang)", CurrentExeDir(), iter->second) };
			
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
