#pragma once

#include <memory>
#include <vector>

#include "BuiltinFunctionType.h"
#include "Token.h"

namespace arithmetic_parser
{
	class Node
	{
	private:
		bool m_value_symbol_based_node;
		BuiltinFunctionType m_builtin_function_type;
		std::vector<std::shared_ptr<Node>> m_child_nodes;
		std::shared_ptr<Token> m_token;

		double GetSymbolValue() const; 
		double CalculateValue() const;

	public:
		Node() = default;
		Node(const Node&) = default;
		Node(std::shared_ptr<Token> token);
		Node(BuiltinFunctionType builtin_function_type);
		~Node() = default;

		//BuiltinFunctionType GetFunctionType();

		std::shared_ptr<Token> GetToken() const noexcept;
		
		void AddChildNode(std::shared_ptr<Node>);

		double Calculate() const;
		double Calculate(double*) const;
	};
}