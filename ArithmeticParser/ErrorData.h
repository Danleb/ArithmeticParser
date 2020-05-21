#pragma once

#include "ErrorCode.h"

namespace arithmetic_parser
{
	struct ErrorData
	{
		ErrorCode m_error_code;
		int m_error_start_index;
		int m_error_end_index;
		//string description of the error

		ErrorData() = default;
		ErrorData(const ErrorData&) = default;
		ErrorData(ErrorCode error_code, int error_start_index);
		ErrorData(ErrorCode error_code, int error_start_index, int error_end_index);
	};
}