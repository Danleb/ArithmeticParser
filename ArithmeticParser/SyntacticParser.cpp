#include<memory>
#include<vector>

#include"Token.h"
#include"LexicalParser.h"
#include"SyntacticParser.h"
#include"TokenType.h"
#include"OperatorType.h"

namespace ArithmeticParser
{
	std::unique_ptr<Node> ParseFunction(std::string s)
	{
		std::vector<Token> tokens = GetTokens(s);
		std::unique_ptr<Node> node = ParseFunction(tokens);
		return node;
	}

	std::unique_ptr<Node> ParseFunction(std::vector<Token> tokens)
	{


		for (size_t i = 0; i < tokens.size(); i++)
		{
			Token currentToken = tokens[i];

			if (currentToken.tokenType == TokenType::Operator)
			{
				if (currentToken.operatorType == OperatorType::Addition || 
					currentToken.operatorType == OperatorType::Subtraction)
				{

				}
				else if(currentToken.operatorType == OperatorType::Multiplication ||
					currentToken.operatorType == OperatorType::Division)
				{

				}
			}
		}

		return nullptr;
	}
}