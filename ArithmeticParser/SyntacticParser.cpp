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
		while (OpenRoundBracketsIfNeeded(start, end));

		if (IsSingleSymbol(start, end))
			return std::make_shared<Node>(m_tokens[start]);

		auto indices = EnumerateTokenIndicesOutOfBrackets(start, end);
		std::reverse(indices.begin(), indices.end());

		for (const auto token_index : indices)
		{
			auto current_token = m_tokens[token_index];

			if (current_token->tokenType == TokenType::BuiltinFunction)
			{
				std::shared_ptr<Node> node;

				if (IsInflectionPointAdditionSubstraction(start, end, token_index, node))
					return node;
			}
		}

		for (const auto token_index : indices)
		{
			auto current_token = m_tokens[token_index];

			std::shared_ptr<Node> node;

			if (IsInflectionPointMultiplyDivision(start, end, token_index, node))
				return node;
		}

		for (const auto token_index : indices)
		{
			auto current_token = m_tokens[token_index];

			std::shared_ptr<Node> node;

			if (IsInflectionPointPower(start, end, token_index, node))
				return node;
		}

		//check for signed operator (unary minus/plus)
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

		std::ostringstream s;
		s << "SyntacticParser did not recognized the expression in the range Start=" << start << " End=" << end;
		ErrorData error_data(ErrorCode::SYNTACTIC_ERROR, start_token->tokenStart);
		m_error_datas.push_back(error_data);
		throw std::runtime_error(s.str());
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
					throw std::exception("SINGLE_CLOSING_PARENTHESIS");
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
			throw std::exception("SINGLE_OPENING_PARENTHESIS");
		}

		if (can_uncover_braces)
		{
			start++;
			end--;
			return true;
		}

		return false;
	}

	std::vector<size_t> SyntacticParser::EnumerateTokenIndicesOutOfBrackets(const size_t start, const size_t end)
	{
		int brackets_counter = 0;

		std::vector<size_t> indices;

		auto inside_braces = false;

		for (auto i = start; i <= end; ++i)
		{
			auto current_token = m_tokens[i];

			if (current_token->IsOpenedRoundBracket())
				brackets_counter++;
			else if (current_token->IsClosingRoundBracket())
				brackets_counter--;

			if (brackets_counter == 1 && !inside_braces)
			{
				inside_braces = true;
				indices.push_back(i);
			}
			else if (brackets_counter == 0)
			{
				inside_braces = false;
				indices.push_back(i);
			}
		}

		return indices;
	}

	bool SyntacticParser::IsSingleSymbol(const size_t start, const size_t end)
	{
		if (start != end)
			return false;

		auto single_symbol =
			IsSingleNumber(start, end) ||
			IsSingleVariable(start, end) ||
			IsSingleConstant(start, end);

		if (single_symbol)
			return true;

		std::ostringstream str;
		auto current_token = m_tokens[start];
		str << "Single token unparsed at position " << start << ". TokenType = " << static_cast<int>(current_token->tokenType);
		ErrorData error_data(ErrorCode::SINGLE_TOKEN_UNPARSED, current_token->tokenStart);
		m_error_datas.push_back(error_data);
		throw std::runtime_error(str.str());
	}

	bool SyntacticParser::IsSingleNumber(const size_t start, const size_t end)
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

	bool SyntacticParser::IsSingleVariable(const size_t start, const size_t end)
	{
		if (start != end)
			return false;

		auto current_token = m_tokens[start];

		return current_token->tokenType == TokenType::Variable;
	}

	bool SyntacticParser::IsSingleConstant(const size_t start, const size_t end)
	{
		if (start != end)
			return false;

		auto current_token = m_tokens[start];

		return current_token->tokenType == TokenType::Constant;
	}

	bool SyntacticParser::IsInflectionPointPower(const size_t start, const size_t end, const size_t index, std::shared_ptr<Node>& current_node)
	{
		auto current_token = m_tokens[start];

		auto power_function = current_token->tokenType == TokenType::BuiltinFunction &&
			current_token->builtin_function_type == BuiltinFunctionType::Power;

		if (power_function)
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

	bool SyntacticParser::IsInflectionPointMultiplyDivision(const size_t start, const size_t end, const size_t index, std::shared_ptr<Node>& current_node)
	{
		auto current_token = m_tokens[index];

		auto multiplication = current_token->builtin_function_type == BuiltinFunctionType::Multiplication;
		auto division = current_token->builtin_function_type == BuiltinFunctionType::Division;
		auto inflection_function = current_token->tokenType == TokenType::BuiltinFunction && (multiplication || division);

		auto expression_first_token = index == start;
		auto expression_last_token = index == end;

		if (!expression_first_token)
		{
			auto previous_token = m_tokens[index - 1];

			auto explicit_inflection_point =
				inflection_function &&
				(
					previous_token->IsValueSymbol() ||
					previous_token->IsClosingRoundBracket()
					);

			if (explicit_inflection_point)
			{
				current_node = std::make_shared<Node>(current_token);

				auto left_child = ParseFunction(start, static_cast<size_t>(index - 1));
				current_node->AddChildNode(left_child);

				auto right_child = ParseFunction(static_cast<size_t>(index + 1), end);
				current_node->AddChildNode(right_child);

				return true;
			}

			if (current_token->IsOpenedRoundBracket())
			{
				if (previous_token->IsValueSymbol() || previous_token->IsClosingRoundBracket())
				{
					current_node = std::make_shared<Node>(BuiltinFunctionType::Multiplication);

					auto left_child = ParseFunction(start, static_cast<size_t>(index - 1));
					current_node->AddChildNode(left_child);

					auto right_child = ParseFunction(index, end);
					current_node->AddChildNode(right_child);

					return true;
				}
			}
		}

		if (!expression_last_token && current_token->IsClosingRoundBracket())
		{
			auto next_token = m_tokens[index + 1];

			if (next_token->IsValueSymbol() || next_token->IsOpenedRoundBracket())
			{
				current_node = std::make_shared<Node>(BuiltinFunctionType::Multiplication);

				auto left_child = ParseFunction(start, index);
				current_node->AddChildNode(left_child);

				auto right_child = ParseFunction(static_cast<size_t>(index + 1), end);
				current_node->AddChildNode(right_child);

				return true;
			}
		}

		return false;
	}

	bool SyntacticParser::IsInflectionPointAdditionSubstraction(const size_t start, const size_t end, const size_t index, std::shared_ptr<Node>& current_node)
	{
		auto current_token = m_tokens[index];

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