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
	int level;      //�ȼ�
	int exp;        //����
	int life;       //����ֵ
	int blue;       //����
	int attack;     //����
	int defence;    //����
	int yellow_key; //��Կ��
	int blue_key;   //��Կ��
	int red_key;    //��Կ��
	int building_level; //����
	int suc; //�Ƿ�ɹ��ƶ�
};

void set_player(lua_State* L);
