#define _USE_MATH_DEFINES 
#include <cmath>

#include "BuiltinFunctionType.h"
#include "Node.h"

namespace arithmetic_parser
{
	Node::Node(std::shared_ptr<Token> token) :
		m_token(token),
		m_builtin_function_type(token->builtin_function_type)
	{
		m_value_symbol_based_node = m_token->IsValueSymbol();
	}

	Node::Node(BuiltinFunctionType builtin_function_type) :
		m_token(nullptr),
		m_builtin_function_type(builtin_function_type),
		m_value_symbol_based_node(false)
	{

	}

	std::shared_ptr<Token> Node::GetToken() const noexcept
	{
		return m_token;
	}

	void Node::AddChildNode(std::shared_ptr<Node> node)
	{
		m_child_nodes.push_back(node);
	}

	double Node::GetSymbolValue() const
	{
		switch (m_token->token_type)
		{
		case TokenType::Number: {
			return m_token->number;
		}

		case TokenType::Constant: {
			switch (m_token->constant_type)
			{
			case ConstantType::PI: {
				return M_PI;
			}
			case ConstantType::Exponent: {
				return M_E;
			}
			default:
				throw std::exception("Unrecognized constant type");
			}
		}

		case TokenType::Variable: {
			//GetVariableValue(arguments)
			throw std::exception("Getting variable value is not yet implemented");
		}
		}

		throw std::exception("Unrecognized token symbol value type");
	}

	double Node::CalculateValue() const
	{
		switch (m_builtin_function_type)
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
			return value;
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
			double value = 1.0 / tan(argument_value);
			return value;
		}
		case BuiltinFunctionType::Arcsine:
		{
			double argument_value = m_child_nodes[0]->Calculate();
			double value = asin(argument_value);
			return value;
		}
		case BuiltinFunctionType::Arccosine:
		{
			double argument_value = m_child_nodes[0]->Calculate();
			double value = acos(argument_value);
			return value;
		}
		case BuiltinFunctionType::Arctangent:
		{
			double argument_value = m_child_nodes[0]->Calculate();
			double value = atan(argument_value);
			return value;
		}
		case BuiltinFunctionType::Arccotangent:
		{
			double argument_value = m_child_nodes[0]->Calculate();
			double value = M_PI_2 - atan(argument_value);
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
		case BuiltinFunctionType::LogarithmArbitraryBasis:
		{
			double argument_value = m_child_nodes[0]->Calculate();
			double base = m_child_nodes[1]->Calculate();
			return log(argument_value) / log(base);
		}
		}

		throw std::exception("Unrecognized builtin function type");
	}

	double Node::Calculate() const
	{
		if (m_value_symbol_based_node)
			return GetSymbolValue();
		else
			return CalculateValue();
	}

	double Node::Calculate(double* arguments) const
	{
		return -1;
	}
}