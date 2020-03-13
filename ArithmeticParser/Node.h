#pragma once
#ifndef NODE_H
#define NODE_H

#include"Token.h"

namespace ArithmeticParser
{
	class Node
	{
	private:
		Node* leftChild;
		Node* rightChild;
		Token* token;
	
	public:
		Node* GetLeftChild() const noexcept;
		Node* GetRightChild() const noexcept;
		Token* GetToken() const noexcept;

		double Calculate();
	};
}

#endif // !NODE_H