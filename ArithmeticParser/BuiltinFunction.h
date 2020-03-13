#pragma once
#ifndef BUILTIN_FUNCTION_H
#define BUILTIN_FUNCTION_H

namespace ArithmeticParser
{
	enum class BuiltinFunction
	{
		None = 0,
		Sinus,
		Cosine,
		Tangent,
		Cotangent,
		Exponent,
		NaturalLogarithm,
		DecimalLogarithm,
		LogarithmArbitraryBasis
	};
}

#endif // !BUILTIN_FUNCTION_H