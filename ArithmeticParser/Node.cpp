#include "Node.h"

namespace arithmetic_parser
{
	Node::Node(class Token token)
	{
		
	}

	double Node::Calculate() const noexcept
	{
		switch (token->tokenType)
		{
		case TokenType::Number:
			{
				return token->number;
			}			
			
		case TokenType::Operator:
			{

				return 0;
			}			

		case TokenType::BuiltinFunction:
			{
				//switch ()
				{
					
				}
			}
		}

		return 0;
	}
}