#ifndef LUAUTILS_H
#define LUAUTILS_H

#include <string.h>
#include <napi.h>

extern "C"{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

char * get_str(Napi::Value val);
Napi::Value lua_to_value(lua_State* L, int);
void push_value_to_lua(lua_State* L, Napi::Value value);
#endif
