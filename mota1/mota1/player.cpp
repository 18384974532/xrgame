#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<graphics.h>
#include<stdlib.h>
#include<conio.h>
#include"player.h"
#include"map.h"

extern "C"
{
#include<lua.h>
#include<lauxlib.h>
#include<lualib.h>
}

extern int map[][13][13];

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

void c2lua(char *str)
{
	FILE* file = fopen(str, "w");
	fputs("map = {\n", file);
	for (int i = 0; i < 50; i++)
	{
		fputs("  {\n", file);
		for (int j = 0; j < 13; j++)
		{
			fputs("    {", file);
			for (int l = 0; l < 13; l++)
			{
				{
					char s[20] = "";
					sprintf(s, "%d,", map[i][j][l]);
					fputs(s, file);
				}
			}
			fputs("    },\n", file);
		}
		fputs("  },\n", file);
	}
	fputs("}\nreturn map", file);
	fclose(file);
}

void load_game(char* str)
{
	char s1[50];
	strcpy(s1, str);
	lua_State* pL = luaL_newstate();
	luaL_openlibs(pL);
	luaL_dofile(pL, strcat(str, "player.lua"));
	set_player(pL);

	lua_State* mapL = luaL_newstate();
	luaL_openlibs(mapL);
	luaL_dofile(mapL, strcat(s1, "map.lua"));
	set_map(mapL, map);
}

void load_saves()
{
	cleardevice();
	outtextxy(200, 200, "�浵1");
	outtextxy(200, 300, "�浵2");
	outtextxy(200, 400, "�浵3");
	MOUSEMSG b;
	while (1)
	{
		b = GetMouseMsg();
		if (b.uMsg == WM_LBUTTONDOWN)
		{
			if (b.y > 200 && b.y < 300)
			{
				char str[50] = "../saves/save1/";
				load_game(str);
				break;
			}
			else if (b.y > 300 && b.y < 400)
			{
				char str[50] = "../saves/save2/";
				load_game(str);
				break;
			}
			else if (b.y > 400 && b.y < 500)
			{
				char str[50] = "../saves/save3/";
				load_game(str);
				break;
			}
		}
	}
}

void load_data()
{
	outtextxy(200, 200, "����Ϸ");
	outtextxy(200, 300, "��ȡ��Ϸ");

	MOUSEMSG a;
	while (true)
	{
		a = GetMouseMsg();
		if (a.uMsg == WM_LBUTTONDOWN)
		{
			if (a.y > 200 && a.y < 300)
			{
				char str[50] = "../saves/newsave/";
				load_game(str);
				break;
			}
			else if (a.y > 300)
			{
				load_saves();
				break;
			}
		}
	}
}

void choose_save()
{
	cleardevice();
	outtextxy(200, 200, "�浽�浵1");
	outtextxy(200, 300, "�浽�浵2");
	outtextxy(200, 400, "�浽�浵3");
	MOUSEMSG a;
	while (1)
	{
		a = GetMouseMsg();
		if (a.uMsg == WM_LBUTTONDOWN)
		{
			if (a.y > 200 && a.y < 300)
			{
				char s1[50] = "../saves/save1/map.lua";
				c2lua(s1);
				break;
			}
			else if (a.y > 300 && a.y < 400)
			{
				char s2[50] = "../saves/save1/map.lua";
				c2lua(s2);
				break;
			}
			else if (a.y > 400 && a.y < 500)
			{
				char s3[50] = "../saves/save1/map.lua";
				c2lua(s3);
				break;
			}
		}
	}
}

void esc()
{
	cleardevice();
	outtextxy(200, 200, "�浵");
	outtextxy(200, 400, "����");
	MOUSEMSG a;
	while (1)
	{
		a = GetMouseMsg();

		if (a.uMsg == WM_LBUTTONDOWN)
		{
			if (a.y > 200 && a.y < 400)
			{
				choose_save();
				break;
			}
			else if (a.y > 400)
			{
				load_saves();
				break;
			}
		}
		/*char key;
		key = _getch();
		if (key)
			break;*/
	}
}