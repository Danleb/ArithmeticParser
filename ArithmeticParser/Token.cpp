#include "Token.h"
#include "TokenType.h"
#include "ParenthesisSide.h"
#include "ParenthesisType.h"

namespace arithmetic_parser
{
	Token::Token(TokenType token_type) :
		token_type(token_type),
		builtin_function_type(BuiltinFunctionType::None)
	{

	}

	Token::Token(ParenthesisType parenthesisType, ParenthesisSide parenthesisSide) :
		token_type(TokenType::Parentheses),
		parenthesis_type(parenthesisType),
		parenthesis_side(parenthesisSide)
	{

	}

	Token::Token(double number) :
		token_type(TokenType::Number),
		builtin_function_type(BuiltinFunctionType::None),
		number(number),
		variable_name("")
	{

	}

	Token::Token(BuiltinFunctionType builtinFunctionType) :
		token_type(TokenType::BuiltinFunction),
		builtin_function_type(builtinFunctionType),
		number(0),
		variable_name("")
	{

	}

	Token::Token(ConstantType constantType) :
		token_type(TokenType::Constant),
		constant_type(constantType)
	{

	}

	Token::Token(std::string variableName) :
		token_type(TokenType::Variable),
		builtin_function_type(BuiltinFunctionType::None),
		number(0),
		variable_name(std::move(variableName))
	{

	}

	bool Token::IsValueSymbol()
	{
		return
			IsNumber() ||
			IsConstant() ||
			IsVariable();
	}

	bool Token::IsNumber()
	{
		return token_type == TokenType::Number;
	}

	bool Token::IsConstant()
	{
		return token_type == TokenType::Constant;
	}

	bool Token::IsVariable()
	{
		return token_type == TokenType::Variable;
	}

	bool Token::IsOpeningBracket()
	{
		return
			IsOpeningRoundBracket() ||
			IsOpeningStraightBracket();
	}

	bool Token::IsClosingBracket()
	{
		return
			IsClosingRoundBracket() ||
			IsClosingStraightBracket();
	}

	bool Token::IsOpeningStraightBracket()
	{
		auto open_bracket =
			token_type == TokenType::Parentheses &&
			parenthesis_type == ParenthesisType::Straight &&
			parenthesis_side == ParenthesisSide::Opening
			;

		return open_bracket;
	}

	bool Token::IsClosingStraightBracket()
	{
		auto closing_bracket =
			token_type == TokenType::Parentheses &&
			parenthesis_type == ParenthesisType::Straight &&
			parenthesis_side == ParenthesisSide::Closing
			;

		return closing_bracket;
	}

	bool Token::IsOpeningRoundBracket()
	{
		auto open_bracket =
			token_type == TokenType::Parentheses &&
			parenthesis_type == ParenthesisType::Round &&
			parenthesis_side == ParenthesisSide::Opening
			;

		return open_bracket;
	}

	bool Token::IsClosingRoundBracket()
	{
		auto open_bracket =
			token_type == TokenType::Parentheses &&
			parenthesis_type == ParenthesisType::Round &&
			parenthesis_side == ParenthesisSide::Closing
			;

		return open_bracket;
	}
}