#include <stdlib.h>
#include "utils.h"
#include <napi.h>

char * get_str(Napi::Value val){
    if(!val.IsString()){
        Napi::Error::New(val.Env(), "Argument Must Be A String");
        return NULL;
    }
    Napi::String val_string(val.Env(),val);
    char * val_char_ptr = (char *) malloc(val_string.Utf8Value().length() + 1);
    strcpy(val_char_ptr, val_string.Utf8Value().c_str());
    return val_char_ptr;
}


Napi::Value lua_to_value(Napi::Env env, lua_State* L, int i){
 switch(lua_type(L, i)){
 case LUA_TBOOLEAN:
         return Napi::Boolean::New(env,(int)lua_toboolean(L, i));
   break;
 case LUA_TNUMBER:
	 return Napi::Number::New(env, lua_tonumber(L, i));
   break;
 case LUA_TSTRING:
	 return Napi::String::New(env,(char *)lua_tostring(L, i));
   break;
 case LUA_TTABLE:
   {
       Napi::Object obj = Napi::Object::New(env);
     lua_pushnil(L);
     while(lua_next(L, -2) != 0){
	Napi::Value key = lua_to_value(env,L, -2);
         Napi::Value value = lua_to_value(env,L, -1);
	obj.Set(key, value);
	lua_pop(L, 1);
     }
     return obj;
     break;
   }
 default:
         return env.Undefined();
   break;
 }
}

void push_value_to_lua(lua_State* L, Napi::Value value){
	if (value.IsString()){
   lua_pushstring(L, get_str(value));
 }else if(value.IsNumber()){
   int i_value = value.ToNumber();
   lua_pushinteger(L, i_value);
 }else if(value.IsBoolean()){
   int b_value = (int)value.ToBoolean();
   lua_pushboolean(L, b_value);
 }else if(value.IsObject()){
   lua_newtable(L);
   Napi::Object obj = value.ToObject();
   Napi::Array keys = obj.GetPropertyNames();
   for(uint32_t i = 0; i < keys.Length(); ++i){
     Napi::Value key = keys.Get(i);
       Napi::Value val = obj.Get(key);
     push_value_to_lua(L, key);
     push_value_to_lua(L, val);
     lua_settable(L, -3);
   }
 }else{
   lua_pushnil(L);
 }
}


