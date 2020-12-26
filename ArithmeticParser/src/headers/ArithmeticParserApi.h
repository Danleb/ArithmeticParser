#pragma once

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