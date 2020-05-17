#pragma once
#ifndef COMMAND_LINE_OPTION_H
#define COMMAND_LINE_OPTION_H

namespace arithmetic_parser
{
	enum class CmdOption
	{
		Help,
		Version,
		Clipboard,
		File,
		Expression,
		Save,
		Verbose
	};
}


#endif // !COMMAND_LINE_OPTION_H