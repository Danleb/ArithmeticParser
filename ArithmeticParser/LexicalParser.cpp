#include<vector>
#include<exception>
#include<ctype.h>

#include"Token.h"
#include"LexicalParser.h"
#include"Utils.h"

namespace ArithmeticParser
{
	bool TryToParseOperator(const std::string s, const size_t index, size_t& shiftedIndex, Token& token)
	{
		char c = s[index];

		switch (c)
		{
		case '+':
		{
			token = Token(OperatorType::Addition);
			break;
		}
		case '-':
		{
			token = Token(OperatorType::Subtraction);
			break;
		}
		case '*':
		{
			token = Token(OperatorType::Multiplication);
			break;
		}
		case '/':
		{
			token = Token(OperatorType::Division);
			break;
		}
		default: return false;
		}

		shiftedIndex = index + 1;

		return true;
	}

	bool TryToParseParentheses(const std::string s, const size_t index, size_t& shiftedIndex, Token& token)
	{
		return false;
	}

	bool TryToParseNumber(const std::string s, const size_t index, size_t& shiftedIndex, Token& token)
	{
		std::string numberString;

		bool delimiterWas = false;

		for (size_t i = index; i < s.size(); i++)
		{
			char c = s[i];

			if (isdigit(c))
			{
				numberString += c;
				continue;
			}
			else if (c == '.' || c == ',')
			{
				if (delimiterWas)
				{
					throw new std::exception("Delimiter in number already was.");
				}

				delimiterWas = true;
				numberString += c;
			}
			else
				break;
		}

		if (numberString.size() == 1 && delimiterWas)
		{
			throw new std::exception("Number cannot consist of only decimal delimiter.");
		}

		double value = std::stod(numberString);
		token = Token(value);
		shiftedIndex = index + numberString.size();

		return true;
	}

	std::vector<Token> GetTokens(std::string s)
	{
		const char charactersToRemove[] = " ";
		RemoveCharactersFromString(s, charactersToRemove);

		std::vector<Token> tokens;

		bool wasNumber = false;

		for (size_t i = 0; i < s.size();)
		{
			Token token;

			bool parsedSuccessfully =
				TryToParseOperator(s, i, i, token) ||
				TryToParseNumber(s, i, i, token);

			if (parsedSuccessfully)
			{
				tokens.push_back(token);
			}
			else
			{
				throw new std::exception("Not recognized expression starting from symbol " + s[i]);
			}
		}

		return tokens;
	}
}