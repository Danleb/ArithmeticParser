#include <memory>
#include <vector>

#include "Token.h"
#include "LexicalParser.h"
#include "SyntacticParser.h"
#include "TokenType.h"
#include "OperatorType.h"

namespace arithmetic_parser
{
	std::unique_ptr<Node> ParseFunction(std::string s)
	{
		auto tokens = GetTokens(s);
		auto node = ParseFunction(tokens);
		return node;
	}

	std::unique_ptr<Node> ParseFunction(std::vector<Token> tokens)
	{
		return ParseFunction(tokens, 0, 1);
	}

	std::unique_ptr<Node> ParseFunction(std::vector<Token> tokens, int start, int end)
	{
		for (size_t i = 0; i < tokens.size(); i++)
		{
			Token currentToken = tokens[i];

			if (currentToken.tokenType == TokenType::Operator)
			{
				if (currentToken.operatorType == OperatorType::Addition ||
					currentToken.operatorType == OperatorType::Subtraction)
				{
					Node node(currentToken);

				}
				else if (currentToken.operatorType == OperatorType::Multiplication ||
					currentToken.operatorType == OperatorType::Division)
				{

				}
			}
		}

		return nullptr;
	}
}