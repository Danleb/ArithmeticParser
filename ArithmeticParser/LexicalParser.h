#pragma once
#ifndef LEXICAL_PARSER_H
#define LEXICAL_PARSER_H

#include<vector>
#include<string>

#include"Token.h"

namespace ArithmeticParser
{
	std::vector<Token> GetTokens(std::string);
}

#endif // !LEXICAL_PARSER_H