#ifndef NODE_H
#define NODE_H

#include"Token.h"

namespace ArithmeticParser
{
	class Node
	{
	public:
		Token token;
		double Calculate();
	};
}

#endif // !NODE_H