#pragma once
#ifndef SYNTACTIC_PARSER_H
#define SYNTACTIC_PARSER_H

#include <string>
#include <vector>

#include "Node.h"
#include "Token.h"

namespace arithmetic_parser
{
    std::unique_ptr<Node> ParseFunction(std::string);
    std::unique_ptr<Node> ParseFunction(std::vector<Token> tokens);
    std::unique_ptr<Node> ParseFunction(std::vector<Token> tokens, int start, int end);
}

#endif // !SYNTACTIC_PARSER_H