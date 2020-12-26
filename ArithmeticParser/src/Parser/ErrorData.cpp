#include "ErrorData.h"

namespace arithmetic_parser
{
	ErrorData::ErrorData(ErrorCode error_code, int error_start_index) :
		m_error_code(error_code),
		m_error_start_index(error_start_index),
		m_error_end_index(-1)
	{
	}

	ErrorData::ErrorData(ErrorCode error_code, int error_start_index, int error_end_index) :
		m_error_code(error_code),
		m_error_start_index(error_start_index),
		m_error_end_index(error_end_index)
	{
	}
}