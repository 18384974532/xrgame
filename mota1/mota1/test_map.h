#pragma once
char str[20] = "";
char* intToWcahr(int xNum)
{
	sprintf_s(str, "%d", xNum);
	return str;
}
