#include <stdlib.h>
#include "utils.h"
#include <nan.h>

char * get_str(v8::Local<v8::Value> val){
 if(!val->IsString()){
   Nan::ThrowError("Argument Must Be A String");
   return NULL;
 }

 v8::String::Utf8Value val_string(val);
 char * val_char_ptr = (char *) malloc(val_string.length() + 1);
 strcpy(val_char_ptr, *val_string);
 return val_char_ptr;
}


v8::Local<v8::Value> lua_to_value(lua_State* L, int i){
 switch(lua_type(L, i)){
 case LUA_TBOOLEAN:
	 return Nan::New((int)lua_toboolean(L, i));
   break;
 case LUA_TNUMBER:
	 return Nan::New(lua_tonumber(L, i));
   break;
 case LUA_TSTRING:
	 return Nan::New((char *)lua_tostring(L, i)).ToLocalChecked();
   break;
 case LUA_TTABLE:
   {
     v8::Local<v8::Object> obj = Nan::New<v8::Object>();
     lua_pushnil(L);
     while(lua_next(L, -2) != 0){
	v8::Local<v8::Value> key = lua_to_value(L, -2);
	v8::Local<v8::Value> value = lua_to_value(L, -1);
	obj->Set(key, value);
	lua_pop(L, 1);
     }
     return obj;
     break;
   }
 default:
	 return Nan::Undefined();
   break;
 }
}

void push_value_to_lua(lua_State* L, v8::Local<v8::Value> value){
	if (value->IsString()){
   lua_pushstring(L, get_str(value->ToString()));
 }else if(value->IsNumber()){
	 int i_value = value->NumberValue();
   lua_pushinteger(L, i_value);
 }else if(value->IsBoolean()){
   int b_value = (int)value->ToBoolean()->Value();
   lua_pushboolean(L, b_value);
 }else if(value->IsObject()){
   lua_newtable(L);
   v8::Local<v8::Object> obj = value->ToObject();
   v8::Local<v8::Array> keys = obj->GetPropertyNames();
   for(uint32_t i = 0; i < keys->Length(); ++i){
     v8::Local<v8::Value> key = keys->Get(i);
     v8::Local<v8::Value> val = obj->Get(key);
     push_value_to_lua(L, key);
     push_value_to_lua(L, val);
     lua_settable(L, -3);
   }
 }else{
   lua_pushnil(L);
 }
}


