#include <memory>
#include <vector>
#include <sstream>

#include "BuiltinFunctionType.h"
#include "Token.h"
#include "LexicalParser.h"
#include "SyntacticParser.h"
#include "TokenType.h"

namespace arithmetic_parser
{
	SyntacticParser::SyntacticParser(const std::string input)
	{
		m_input = input;
		m_tokens = GetTokens(m_input);
	}

	SyntacticParser::SyntacticParser(const std::vector<std::shared_ptr<Token>> tokens)
	{
		m_tokens = tokens;
	}

	std::shared_ptr<Node> SyntacticParser::ParseFunction()
	{
		auto node = ParseFunction(0, m_tokens.size() - 1);
		return node;
	}

	std::shared_ptr<Node> SyntacticParser::ParseFunction(size_t start, size_t end)
	{
		//CheckForParenthesisCorrectness(tokens, start, end);

		//if(number
		//if(variable
		if (start == end)
		{
			//check for single number
			auto current_token = m_tokens[start];

			if (current_token->tokenType == TokenType::Number)
			{
				auto current_node = std::make_shared<Node>(current_token);
				return current_node;
			}
			else
			{
				std::ostringstream str;
				str << "Single token unparsed at position " << start << ". TokenType = " << static_cast<int>(current_token->tokenType);
				throw std::runtime_error(str.str());
			}
		}

		//check for inflection points
		for (size_t i = end + 1; i >= start + 1; --i)
		{
			auto index = i - 1;

			auto current_token = m_tokens[index];

			if (current_token->tokenType == TokenType::BuiltinFunction)
			{
				std::shared_ptr<Node> node;

				if (TryInflectionPointAddSubstr(node, current_token, start, end, index))
				{
					return node;
				}

				//mult div
			}
		}

		//check for signed operator
		auto start_token = m_tokens[start];
		if (start_token->tokenType == TokenType::BuiltinFunction)
		{
			if (start_token->builtin_function_type == BuiltinFunctionType::Addition)
			{
				auto nested_node = ParseFunction(start + 1, end);
				return nested_node;
			}
			else if (start_token->builtin_function_type == BuiltinFunctionType::Subtraction)
			{
				auto nested_node = ParseFunction(start + 1, end);
				start_token->builtin_function_type = BuiltinFunctionType::SignMinus;
				auto node = std::make_shared<Node>(start_token);
				node->AddChildNode(nested_node);
				return node;
			}
		}

		return nullptr;
	}

	bool SyntacticParser::TryGetNumber()
	{
		return false;
	}

	bool SyntacticParser::TryInflectionPointMultiplyDivision(std::shared_ptr<Node>& current_node, const std::shared_ptr<Token>& current_token, size_t start, size_t end, size_t index)
	{
		auto inflection_function =
			current_token->builtin_function_type == BuiltinFunctionType::Multiplication ||
			current_token->builtin_function_type == BuiltinFunctionType::Division;

		auto inflection_point =
			inflection_function &&
			index != start &&
			(
				m_tokens[static_cast<size_t>(index - 1)]->tokenType == TokenType::Number
				);
			;

		return false;
	}

	bool SyntacticParser::TryInflectionPointAddSubstr(std::shared_ptr<Node>& current_node, const std::shared_ptr<Token>& current_token, size_t start, size_t end, size_t index)
	{
		auto inflection_function =
			current_token->builtin_function_type == BuiltinFunctionType::Addition ||
			current_token->builtin_function_type == BuiltinFunctionType::Subtraction;

		auto inflection_point =
			inflection_function &&
			index != start &&
			(
				m_tokens[static_cast<size_t>(index - 1)]->tokenType == TokenType::Number
				);

		if (inflection_point)
		{
			current_node = std::make_shared<Node>(Node(current_token));

			auto left_child = ParseFunction(start, static_cast<size_t>(index - 1));
			current_node->AddChildNode(left_child);

			auto right_child = ParseFunction(static_cast<size_t>(index + 1), end);
			current_node->AddChildNode(right_child);

			return true;
		}

		return false;
	}
}