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
	}

	SyntacticParser::SyntacticParser(const std::vector<std::shared_ptr<Token>> tokens)
	{
		m_tokens = tokens;
	}

	std::shared_ptr<Node> SyntacticParser::ParseFunction()
	{
		auto tokens = GetTokens(m_input);
		auto node = ParseFunction(0, tokens.size());
		return node;
	}

	std::shared_ptr<Node> SyntacticParser::ParseFunction(size_t start, size_t end)
	{
		//CheckForParenthesisCorrectness(tokens, start, end);

		if (start == end)
		{
			auto current_token = m_tokens[start];

			if (current_token->tokenType == TokenType::Number)
			{
				auto current_node = std::make_shared<Node>(Node(current_token));
				return current_node;
			}
			else
			{
				std::ostringstream str;
				str << "Single token unparsed at position " << start << ". TokenType = " << static_cast<int>(current_token->tokenType);
				throw std::runtime_error(str.str());
			}
		}

		for (size_t i = start; i < end; i++)
		{
			auto current_token = m_tokens[i];

			if (current_token->tokenType == TokenType::BuiltinFunction)
			{
				std::shared_ptr<Node> node;

				if (TryInflectionPointAddSubstr(node, current_token, start, end, i))
				{
					return node;
				}

				//mult div
			}
		}



		return nullptr;
	}

	bool SyntacticParser::TryGetNumber()
	{
		return false;
	}

	/*bool SyntacticParser::TryInflectionPointMultiplyDivision(std::shared_ptr<Node>& node, const const std::vector<std::shared_ptr<Token>>& tokens, int start, int end)
	{

	}*/

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
			current_node->AddChildNode(left_child);

			return true;
		}

		return false;
	}
}