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
#include <napi.h>

extern "C"{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include "MyWorkerQueue.hpp"

class MyLuaState : public Napi::ObjectWrap<MyLuaState> {
public:
    static Napi::Object Init(Napi::Env env,Napi::Object exports);
    static Napi::Object NewInstance(Napi::CallbackInfo& arg);
    lua_State* getLuaState()const{return _L;}
   
    MyLuaState(const Napi::CallbackInfo& callbackInfo);
    ~MyLuaState();
private:

    lua_State* _L;
    double _idVal;
    static Napi::FunctionReference constructor; // 创建 FunctionReference ，防止被垃圾回收

    static Napi::Value New(const Napi::CallbackInfo& info);
    Napi::Value DoFile(const Napi::CallbackInfo& info);
    Napi::Value DoString(const Napi::CallbackInfo& info);
    Napi::Value Status(const Napi::CallbackInfo& info);
    Napi::Value CallGlobalFunction(const Napi::CallbackInfo& info);
    
    MyWorkerQueue workerQueue;
    
    
    void normalCallBack(Napi::Function& cb,MyLuaWorker* worker);
    void normalGetRetCallBack(Napi::Function& cb,MyLuaWorker* worker);
};

#endif /* MyLuaState_hpp */
