#include "gtest/gtest.h"

#include <string>
#include <vector>

#include "SyntacticParser.h"
#include "LexicalParser.h"
#include "Token.h"

namespace ArithmeticalParserTests
{
	namespace SyntacticParserTests
	{
		constexpr double eps = 1e-10;

		TEST(BuiltinFunctionsTests, SinusTest)
		{
			auto node = arithmetic_parser::SyntacticParser("sin(PI)").ParseExpression();
			auto value = node->Calculate();
			ASSERT_NEAR(value, 0, eps);
		}

		TEST(BuiltinFunctionsTests, CosineTest)
		{
			auto node = arithmetic_parser::SyntacticParser("cos(PI/2)").ParseExpression();
			auto value = node->Calculate();
			ASSERT_NEAR(value, 0, eps);
		}

		TEST(BuiltinFunctionsTests, NaturalLogarithmTest)
		{
			auto node = arithmetic_parser::SyntacticParser("ln(15)").ParseExpression();
			auto value = node->Calculate();
			ASSERT_NEAR(value, log(15), eps);
		}

		TEST(BuiltinFunctionsTests, DecimalLogarithmTest)
		{
			auto node = arithmetic_parser::SyntacticParser("lg(24)").ParseExpression();
			auto value = node->Calculate();
			ASSERT_NEAR(value, log10(24), eps);
		}

		TEST(BuiltinFunctionsTests, CustomLogarithmTest)
		{
			auto node = arithmetic_parser::SyntacticParser("log(432,16)").ParseExpression();
			auto value = node->Calculate();
			ASSERT_NEAR(value, 2.1887218755, eps);
		}

		TEST(BuiltinFunctionsTests, NestedCustomLogarithmsTest)
		{
			auto node = arithmetic_parser::SyntacticParser("log(log(4,5),log(6,7))").ParseExpression();
			auto value = node->Calculate();
			ASSERT_NEAR(value, 1.80844, 0.0001);
		}

		TEST(BuiltinFunctionsTests, ArccotangentTest)
		{
			auto node = arithmetic_parser::SyntacticParser("actg(-100)").ParseExpression();
			auto value = node->Calculate();
			ASSERT_NEAR(value, 3.1315929869, 0.0001);
		}
	}
}