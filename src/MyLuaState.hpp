//
//  MyLuaState.hpp
//  binding
//
//  Created by mac on 16/8/9.
//
//

#ifndef MyLuaState_hpp
#define MyLuaState_hpp

#include <stdio.h>
#include <nan.h>

extern "C"{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include "MyWorkerQueue.hpp"

class MyLuaState : public Nan::ObjectWrap {
public:
    static void Init(v8::Local<v8::Object> exports);
    static v8::Local<v8::Object> NewInstance(v8::Local<v8::Value> arg);
    lua_State* getLuaState()const{return _L;}
    
private:
    MyLuaState(double value);
    ~MyLuaState();
    lua_State* _L;
    double _idVal;
    static Nan::Persistent<v8::Function> constructor;

    static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);
    static void DoFile(const Nan::FunctionCallbackInfo<v8::Value>& info);
    static void DoString(const Nan::FunctionCallbackInfo<v8::Value>& info);
    
    MyWorkerQueue workerQueue;
    
    
    static void normalCallBack(Nan::Callback* cb,MyLuaWorker* worker);
    static void normalGetRetCallBack(Nan::Callback* cb,MyLuaWorker* worker);
};

#endif /* MyLuaState_hpp */
