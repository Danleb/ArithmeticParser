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

	bool SyntacticParser::OpenRoundBracketsIfNeeded(size_t& start, size_t& end)
	{
		int brackets_counter = 0;

		auto can_uncover_braces = m_tokens[start]->IsOpenedRoundBracket();

		for (size_t i = start; i <= end; ++i)
		{
			auto current_token = m_tokens[i];

			if (current_token->IsOpenedRoundBracket())
				brackets_counter++;
			else if (current_token->IsClosingRoundBracket())
			{
				brackets_counter--;

				if (brackets_counter < 0)
				{
					ErrorData error_data(ErrorCode::SINGLE_CLOSING_PARENTHESIS, current_token->tokenStart);
					m_error_datas.push_back(error_data);
					throw std::exception();
				}
			}

			if (brackets_counter == 0 && i != end)
			{
				can_uncover_braces = false;
			}
		}

		if (brackets_counter > 0)
		{
			ErrorData error_data(ErrorCode::SINGLE_OPENING_PARENTHESIS, m_tokens[start]->tokenStart);
			m_error_datas.push_back(error_data);
			throw std::exception();
		}

		if (can_uncover_braces)
		{
			start++;
			end--;
		}
	}

	bool SyntacticParser::IsSingleNumberNodeAt(const size_t start, const size_t end)
	{
		if (start == end)
		{
			auto current_token = m_tokens[start];

			if (current_token->tokenType == TokenType::Number)
			{
				auto current_node = std::make_shared<Node>(current_token);
				return true;
			}
			else
			{
				std::ostringstream str;
				str << "Single token unparsed at position " << start << ". TokenType = " << static_cast<int>(current_token->tokenType);
				ErrorData error_data(ErrorCode::SINGLE_TOKEN_UNPARSED, current_token->tokenStart);
				m_error_datas.push_back(error_data);
				throw std::runtime_error(str.str());
			}
		}

		return false;
	}

	//std::rand Enumerate()
	//{
	//}

	std::shared_ptr<Node> SyntacticParser::ParseFunction(size_t start, size_t end)
	{
		while (OpenRoundBracketsIfNeeded(start, end));

		//TODO if(IsSingleVariablNodeAt)

		if (IsSingleNumberNodeAt(start, end))
			return std::make_shared<Node>(m_tokens[start]);

		//for (auto& pair : EnumerateTokensOutOfBrackets())
		{
			//auto token_index = 
			//auto token = 


		}

		//check for inflection points of the addition and substraction
		for (size_t i = end + 1; i >= start + 1; --i)
		{
			auto index = i - 1;
			auto current_token = m_tokens[index];

			if (current_token->tokenType == TokenType::BuiltinFunction)
			{
				std::shared_ptr<Node> node;
				if (TryInflectionPointAddSubstr(node, current_token, start, end, index))
					return node;
			}
		}

		//check for inflection points of the multiplication and division
		for (size_t i = end + 1; i >= start + 1; --i)
		{
			auto index = i - 1;
			auto current_token = m_tokens[index];
			if (current_token->tokenType == TokenType::BuiltinFunction)
			{
				std::shared_ptr<Node> node;
				if (TryInflectionPointMultiplyDivision(node, current_token, start, end, index))
					return node;
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

	bool SyntacticParser::TryGetNumber(std::shared_ptr<Node>& current_node, const std::shared_ptr<Token>& current_token, size_t start, size_t end, size_t index)
	{
		if (start == end)
		{
			//check for single number
			auto current_token = m_tokens[start];

			if (current_token->tokenType == TokenType::Number)
			{
				auto current_node = std::make_shared<Node>(current_token);
				return true;
			}
			else
			{
				std::ostringstream str;
				str << "Single token unparsed at position " << start << ". TokenType = " << static_cast<int>(current_token->tokenType);
				throw std::runtime_error(str.str());
			}
		}

		return false;
	}

	bool TryInflectionPointPower()
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

		//TODO Chek if this is multiplication operation without multiplication symbol '*'.

		if (inflection_point)
		{
			current_node = std::make_shared<Node>(current_token);

			auto left_child = ParseFunction(start, static_cast<size_t>(index - 1));
			current_node->AddChildNode(left_child);

			auto right_child = ParseFunction(static_cast<size_t>(index + 1), end);
			current_node->AddChildNode(right_child);

			return true;
		}

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
			current_node = std::make_shared<Node>(current_token);

			auto left_child = ParseFunction(start, static_cast<size_t>(index - 1));
			current_node->AddChildNode(left_child);

			auto right_child = ParseFunction(static_cast<size_t>(index + 1), end);
			current_node->AddChildNode(right_child);

			return true;
		}

		return false;
	}
}