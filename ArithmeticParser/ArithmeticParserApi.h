#pragma once
#ifndef ARITHMETIC_PARSER_API_H
#define ARITHMETIC_PARSER_API_H

#include <map>

#include "CmdOption.h"
#include "ErrorCode.h"
#include "ArgumentsParsing.h"

namespace arithmetic_parser
{
	ErrorCode Process(const int argc, char* argv[]);
	ErrorCode Process(const std::map<CmdOption, OptionInput>& option_inputs);

	__declspec(dllexport) ErrorCode Process(const std::string& input, double& result);
}

#endif // ARITHMETIC_PARSER_API_H