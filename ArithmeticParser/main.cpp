#include<iostream>
#include<string>

#include"Utils.h"
#include"Parser.h"

int main()
{
	std::string input;
	std::getline(std::cin, input);

	const char charactersToRemove[] = " ";
	RemoveCharactersFromString(input, charactersToRemove);

	void* function = ParseFunction(input);

	return 0;
}