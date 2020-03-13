#pragma once
#ifndef SYNTACTIC_PARSER_H
#define SYNTACTIC_PARSER_H

#include<string>
#include<vector>

#include"Node.h"
#include"Token.h"

namespace ArithmeticParser
{
    std::unique_ptr<Node> ParseFunction(std::string s);
    std::unique_ptr<Node> ParseFunction(std::vector<Token> tokens);
}

#endif // !SYNTACTIC_PARSER_H