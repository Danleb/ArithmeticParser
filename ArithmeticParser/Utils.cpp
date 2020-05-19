#include <iostream>
#include <fstream>
#include <Windows.h>
#include <sstream>
#include <string>
#include <cerrno>
#include <WinUser.h>

#include "Utils.h"
#include "Version.h"
#include "resource.h"

namespace arithmetic_parser
{
	bool FindOption(const std::map<CmdOption, OptionInput>& option_inputs, const CmdOption option_to_find, OptionInput& option)
	{
		const auto search = option_inputs.find(option_to_find);

		if (search != option_inputs.end())
		{
			option = search->second;
			return true;
		}

		return false;
	}

	void ShowVersion()
	{
		std::cout << "Arithmetic Parser v" << MAJOR_VERSION << "." << MINOR_VERSION << "." << BUILD_VERSION << std::endl;
		std::cout << "Copyright (C) " << YEAR << " " << AUTHOR << "." << std::endl;
	}

	void ShowHelp()
	{
		ShowVersion();
		std::cout << std::endl;

		auto resource_id = IDR_TEXT1;
		auto resname = "";
		auto hResource = FindResource(nullptr, MAKEINTRESOURCEW(resource_id), L"TEXT");
		auto hMemory = LoadResource(nullptr, hResource);

		std::size_t size_bytes = 0;
		void* ptr = nullptr;

		size_bytes = SizeofResource(nullptr, hResource);
		ptr = LockResource(hMemory);
		
		std::string_view dst;
		if (ptr != nullptr)
			dst = std::string_view(reinterpret_cast<char*>(ptr), size_bytes);

		std::cout << dst;
	}

	bool SaveResult(const std::string& file_path, double result) noexcept
	{
		try
		{
			std::ofstream save_stream;
			save_stream.open(file_path.c_str(), std::ios::out | std::ios::app);
			save_stream << result << std::endl;
			save_stream.close();

			return true;
		}
		catch (std::exception& exception)
		{
			std::cout << exception.what() << std::endl;
			return false;
		}
	}

	void CopyToTheClipboard(const double result)
	{
		auto str = std::to_string(result);

		HWND hwnd = GetDesktopWindow();
		OpenClipboard(hwnd);
		EmptyClipboard();
		HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, str.size());
		if (!hg)
		{
			CloseClipboard();
			return;
		}
		memcpy(GlobalLock(hg), str.c_str(), str.size());
		GlobalUnlock(hg);
		SetClipboardData(CF_TEXT, hg);
		CloseClipboard();
		GlobalFree(hg);
	}

	bool LoadExpression(const std::string& file_path, std::string& input)
	{
		std::ifstream load_stream;
		load_stream.open(file_path, std::ios::in);

		if (!load_stream)
			return false;

		std::ostringstream contents;
		contents << load_stream.rdbuf();
		load_stream.close();
		input = contents.str();

		return true;
	}

	void RemoveCharactersFromString(std::string& s, const char* characters)
	{
		for (size_t i = 0; i < strlen(characters); ++i)
		{
			s.erase(std::remove(s.begin(), s.end(), characters[i]), s.end());
		}
	}
}
