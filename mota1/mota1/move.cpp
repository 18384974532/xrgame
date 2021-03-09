#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<string.h>
#include<graphics.h>
#include<stdlib.h>
#include<conio.h>
#include"map.h"
#include"player.h"

extern "C"
{
#include<lua.h>
#include<lauxlib.h>
#include<lualib.h>
}

extern int map[][13][13];
extern gameRole role;

void move(lua_State* L, gameRole* role, int pos)
{
	lua_getglobal(L, "move");
	lua_newtable(L);
	lua_pushinteger(L, role->level);
	lua_setfield(L, -2, "level");
	lua_pushinteger(L, role->life);
	lua_setfield(L, -2, "life");
	lua_pushinteger(L, role->blue);
	lua_setfield(L, -2, "blue");
	lua_pushinteger(L, role->attack);
	lua_setfield(L, -2, "attack");
	lua_pushinteger(L, role->defence);
	lua_setfield(L, -2, "defence");
	lua_pushinteger(L, role->exp);
	lua_setfield(L, -2, "exp");
	lua_pushinteger(L, role->yellow_key);
	lua_setfield(L, -2, "yellow_key");
	lua_pushinteger(L, role->blue_key);
	lua_setfield(L, -2, "blue_key");
	lua_pushinteger(L, role->red_key);
	lua_setfield(L, -2, "red_key");
	lua_pushinteger(L, role->building_level);
	lua_setfield(L, -2, "building_level");
	lua_pushinteger(L, role->suc);
	lua_setfield(L, -2, "suc");
	lua_pushinteger(L, pos);

	lua_pcall(L, 2, 1, 0);

	lua_getfield(L, -1, "level");
	role->level = lua_tointeger(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, -1, "life");
	role->life = lua_tointeger(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, -1, "blue");
	role->blue = lua_tointeger(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, -1, "attack");
	role->attack = lua_tointeger(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, -1, "defence");
	role->defence = lua_tointeger(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, -1, "exp");
	role->exp = lua_tointeger(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, -1, "yellow_key");
	role->yellow_key = lua_tointeger(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, -1, "blue_key");
	role->blue_key = lua_tointeger(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, -1, "red_key");
	role->red_key = lua_tointeger(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, -1, "building_level");
	role->building_level = lua_tointeger(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, -1, "suc");
	role->suc = lua_tointeger(L, -1);
	lua_pop(L, 1);
}

void getkey(lua_State* L)
{
	char key;
	int i, j;
	for (i = 0; i < 13; i++)
	{
		for (j = 0; j < 13; j++)
			if (map[role.building_level][i][j] == 2)
				break;
		if (map[role.building_level][i][j] == 2)
			break;
	}
	key = _getch();
	switch (key)
	{
	case 'w':
		if (i > 0)
		{
			move(L, &role, map[role.building_level][i - 1][j]);
			if (role.suc == 1)
			{
				map[role.building_level][i][j] = 1001;
				map[role.building_level][i - 1][j] = 2;
				role.suc = 0;
			}
			break;
		}
	case 'a':
		if (j > 0)
		{
			move(L, &role, map[role.building_level][i][j - 1]);
			if (role.suc == 1)
			{
				map[role.building_level][i][j] = 1001;
				map[role.building_level][i][j - 1] = 2;
				role.suc = 0;
			}
			break;
		}
	case 's':
		if (i < 13)
		{
			move(L, &role, map[role.building_level][i + 1][j]);
			if (role.suc == 1)
			{
				map[role.building_level][i][j] = 1001;
				map[role.building_level][i + 1][j] = 2;
				role.suc = 0;
			}
			break;
		}
	case 'd':
		if (j < 13)
		{
			move(L, &role, map[role.building_level][i][j + 1]);
			if (role.suc == 1)
			{
				map[role.building_level][i][j] = 1001;
				map[role.building_level][i][j + 1] = 2;
				role.suc = 0;
			}
			break;
		}
	}
}