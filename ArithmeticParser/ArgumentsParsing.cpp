#include <algorithm>
#include <map>
#include <exception>
#include <string>
#include <iostream>
#include <sstream>
#include <set>

#include "ArgumentsParsing.h"
#include "CmdOption.h"

namespace arithmetic_parser
{
	std::vector<OptionData> TryGetOptions(const std::string& argument);
	bool CheckForFullOption(std::vector<OptionData>& parsed_options, const std::string& argument);
	bool CheckForShortOptions(std::vector<OptionData>& parsed_options, const std::string& argument);
	std::vector<std::string> GetArguments(int argc, char* argv[], size_t current_index, const OptionData& option_data, std::vector<bool>& used);
	void BuildExpressionFromAllArguments(int argc, char* argv[], std::map<CmdOption, OptionInput>& option_inputs);
	void TryBuildExpressionFromUnused(int argc, char* argv[], std::map<CmdOption, OptionInput>& option_inputs, std::vector<bool>& used);

	void ParseArguments(const int argc, char* argv[], std::map<CmdOption, OptionInput>& option_inputs)
	{
		std::vector<bool> used(argc, false);

		for (size_t i = 1; i < argc; ++i)
		{
			auto current_argument = std::string(argv[i]);
			std::transform(current_argument.begin(), current_argument.end(), current_argument.begin(), std::tolower);

			auto parsed_options = TryGetOptions(current_argument);

			if (!parsed_options.empty())
			{
				used[i] = true;

				for (const auto& option : parsed_options)
				{
					auto option_arguments = GetArguments(argc, argv, i, option, used);
					i += option.arguments_count;

					OptionInput option_input{ option, option_arguments };

					option_inputs.insert({ option.command_line_option, option_input });
				}
			}
		}

		if (option_inputs.empty())
			BuildExpressionFromAllArguments(argc, argv, option_inputs);
		else if (option_inputs.find(CmdOption::Expression) == option_inputs.end())
			TryBuildExpressionFromUnused(argc, argv, option_inputs, used);
	}

	std::vector<std::string> GetArguments(const int argc, char* argv[], const size_t current_index, const OptionData& option_data, std::vector<bool>& used)
	{
		std::vector<std::string> arguments{};

		for (size_t i = 0; i < option_data.arguments_count; ++i)
		{
			auto index = current_index + i + 1;

			if (index < argc)
			{
				used[index] = true;
				arguments.emplace_back(argv[index]);
			}
			else
			{
				std::stringstream stream;
				stream << "Arguments count error for option type = " << option_data.full_name
					<< ". Expected " << option_data.arguments_count << "arguments, but found only " << i - 1;

				throw std::runtime_error(stream.str());
			}
		}

		return arguments;
	}

	bool CheckForFullOption(std::vector<OptionData>& parsed_options, const std::string& argument)
	{
		if (argument.size() < 3)
			return false;

		if (argument.find("--") != 0)
			return false;

		auto cut_argument = argument.substr(2, argument.size() - 2);

		for (const auto& pair : available_options_map)
		{
			auto option_data = pair.second;

			if (cut_argument == option_data.full_name)
			{
				parsed_options.push_back(option_data);
				return true;
			}
		}

		return false;
	}

	bool CheckForShortOptions(std::vector<OptionData>& parsed_options, const std::string& argument)
	{
		if (argument.size() < 2)
			return false;

		if (argument[0] != '-')
			return false;

		std::vector<OptionData> local_parser_options{};

		for (size_t i = 1; i < argument.size(); ++i)
		{
			auto current_symbol = argument[i];

			auto was_any_option = false;

			for (const auto& pair : available_options_map)
			{
				auto option_data = pair.second;

				if (current_symbol == option_data.short_name)
				{
					if (std::find(local_parser_options.begin(), local_parser_options.end(), option_data) == local_parser_options.end())
					{
						was_any_option = true;
						local_parser_options.push_back(option_data);
						break;
					}
					else
					{
						std::ostringstream stream;
						stream << "Option " << option_data.full_name << " have been already declared. Only single declaration is permitted for option.";
						throw std::runtime_error(stream.str());
					}
				}
			}

			if (!was_any_option)
			{
				return false;
			}
		}

		parsed_options.insert(parsed_options.end(), local_parser_options.begin(), local_parser_options.end());
		return true;
	}

	std::vector<OptionData> TryGetOptions(const std::string& argument)
	{
		std::vector<OptionData> parsed_options{};

		if (CheckForFullOption(parsed_options, argument))
			return parsed_options;

		if (CheckForShortOptions(parsed_options, argument))
			return parsed_options;

		return parsed_options;
	}

	void TryBuildExpressionFromUnused(const int argc, char* argv[], std::map<CmdOption, OptionInput>& option_inputs, std::vector<bool>& used)
	{
		bool startFound = false;
		size_t unusedStart = 0;
		size_t unusedEnd = argc;

		for (size_t i = 1; i < argc; ++i)
		{
			if (!used[i] && !startFound)
			{
				startFound = true;
				unusedStart = i;
			}

			if (used[i] && startFound)
			{
				unusedEnd = i + 1;
				break;
			}
		}

		if (unusedStart > 0)
		{
			std::string input;

			for (size_t i = unusedStart; i < unusedEnd; ++i)
			{
				input.append(argv[i]);
				input.append(" ");
			}

			OptionInput option_input{
				available_options_map.at(CmdOption::Expression),
				{input}
			};

			option_inputs.emplace(CmdOption::Expression, option_input);
		}
	}

	void BuildExpressionFromAllArguments(const int argc, char* argv[], std::map<CmdOption, OptionInput>& option_inputs)
	{
		if (argc == 1)
			return;

		std::string input;

		for (size_t i = 1; i < argc; ++i)
		{
			input.append(argv[i]);
			input.append(" ");
		}

		option_inputs[CmdOption::Expression] = OptionInput
		{
			available_options_map.at(CmdOption::Expression),
			{input }
		};
	}

	bool OptionData::operator<(const OptionData& od) const
	{
		return short_name < od.short_name;
	}

	bool OptionData::operator==(const OptionData& od) const
	{
		return command_line_option == od.command_line_option;
	}
}