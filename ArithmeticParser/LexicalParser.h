#pragma once
#ifndef LEXICAL_PARSER_H
#define LEXICAL_PARSER_H

#include <vector>
#include <string>

#include "Token.h"

namespace arithmetic_parser
{
	std::vector<std::shared_ptr<Token>> GetTokens(std::string input);
}

#endif // !LEXICAL_PARSER_H