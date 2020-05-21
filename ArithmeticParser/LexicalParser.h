#pragma once

#include <vector>
#include <string>

#include "Token.h"

namespace arithmetic_parser
{
	std::vector<std::shared_ptr<Token>> GetTokens(std::string input);
}