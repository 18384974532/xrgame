#pragma once
#include<stdio.h>
#include<string.h>
#include<graphics.h>
#include<stdlib.h>
#include<conio.h>

extern "C"
{
#include<lua.h>
#include<lauxlib.h>
#include<lualib.h>
}

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
};

void set_player(lua_State* L);
