#pragma once

namespace arithmetic_parser
{
	enum class BuiltinFunctionType
	{
		None = 0,

		SignPlus,
		SignMinus,

		Addition,
		Subtraction,
		Multiplication,
		Division,		

		Power,
		Absolute,		

		Sinus,
		Cosine,
		Tangent,
		Cotangent,

		Arcsine,
		Arccosine,
		Arctangent,
		Arccotangent,

		NaturalLogarithm,
		DecimalLogarithm,
		LogarithmArbitraryBasis
	};
}