#include <vector>
#include <exception>
#include <cctype>
#include <memory>
#include <sstream>

#include "BuiltinFunctionType.h"
#include "LexicalParser.h"
#include "ParenthesisSide.h"
#include "ParenthesisType.h"
#include "Token.h"
#include "Utils.h"

namespace arithmetic_parser
{
	bool TryToParseOperator(const std::string input, const size_t index, size_t& shiftedIndex, std::shared_ptr<Token>& token)
	{
		const char c = input[index];

		switch (c)
		{
		case '+':
		{
			token = std::make_shared<Token>(BuiltinFunctionType::Addition);
			break;
		}
		case '-':
		{
			token = std::make_shared<Token>(BuiltinFunctionType::Subtraction);
			break;
		}
		case '*':
		{
			token = std::make_shared<Token>(BuiltinFunctionType::Multiplication);
			break;
		}
		case '/':
		{
			token = std::make_shared<Token>(BuiltinFunctionType::Division);
			break;
		}
		default: return false;
		}

		shiftedIndex = index + 1;

		return true;
	}

	bool TryToParseParentheses(const std::string& input, const size_t current_index, size_t& shiftedIndex, std::shared_ptr<Token>& token)
	{
		const char c = input[current_index];

		switch (c)
		{
		case '(': {
			token = std::make_shared<Token>(ParenthesisType::Round, ParenthesisSide::Opening);
			break;
		}
		case ')': {
			token = std::make_shared<Token>(ParenthesisType::Round, ParenthesisSide::Closing);
			break;
		}
		case '[': {
			token = std::make_shared<Token>(ParenthesisType::Square, ParenthesisSide::Opening);
			break;
		}
		case ']': {
			token = std::make_shared<Token>(ParenthesisType::Square, ParenthesisSide::Closing);
			break;
		}
		case '{': {
			token = std::make_shared<Token>(ParenthesisType::Curly, ParenthesisSide::Opening);
			break;
		}
		case '}': {
			token = std::make_shared<Token>(ParenthesisType::Curly, ParenthesisSide::Closing);
			break;
		}

		default: return false;
		}

		shiftedIndex = current_index + 1;

		return true;
	}

	bool TryParseSpecialSymbols(const std::string& input, const size_t current_index, size_t& shiftedIndex, std::shared_ptr<Token>& token)
	{
		char c = input[current_index];

		switch (c)
		{
		case '|':

			break;

		case ',':

			break;

		default:
			return false;
		}

		return false;
	}

	bool TryToParseNumber(const std::string& input, const size_t index, size_t& shiftedIndex, std::shared_ptr<Token>& token)
	{
		std::string numberString;

		bool delimiterWas = false;

		for (size_t i = index; i < input.size(); i++)
		{
			char c = input[i];

			if (isdigit(c))
			{
				numberString += c;
				continue;
			}
			else if (c == '.')
			{
				if (delimiterWas)
				{
					throw std::exception("Delimiter in number already was.");
				}

				delimiterWas = true;
				numberString += c;
			}
			else
				break;
		}

		if (numberString.size() == 1 && delimiterWas)
		{
			throw std::exception("Number cannot consist of only decimal delimiter.");
		}

		double value = std::stod(numberString);
		token = std::make_shared<Token>(Token(value));
		shiftedIndex = index + numberString.size();

		return true;
	}

	bool TryToParseBuiltinFunction(const std::string& input, const size_t index, size_t& shiftedIndex, std::shared_ptr<Token>& token)
	{


		return false;
	}

	std::vector<std::shared_ptr<Token>> GetTokens(std::string input)
	{
		std::vector<std::shared_ptr<Token>> tokens;

		//std::shared_ptr<Token> previousToken = nullptr;

		for (size_t i = 0; i < input.size();)
		{
			std::shared_ptr<Token> token;

			const auto parsedSuccessfully =
				TryToParseOperator(input, i, i, token) ||
				TryToParseNumber(input, i, i, token) ||
				TryToParseParentheses(input, i, i, token) ||
				TryToParseBuiltinFunction(input, i, i, token)
				;

			if (parsedSuccessfully)
			{
				tokens.push_back(token);
			}
			else if (input[i] == ' ')
			{
				i++;
			}
			else
			{
				std::ostringstream string_stream;
				string_stream << "Not recognized expression starting from symbol " << input[i] << " at position " << i << ".";
				throw new std::runtime_error(string_stream.str());
			}
		}

		return tokens;
	}
}