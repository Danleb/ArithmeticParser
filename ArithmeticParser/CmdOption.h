#pragma once
#ifndef CMD_OPTION_H
#define CMD_OPTION_H

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


#endif // !CMD_OPTION_H