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
	bool TryParseOperator(const std::string_view& input, const size_t current_index, size_t& shifted_index, std::shared_ptr<Token>& token)
	{
		const char c = input[current_index];

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
		case '^':
		{
			token = std::make_shared<Token>(BuiltinFunctionType::Power);
			break;
		}
		default:
			return false;
		}

		shifted_index = current_index + 1;

		return true;
	}

	bool TryParseParentheses(const std::string_view& input, const size_t current_index, size_t& shifted_index, std::shared_ptr<Token>& token)
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
		case '|':
			token = std::make_shared<Token>(ParenthesisType::Straight, ParenthesisSide::None);
			break;
		default:
			return false;
		}

		shifted_index = current_index + 1;

		return true;
	}

	bool TryParseSpecialSymbols(const std::string_view& input, const size_t current_index, size_t& shifted_index, std::shared_ptr<Token>& token)
	{
		char c = input[current_index];

		switch (c)
		{
		case ',':
			token = std::make_shared<Token>(TokenType::Comma);
			break;

		default:
			return false;
		}

		shifted_index = current_index + 1;

		return true;
	}

	bool TryParseConstant(std::string_view input, const size_t current_index, size_t& shifted_index, std::shared_ptr<Token>& token)
	{
		const std::map<std::string, ConstantType> constants{
			{"PI", ConstantType::PI},
			{"e", ConstantType::Exponent}
		};

		input.remove_prefix(current_index);

		for (const auto& [name, constant] : constants)
		{
			if (input.find(name) == 0)
			{
				shifted_index = current_index + name.length();
				token = std::make_shared<Token>(constant);
				return true;
			}
		}

		return false;
	}

	bool TryParseVariable(const std::string_view& input, const size_t current_index, size_t& shifted_index, std::shared_ptr<Token>& token)
	{


		return false;
	}

	bool TryParseNumber(const std::string_view& input, const size_t current_index, size_t& shifted_index, std::shared_ptr<Token>& token)
	{
		std::string numberString;

		bool delimiterWas = false;

		for (size_t i = current_index; i < input.size(); i++)
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

		if (numberString.size() == 0)
			return false;

		if (numberString.size() == 1 && delimiterWas)
		{
			throw std::exception("Number cannot consist of only decimal delimiter.");
		}

		double value = std::stod(numberString);
		token = std::make_shared<Token>(Token(value));
		shifted_index = current_index + numberString.size();

		return true;
	}

	bool TryParseBuiltinFunction(std::string_view input, const size_t current_index, size_t& shifted_index, std::shared_ptr<Token>& token)
	{
		const std::map<std::string, BuiltinFunctionType> functions{
			{"sin", BuiltinFunctionType::Sinus},
			{"cos", BuiltinFunctionType::Cosine},
			{"tg", BuiltinFunctionType::Tangent},
			{"ctg", BuiltinFunctionType::Cotangent},
			{"asin", BuiltinFunctionType::Arcsine},
			{"acos", BuiltinFunctionType::Arccosine},
			{"atg", BuiltinFunctionType::Arctangent},
			{"actg", BuiltinFunctionType::Arccotangent},
			{"ln", BuiltinFunctionType::NaturalLogarithm},
			{"lg", BuiltinFunctionType::DecimalLogarithm},
			{"log", BuiltinFunctionType::LogarithmArbitraryBasis}
		};

		input.remove_prefix(current_index);

		for (const auto& [name, function] : functions)
		{
			if (input.find(name) == 0)
			{
				shifted_index = current_index + name.length();
				token = std::make_shared<Token>(function);
				return true;
			}
		}

		return false;
	}

	std::vector<std::shared_ptr<Token>> GetTokens(const std::string_view& input)
	{
		std::vector<std::shared_ptr<Token>> tokens;

		for (size_t i = 0; i < input.size();)
		{
			if (isblank(input[i]))
			{
				i++;
				continue;
			}

			std::shared_ptr<Token> token;

			const auto parsed_successfully =
				TryParseOperator(input, i, i, token) ||
				TryParseNumber(input, i, i, token) ||
				TryParseConstant(input, i, i, token) ||
				TryParseVariable(input, i, i, token) ||
				TryParseParentheses(input, i, i, token) ||
				TryParseBuiltinFunction(input, i, i, token) ||
				TryParseSpecialSymbols(input, i, i, token)
				;

			if (parsed_successfully)
			{
				tokens.push_back(token);
			}
			else
			{
				std::ostringstream string_stream;
				string_stream << "Not recognized expression starting from symbol " << input[i] << " at position " << i << ".";
				throw std::runtime_error(string_stream.str());
			}
		}

		return tokens;
	}
}