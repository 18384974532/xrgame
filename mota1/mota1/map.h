
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

void loadresource();
void drawmap(int n);
void set_map(lua_State* L, int map[][13][13]);
