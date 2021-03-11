#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<string.h>
#include<graphics.h>
#include<stdlib.h>
#include<conio.h>
#include"map.h"
#include"player.h"
#include"test_map.h"

extern "C"
{
#include<lua.h>
#include<lauxlib.h>
#include<lualib.h>
}

IMAGE monsterImg[42];
IMAGE wallImg[2];
IMAGE doorImg[5];
IMAGE itemImg[5];

int map[50][13][13];
extern gameRole role;

void loadresource()
{
	for (int i = 0; i < 42; i++)
	{
		char filename[20] = "";
		sprintf(filename, "../res/%d.jpg", i);
		loadimage(monsterImg + i, filename, 60, 60);
	}
	for (int i = 1000; i < 1002; i++)
	{
		char filename[20] = "";
		sprintf(filename, "../res/%d.jpg", i);
		loadimage(wallImg + (i - 1000), filename, 60, 60);
	}
	for (int i = 2000; i < 2005; i++)
	{
		char filename[20] = "";
		sprintf(filename, "../res/%d.jpg", i);
		loadimage(doorImg + (i - 2000), filename, 60, 60);
	}
	for (int i = 3000; i < 3005; i++)
	{
		char filename[20] = "";
		sprintf(filename, "../res/%d.jpg", i);
		loadimage(itemImg + (i - 3000), filename, 60, 60);
	}
}

void drawmap(int n)
{
	int x, y;
	char st[20] = "";
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			x = 60 * j;
			y = 60 * i;
			if (map[role.building_level][i][j] >= 3000)
				putimage(x, y, itemImg + (map[role.building_level][i][j] - 3000));
			else if (map[role.building_level][i][j] >= 2000)
				putimage(x, y, doorImg + (map[role.building_level][i][j] - 2000));
			else if (map[role.building_level][i][j] >= 1000)
				putimage(x, y, wallImg + (map[role.building_level][i][j] - 1000));
			else
				putimage(x, y, monsterImg + map[role.building_level][i][j]);
		}
		for (int j = 13; j < 15; j++)
		{
			x = 60 * j;
			y = 60 * i;
			putimage(x, y, &wallImg[1]);
		}
	}
	outtextxy(780, 40, "角色等级:");
	outtextxy(780, 80, intToWcahr(role.level));
	outtextxy(780, 120, "生命值:");
	outtextxy(780, 160, intToWcahr(role.life));
	outtextxy(780, 200, "蓝量:");
	outtextxy(780, 240, intToWcahr(role.blue));
	outtextxy(780, 280, "攻击力:");
	outtextxy(780, 320, intToWcahr(role.attack));
	outtextxy(780, 360, "防御力:");
	outtextxy(780, 400, intToWcahr(role.defence));
	outtextxy(780, 440, "经验值:");
	outtextxy(780, 480, intToWcahr(role.exp));
	outtextxy(780, 520, "黄钥匙:");
	outtextxy(780, 560, intToWcahr(role.yellow_key));
	outtextxy(780, 600, "蓝钥匙:");
	outtextxy(780, 640, intToWcahr(role.blue_key));
	outtextxy(780, 680, "红钥匙:");
	outtextxy(780, 720, intToWcahr(role.building_level));
}

void set_map(lua_State* L, int map[][13][13])
{
	lua_getglobal(L, "map");
	int index = lua_gettop(L);
	int indexA = 0;
	lua_pushnil(L);
	while (lua_next(L, index))
	{
		int tempIndex = lua_gettop(L);
		lua_pushnil(L);
		int count = 0;
		while (lua_next(L, tempIndex))
		{
			int temp2Index = lua_gettop(L);
			lua_pushnil(L);
			int count1 = 0;
			while (lua_next(L, temp2Index))
			{
				int card = luaL_checkinteger(L, -1);
				map[indexA][count][count1++] = card;
				lua_pop(L, 1);
			}
			count++;
			lua_pop(L, 1);
		}
		indexA++;
		lua_pop(L, 1);
	}
}