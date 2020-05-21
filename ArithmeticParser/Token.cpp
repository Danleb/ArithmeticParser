#include "Token.h"
#include "TokenType.h"
#include "ParenthesisSide.h"
#include "ParenthesisType.h"

namespace arithmetic_parser
{
	bool Token::IsOpenedRoundBracket()
	{
		auto open_bracket =
			tokenType == TokenType::Parentheses &&
			parenthesis_type == ParenthesisType::Round &&
			parenthesis_side == ParenthesisSide::Opening
			;

		return open_bracket;
	}

	bool Token::IsClosingRoundBracket()
	{
		auto open_bracket =
			tokenType == TokenType::Parentheses &&
			parenthesis_type == ParenthesisType::Round &&
			parenthesis_side == ParenthesisSide::Closing
			;

		return open_bracket;
	}
}