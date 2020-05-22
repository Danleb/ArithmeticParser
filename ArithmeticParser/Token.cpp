#include "Token.h"
#include "TokenType.h"
#include "ParenthesisSide.h"
#include "ParenthesisType.h"

namespace arithmetic_parser
{
	Token::Token(TokenType token_type) :
		tokenType(token_type),
		builtin_function_type(BuiltinFunctionType::None)
	{

	}

	Token::Token(ParenthesisType parenthesisType, ParenthesisSide parenthesisSide) :
		tokenType(TokenType::Parentheses),
		parenthesis_type(parenthesisType),
		parenthesis_side(parenthesisSide)
	{

	}

	Token::Token(double number) :
		tokenType(TokenType::Number),
		builtin_function_type(BuiltinFunctionType::None),
		number(number),
		variableName("")
	{

	}

	Token::Token(BuiltinFunctionType builtinFunctionType) :
		tokenType(TokenType::BuiltinFunction),
		builtin_function_type(builtinFunctionType),
		number(0),
		variableName("")
	{

	}

	Token::Token(ConstantType constantType) :
		tokenType(TokenType::Constant),
		constant_type(constantType)
	{

	}

	Token::Token(std::string variableName) :
		tokenType(TokenType::Variable),
		builtin_function_type(BuiltinFunctionType::None),
		number(0),
		variableName(std::move(variableName))
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
		return tokenType == TokenType::Number;
	}

	bool Token::IsConstant()
	{
		return tokenType == TokenType::Constant;
	}

	bool Token::IsVariable()
	{
		return tokenType == TokenType::Variable;
	}

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