#include<stdio.h>
#include<string.h>
#include<graphics.h>
#include<stdlib.h>
#include<conio.h>
#include"player.h"

extern "C"
{
#include<lua.h>
#include<lauxlib.h>
#include<lualib.h>
}

gameRole role;

void set_player(lua_State* L)
{
	lua_getglobal(L, "player");
	int i = 0;
	int* p = &role.level;
	int index = lua_gettop(L);
	lua_pushnil(L);
	while (lua_next(L, index))
	{
		int value = luaL_checkinteger(L, -1);
		(*p++) = value;
		lua_pop(L, 1);
	}
}