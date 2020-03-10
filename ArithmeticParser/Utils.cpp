#include<algorithm>

#include"Utils.h"

void RemoveCharactersFromString(std::string& s, const char* characters)
{
	for (unsigned int i = 0; i < strlen(characters); ++i)
	{
		s.erase(std::remove(s.begin(), s.end(), characters[i]), s.end());
	}
}