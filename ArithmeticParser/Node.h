#pragma once
#ifndef NODE_H
#define NODE_H

#include "Token.h"

namespace arithmetic_parser
{
	class Node
	{
	private:
		Node* leftChild;
		Node* rightChild;
		Token* token;
	
	public:
		Node() = default;
		Node(const Node&) = default;
		Node(Token token);
		~Node() = default;

		Node* GetLeftChild() const noexcept;
		Node* GetRightChild() const noexcept;
		Token* GetToken() const noexcept;

		double Calculate() const noexcept;
	};
}

#endif // !NODE_H