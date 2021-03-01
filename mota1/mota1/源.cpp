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

struct gameRole {
	char rolename[20];
	int life;       //生命值
	int level;      //等级
	int blue;       //蓝量
	int defence;    //防御
	int attack;     //攻击
	int yellow_key; //黄钥匙
	int blue_key;   //蓝钥匙
	int red_key;    //红钥匙
	int exp;        //经验
	int building_level; //层数
	int suc; //是否成功移动
}role;

void putrole()
{
	//role.rolename = 'x';
	role.level = 0;
	role.life = 10000;
	role.blue = 200;
	role.attack = 1000;
	role.defence = 1000;
	role.yellow_key = 100;
	role.blue_key = 100;
	role.red_key = 100;
	role.exp = 0;
	role.suc = 0;
}

IMAGE monsterImg[42];
IMAGE wallImg[1];
IMAGE doorImg[1];
void loadresource()
{
	for (int i = 0; i < 42; i++)
	{
		char filename[20] = "";
		sprintf(filename, "../res/%d.jpg", i);
		loadimage(monsterImg + i, filename, 60, 60);
	}
	for (int i = 1000; i < 1001; i++)
	{
		char filename[20] = "";
		sprintf(filename, "../res/%d.jpg", i);
		loadimage(wallImg + (i-1000), filename, 60, 60);
	}
	for (int i = 2000; i < 2000; i++)
	{
		char filename[20] = "";
		sprintf(filename, "../res/%d.jpg", i);
		loadimage(doorImg + (i-2000), filename, 60, 60);
	}
}

int N = 0;

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
			if (map[N][i][j] >= 3000)
				;
			else if(map[N][i][j] >= 2000)
				putimage(x, y, doorImg + map[N][i][j]);
			else if (map[N][i][j] >= 1000)
				putimage(x, y, wallImg + map[N][i][j]);
			else
				putimage(x, y, monsterImg + map[N][i][j]);
		}
		for (int j = 13; j < 15; j++)
		{
			x = 60 * j;
			y = 60 * i;
			putimage(x, y, &monsterImg[map[0][1][11]]);
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
	outtextxy(780, 720, intToWcahr(role.red_key));
}

gameRole move(lua_State *L, gameRole role, int pos)
{
	luaL_loadfile(L, "some.lua");
	lua_getglobal(L, "move");
	lua_newtable(L);
	lua_pushinteger(L, role.level);
	lua_setfield(L, -2, "level");
	lua_pushinteger(L, role.life);
	lua_setfield(L, -2, "life");
	lua_pushinteger(L,  role.blue);
	lua_setfield(L, -2, "bule");
	lua_pushinteger(L, role.attack);
	lua_setfield(L, -2, "attack");
	lua_pushinteger(L, role.defence);
	lua_setfield(L, -2, "defence");
	lua_pushinteger(L, role.exp);
	lua_setfield(L, -2, "exp");
	lua_pushinteger(L, role.yellow_key);
	lua_setfield(L, -2, "yellow_key");
	lua_pushinteger(L, role.blue_key);
	lua_setfield(L, -2, "blue_key");
	lua_pushinteger(L, role.red_key);
	lua_setfield(L, -2, "red_key");
	lua_pushinteger(L, role.building_level);
	lua_setfield(L, -2, "building_level");
	lua_pushinteger(L, role.suc);
	lua_setfield(L, -2, "suc");
	lua_pushinteger(L, pos);

	lua_pcall(L, 2, 1, 0);
	
	lua_getfield(L, -1, "level");
	role.level = lua_tointeger(L, -1);
	lua_pop(L, -1);
	lua_getfield(L, -1, "life");
	role.life = lua_tointeger(L, -1);
	lua_pop(L, -1);
	lua_getfield(L, -1, "blue");
	role.blue = lua_tointeger(L, -1);
	lua_pop(L, -1);
	lua_getfield(L, -1, "attack");
	role.attack = lua_tointeger(L, -1);
	lua_pop(L, -1);
	lua_getfield(L, -1, "defence");
	role.defence = lua_tointeger(L, -1);
	lua_pop(L, -1);
	lua_getfield(L, -1, "exp");
	role.exp = lua_tointeger(L, -1);
	lua_pop(L, -1);
	lua_getfield(L, -1, "yellow_key");
	role.yellow_key = lua_tointeger(L, -1);
	lua_pop(L, -1);
	lua_getfield(L, -1, "blue_key");
	role.blue_key = lua_tointeger(L, -1);
	lua_pop(L, -1);
	lua_getfield(L, -1, "red_key");
	role.red_key = lua_tointeger(L, -1);
	lua_pop(L, -1);
	lua_getfield(L, -1, "building_level");
	role.building_level = lua_tointeger(L, -1);
	lua_pop(L, -1);
	lua_getfield(L, -1, "suc");
	role.suc = lua_tointeger(L, -1);
	lua_pop(L, -1);

	return role;
}

void getkey(lua_State *L)
{
	char key;
	int i, j;
	for (i = 0; i < 13; i++)
	{
		for (j = 0; j < 13; j++)
			if (map[N][i][j] == 2)
				break;
	}
	key = _getch();
	switch (key)
	{
	case 75:
		move(L, role, map[N][i][j]);
		if (role.suc == 1)
		{

		}
	}
}

int main()
{
	initgraph(900,  780);
	loadresource();
	lua_State* L;
	//putimage(0, 0, &img[1]);
	drawmap(N);
	//loadimage(img+0,"../res/0.jpg",60,60);
	//putimage(0, 0, &img[0]);
	while (1) {
		drawmap(N);
	}
	system("pause");
	return 0;
}