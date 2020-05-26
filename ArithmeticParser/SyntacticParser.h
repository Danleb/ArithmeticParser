#pragma once

#include <string>
#include <vector>

#include "ErrorData.h"
#include "Node.h"
#include "Token.h"

namespace arithmetic_parser
{
	class SyntacticParser
	{
	public:
		SyntacticParser() = delete;
		SyntacticParser(std::string input);
		SyntacticParser(std::vector<std::shared_ptr<Token>> tokens);

		std::shared_ptr<Node> ParseExpression();

	protected:

	private:
		std::string m_input;
		std::vector<std::shared_ptr<Token>> m_tokens;
		std::vector<ErrorData> m_error_datas;

		std::shared_ptr<Node> ParseExpression(size_t start, size_t end);

		bool OpenRoundBracketsIfNeeded(size_t& start, size_t& end);
		std::vector<size_t> EnumerateTokenIndicesOutOfBrackets(const size_t start, const size_t end);
		std::vector<size_t> EnumerateTokenIndicesOutOfModulusBrackets(const std::vector<size_t>& token_indices_outside_brackets);

		void ArrageStraightParenthesesSide();

		bool IsSingleSymbol(const size_t start, const size_t end);
		bool IsSingleNumber(const size_t start, const size_t end);
		bool IsSingleVariable(const size_t start, const size_t end);
		bool IsSingleConstant(const size_t start, const size_t end);

		bool IsInflectionPointAdditionSubstraction(const size_t start, const size_t end, const size_t index, std::shared_ptr<Node>& current_node);
		bool IsInflectionPointMultiplyDivision(const size_t start, const size_t end, const size_t index, std::shared_ptr<Node>& current_node);
		bool IsInflectionPointPower(const size_t start, const size_t end, const size_t index, std::shared_ptr<Node>& current_node);

		bool IsBuiltinFunction(const size_t start, const size_t end, std::shared_ptr<Node>& current_node);
	};
}