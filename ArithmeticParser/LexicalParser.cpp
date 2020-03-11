#include<vector>
#include<exception>

#include"LexicalParser.h"

namespace ArithmeticParser
{
	Token TryToParseNumber(std::string s, int index)
	{
		std::string numberString;

		bool delimiterWas = false;

		while (true)
		{
			switch (s[index])
			{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				numberString += s[index];
				break;

			case '.':
			case ',':
				if (delimiterWas)
				{
					throw new std::exception("Delimiter in number already was.");
				}

				delimiterWas = true;
				numberString += s[index];

				break;

			default:
				Token
				
				break;
			}
		}
	}

	std::vector<Token> GetTokens(std::string s)
	{
		std::vector<Token> tokens;

		for (size_t i = 0; i < s.size(); i++)
		{
			switch (s[i])
			{
			case '+':
				Token t(TokenType::Operator, OperatorType::Addition);
				tokens.push_back(t);
				break;
			case '-':
				Token t(TokenType::Operator, OperatorType::Subtraction);
				tokens.push_back(t);
				break;
			case '*':
				Token t(TokenType::Operator, OperatorType::Multiplication);
				tokens.push_back(t);
				break;
			case '/':
				Token t(TokenType::Operator, OperatorType::Division);
				tokens.push_back(t);
				break;

			default:
				if (true)
				{
					throw new std::exception("Not recognized symbol " + s[i]);
				}

				auto token = TryToParseNumber(s, i);
				tokens.push_back(token);
				break;
			}
		}

		return tokens;
	}
}