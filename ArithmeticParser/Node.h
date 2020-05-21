#pragma once

#include <memory>
#include <vector>

#include "Token.h"

namespace arithmetic_parser
{
	class Node
	{
	private:
		std::vector<std::shared_ptr<Node>> m_child_nodes;
		std::shared_ptr<Token> m_token;

	public:
		Node() = default;
		Node(const Node&) = default;
		Node(std::shared_ptr<Token> token);
		~Node() = default;

		std::shared_ptr<Token> GetToken() const noexcept;
		
		void AddChildNode(std::shared_ptr<Node>);

		double Calculate() const noexcept;
	};
}