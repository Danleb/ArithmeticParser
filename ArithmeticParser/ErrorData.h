#pragma once
#ifndef ERROR_DATA_H
#define ERROR_DATA_H

#include "ErrorCode.h"

namespace arithmetic_parser
{
	struct ErrorData
	{
		ErrorCode errorCode;
		int errorStartIndex;
		int errorEndIndex;
	};
}

#endif // !ERROR_DATA_H