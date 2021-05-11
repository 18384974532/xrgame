#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<string.h>
#include<graphics.h>
#include<stdlib.h>
#include<conio.h>
#include"player.h"
#include "map.h"
#include "move.h"

extern "C"
{
#include<lua.h>
#include<lauxlib.h>
#include<lualib.h>
}

extern int map[][13][13];
extern gameRole role;

int main()
{
	initgraph(900,  780);
	loadresource();

	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	luaL_dofile(L, "some.lua");

	load_data();

	drawmap(role.building_level);

	while (1) {
		drawmap(role.building_level);
		getkey(L);
	}
	system("pause");
	return 0;
}