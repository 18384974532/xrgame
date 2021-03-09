#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<string.h>
#include<graphics.h>
#include<stdlib.h>
#include<conio.h>
#include"test_map.h"

extern "C"
{
#include<lua.h>
#include<lauxlib.h>
#include<lualib.h>
}

int map[1][13][13];

struct gameRole {
	int level;      //等级
	int exp;        //经验
	int life;       //生命值
	int blue;       //蓝量
	int attack;     //攻击
	int defence;    //防御
	int yellow_key; //黄钥匙
	int blue_key;   //蓝钥匙
	int red_key;    //红钥匙
	int building_level; //层数
	int suc; //是否成功移动
}role;

void set_player(lua_State* L)
{
	lua_getglobal(L, "player");
	int i = 0;
	int *p = &role.level;
	int index = lua_gettop(L);
	lua_pushnil(L);
	while (lua_next(L, index))
	{
		int value = luaL_checkinteger(L, -1);
		(*p++) = value;
		lua_pop(L, 1);
	}
}

void putrole()
{
	//role.rolename = 'x';
	role.level = 1;
	role.exp = 0;
	role.life = 10000;
	role.blue = 200;
	role.attack = 1;
	role.defence = 1000;
	role.yellow_key = 100;
	role.blue_key = 100;
	role.red_key = 100;
	role.suc = 0;
	role.building_level = 0;
}

IMAGE monsterImg[42];
IMAGE wallImg[2];
IMAGE doorImg[5];
IMAGE itemImg[5];

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
		loadimage(wallImg + (i-1000), filename, 60, 60);
	}
	for (int i = 2000; i < 2005; i++)
	{
		char filename[20] = "";
		sprintf(filename, "../res/%d.jpg", i);
		loadimage(doorImg + (i-2000), filename, 60, 60);
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
			else if(map[role.building_level][i][j] >= 2000)
				putimage(x, y, doorImg + (map[role.building_level][i][j]-2000));
			else if (map[role.building_level][i][j] >= 1000)
				putimage(x, y, wallImg + (map[role.building_level][i][j]-1000));
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

void move(lua_State *L, gameRole *role, int pos)
{
	lua_getglobal(L, "move");
	lua_newtable(L);
	lua_pushinteger(L, role->level);
	lua_setfield(L, -2, "level");
	lua_pushinteger(L, role->life);
	lua_setfield(L, -2, "life");
	lua_pushinteger(L,  role->blue);
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

void getkey(lua_State *L)
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

int main()
{
	initgraph(900,  780);
	loadresource();
	//putrole();

	lua_State* pL = luaL_newstate();
	luaL_openlibs(pL);
	luaL_dofile(pL, "player.lua");
	set_player(pL);

	lua_State* mapL = luaL_newstate();
	luaL_openlibs(mapL);
	luaL_dofile(mapL, "map.lua");
	set_map(mapL, map);

	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	luaL_dofile(L, "some.lua");
	//putimage(0, 0, &img[1]);
	drawmap(role.building_level);
	//loadimage(img+0,"../res/0.jpg",60,60);
	//putimage(0, 0, &img[0]);
	while (1) {
		drawmap(role.building_level);
		getkey(L);
	}
	system("pause");
	return 0;
}