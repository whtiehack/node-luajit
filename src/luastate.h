#ifndef LUASTATE_H
#define LUASTATE_H
//
//#include <map>
//#include <node.h>
//
//#include "utils.h"
//#include <nan.h>
//
//extern "C"{
//#include <lua.h>
//#include <lauxlib.h>
//#include <lualib.h>
//}
//
//class LuaState : public Nan::ObjectWrap{
// public:
//  lua_State* lua_;
//  char* name_;
//
//  static void Init(v8::Handle<v8::Object> target);
//  static int CallFunction(lua_State* L);
//
// private:
//  LuaState();
//  ~LuaState();
//
//  static v8::Handle<v8::Value> New(const Nan::FunctionCallbackInfo<v8::Value>& args);
//  static v8::Handle<v8::Value> Close(const Nan::FunctionCallbackInfo<v8::Value>& args);
//  static v8::Handle<v8::Value> GetName(const Nan::FunctionCallbackInfo<v8::Value>& args);
//
//  static v8::Handle<v8::Value> CollectGarbage(const Nan::FunctionCallbackInfo<v8::Value>& args);
//  static v8::Handle<v8::Value> CollectGarbageSync(const Nan::FunctionCallbackInfo<v8::Value>& args);
//
//  static v8::Handle<v8::Value> Status(const Nan::FunctionCallbackInfo<v8::Value>& args);
//  static v8::Handle<v8::Value> StatusSync(const Nan::FunctionCallbackInfo<v8::Value>& args);
//
//
//  static v8::Handle<v8::Value> DoFileSync(const Nan::FunctionCallbackInfo<v8::Value>& args);
//  static v8::Handle<v8::Value> DoFile(const Nan::FunctionCallbackInfo<v8::Value>& args);
//
//  static v8::Handle<v8::Value> DoStringSync(const Nan::FunctionCallbackInfo<v8::Value>& args);
//  static v8::Handle<v8::Value> DoString(const Nan::FunctionCallbackInfo<v8::Value>& args);
//
//  static v8::Handle<v8::Value> SetGlobal(const Nan::FunctionCallbackInfo<v8::Value>& args);
//  static v8::Handle<v8::Value> GetGlobal(const Nan::FunctionCallbackInfo<v8::Value>& args);
//
//  static v8::Handle<v8::Value> RegisterFunction(const Nan::FunctionCallbackInfo<v8::Value>& args);
//
//  static v8::Handle<v8::Value> Push(const Nan::FunctionCallbackInfo<v8::Value>& args);
//  static v8::Handle<v8::Value> Pop(const Nan::FunctionCallbackInfo<v8::Value>& args);
//  static v8::Handle<v8::Value> GetTop(const Nan::FunctionCallbackInfo<v8::Value>& args);
//  static v8::Handle<v8::Value> SetTop(const Nan::FunctionCallbackInfo<v8::Value>& args);
//  static v8::Handle<v8::Value> Replace(const Nan::FunctionCallbackInfo<v8::Value>& args);
//};
#endif
