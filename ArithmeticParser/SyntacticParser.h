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

		std::shared_ptr<Node> ParseFunction();

	protected:

	private:
		std::string m_input;
		std::vector<std::shared_ptr<Token>> m_tokens;
		std::vector<ErrorData> m_error_datas;

		std::shared_ptr<Node> ParseFunction(size_t start, size_t end);

		bool OpenRoundBracketsIfNeeded(size_t& start, size_t& end);

		bool IsSingleNumberNodeAt(const size_t start, const size_t end);

		bool TryGetNumber(std::shared_ptr<Node>& current_node, const std::shared_ptr<Token>& current_token, size_t start, size_t end, size_t index);
		bool TryInflectionPointAddSubstr(std::shared_ptr<Node>& current_node, const std::shared_ptr<Token>& current_token, size_t start, size_t end, size_t index);
		bool TryInflectionPointMultiplyDivision(std::shared_ptr<Node>& current_node, const std::shared_ptr<Token>& current_token, size_t start, size_t end, size_t index);
	};
}