#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <map>

#include "CmdOption.h"
#include "ArgumentsParsing.h"

namespace arithmetic_parser
{
	bool FindOption(const std::map<CmdOption, OptionInput>&, CmdOption option_to_find, OptionInput& option);
	void RemoveCharactersFromString(std::string& s, const char* characters);

	void ShowVersion();
	void ShowHelp();
	bool SaveResult(const std::string& file_path, double result) noexcept;
	void CopyToTheClipboard(double);
	bool LoadExpression(const std::string& file_path,  std::string& input);
	bool GetInput(const std::map<CmdOption, OptionInput>& option_inputs, std::string& input);
}

#endif // !UTILS_H