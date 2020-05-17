#pragma once
#ifndef ARGUMENTS_PARSING_H
#define ARGUMENTS_PARSING_H

#include <map>
#include <vector>
#include <string>

#include "CommandLineOption.h"

namespace arithmetic_parser
{
	struct OptionData
	{
		CmdOption command_line_option;
		char short_name;
		std::string full_name;
		size_t arguments_count;

		bool operator<(const OptionData& od)const;
	};

	struct OptionInput
	{
		OptionData option_data;
		std::vector<std::string> arguments;
	};

	/*const std::vector<OptionData> available_options{
		{ CommandLineOption::Help, "h", "help", 0 },
		{ CommandLineOption::Version, "v", "version", 0 },
		{ CommandLineOption::Clipboard, "c", "clipboard", 0 },
		{ CommandLineOption::File, "f", "file", 1 },
		{ CommandLineOption::Expression, "e", "expression", 1 },
		{ CommandLineOption::Save, "s", "save", 1 },
	};*/

	const std::map<CmdOption, OptionData>available_options_map{
		{{CmdOption::Help}, { CmdOption::Help, 'h', "help", 0 }},
		{{CmdOption::Version}, { CmdOption::Version, 'v', "version", 0 }},
		{{CmdOption::Clipboard}, { CmdOption::Clipboard, 'c', "clipboard", 0 }},
		{{CmdOption::File}, { CmdOption::File, 'f', "file", 1 }},
		{{CmdOption::Expression}, { CmdOption::Expression, 'e', "expression", 1 }},
		{{CmdOption::Save}, { CmdOption::Save, 's', "save", 1 }},
		{{CmdOption::Verbose}, { CmdOption::Verbose, 'r', "verbose", 0 }}
	};

	void ParseArguments(const int argc, char* argv[], std::map<CmdOption, OptionInput>& option_inputs);
}

#endif // !ARGUMENTS_PARSING_H