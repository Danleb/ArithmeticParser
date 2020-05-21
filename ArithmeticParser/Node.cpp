#define _USE_MATH_DEFINES 
#include <cmath>

#include "Node.h"

namespace arithmetic_parser
{
	Node::Node(std::shared_ptr<Token> token)
	{
		m_token = token;
	}

	std::shared_ptr<Token> Node::GetToken() const noexcept
	{
		return m_token;
	}

	void Node::AddChildNode(std::shared_ptr<Node> node)
	{
		m_child_nodes.push_back(node);
	}

	double Node::Calculate() const noexcept
	{
		switch (m_token->tokenType)
		{
		case TokenType::Number:
		{
			return m_token->number;
		}

		case TokenType::Constant:
		{
			switch (m_token->constant_type)
			{
			case ConstantType::PI: {
				return M_PI;
			}
			case ConstantType::Exponent: {
				return M_E;
			}
			default:
				throw std::exception("Unrecognized consntant tpye");
			}
		}

		case TokenType::BuiltinFunction:
		{
			switch (m_token->builtin_function_type)
			{
			case BuiltinFunctionType::SignMinus:
			{
				double value = m_child_nodes[0]->Calculate();
				double negatedValue = -value;
				return negatedValue;
			}
			case BuiltinFunctionType::Addition:
			{
				double leftValue = m_child_nodes[0]->Calculate();
				double rightValue = m_child_nodes[1]->Calculate();

				return leftValue + rightValue;
			}
			case BuiltinFunctionType::Subtraction:
			{
				double leftValue = m_child_nodes[0]->Calculate();
				double rightValue = m_child_nodes[1]->Calculate();

				return leftValue - rightValue;
			}
			case BuiltinFunctionType::Multiplication:
			{
				double leftValue = m_child_nodes[0]->Calculate();
				double rightValue = m_child_nodes[1]->Calculate();

				return leftValue * rightValue;
			}
			case BuiltinFunctionType::Division:
			{
				double leftValue = m_child_nodes[0]->Calculate();
				double rightValue = m_child_nodes[1]->Calculate();

				return leftValue / rightValue;
			}
			case BuiltinFunctionType::Power:
			{
				double base = m_child_nodes[0]->Calculate();
				double power = m_child_nodes[1]->Calculate();
				double value = pow(base, power);
			}
			case BuiltinFunctionType::Absolute:
			{
				double number = m_child_nodes[0]->Calculate();
				double value = abs(number);
				return value;
			}

			case BuiltinFunctionType::Sinus:
			{
				double argument_value = m_child_nodes[0]->Calculate();
				double value = sin(argument_value);
				return value;
			}
			case BuiltinFunctionType::Cosine:
			{
				double argument_value = m_child_nodes[0]->Calculate();
				double value = cos(argument_value);
				return value;
			}
			case BuiltinFunctionType::Tangent:
			{
				double argument_value = m_child_nodes[0]->Calculate();
				double value = tan(argument_value);
				return value;
			}
			case BuiltinFunctionType::Cotangent:
			{
				double argument_value = m_child_nodes[0]->Calculate();
				double value = 1.0 / (argument_value);
				return value;
			}
			case BuiltinFunctionType::NaturalLogarithm:
			{
				double argument_value = m_child_nodes[0]->Calculate();
				double value = log(argument_value);
				return value;
			}
			case BuiltinFunctionType::DecimalLogarithm:
			{
				double argument_value = m_child_nodes[0]->Calculate();
				double value = log10(argument_value);
				return value;
			}
			}
		}
		}

		throw std::exception("Unrecognized token type");
	}
}