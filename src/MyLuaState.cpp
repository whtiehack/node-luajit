//
//  MyLuaState.cpp
//  binding
//
//  Created by mac on 16/8/9.
//
//

#include "MyLuaState.hpp"
#include "MyLuaWorker.hpp"
#include "utils.h"
#include <napi.h>


Napi::FunctionReference MyLuaState::constructor;

extern "C"{
 int luaopen_cjson(lua_State *l);
}

double glboalInstanceVal = 0;

MyLuaState::MyLuaState(const Napi::CallbackInfo& info):
        Napi::ObjectWrap<MyLuaState>(info){
    Napi::Number value;
    if(info[0].IsNumber()){
        value= info[0].As<Napi::Number>();
        glboalInstanceVal = value;
    }else{
        value  = Napi::Number::New(info.Env(), ++glboalInstanceVal);
    }
    _idVal = value;
    _L = lua_open();
    int top = lua_gettop(_L);
    luaL_openlibs(_L);
    luaopen_cjson(_L);
    lua_pushvalue(_L, -1);
    lua_setglobal(_L, "cjson");
    lua_settop(_L, top);
}

MyLuaState::~MyLuaState() {
    printf("My LuaState ~~~ 析构 %f\n",_idVal);
    fflush(stdout);
    lua_close(_L);
}

void MyLuaState::normalCallBack(Napi::Function& _cb,MyLuaWorker* worker){
    if(!_cb){
        return;
    }
    auto env = worker->Callback().Env();
    Napi::HandleScope scope(env);
    auto ret = worker->getUserData();
    Napi::Value err;
    Napi::Value arg2;
    if(ret.hasErr){
        err = Napi::String::New(env,ret.buff);
        arg2 = env.Undefined();
    }else{
        err = env.Null();
        arg2 = Napi::String::New(env,ret.buff);
    }
    worker->Callback().Call({err,arg2});
}


// worker->userParam = obj; 要设置成 MyLuaState 实例
void MyLuaState::normalGetRetCallBack(Napi::Function&  ccx,MyLuaWorker* worker){
    if(!ccx){
        return;
    }
    auto env = worker->Callback().Env();
    Napi::HandleScope scope(env);
    auto ret = worker->getUserData();
    Napi::Value err;
    if(ret.hasErr){
        Napi::Value arg2;
        err = Napi::String::New(env,ret.buff);
        arg2 = env.Undefined();
        worker->Callback().Call({err,arg2});
    }else{
        MyLuaState* obj = (MyLuaState*)worker->userParam;
        err = env.Null();
        auto L = obj->getLuaState();
        int len = lua_gettop(L) - worker->getUserData().customVal;
        if(len){
            //lua_to_value
            napi_value *argv  = new napi_value[len+1];
            argv[0] = env.Null();
            int i = 1;
            while (i<=len) {
                argv[i] = lua_to_value(env,L, i);
                i++;
            }
            lua_settop(L, worker->getUserData().customVal);
            worker->Callback().Call(env.Null(), size_t(len+1), (napi_value*)argv);
            delete []argv;
        }else{
            worker->Callback().Call({err,Napi::String::New(env,ret.buff)});
        }
    }

    
}


// exports.MyLuaState = class { constructor(id){},doFile,doString,status,callGlobalFunction, static New}
Napi::Object MyLuaState::Init(Napi::Env env,Napi::Object exports) {
    Napi::HandleScope scope(env);
    
    Napi::Function func = DefineClass(env, "MyLuaState", {
        InstanceMethod<&MyLuaState::DoFile>("doFile"),
        InstanceMethod<&MyLuaState::DoString>("doString"),
        InstanceMethod<&MyLuaState::Status>("status"),
        InstanceMethod<&MyLuaState::CallGlobalFunction>("callGlobalFunction"),
        StaticMethod<&MyLuaState::New>("New"),
    });
    
    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    exports.Set("MyLuaState", func);
    
    env.SetInstanceData<Napi::FunctionReference>(constructor);

    return exports;
}



// MyLuaState.New(121)
Napi::Value MyLuaState::New(const Napi::CallbackInfo& info) {
    // Retrieve the instance data we stored during `Init()`. We only stored the
    // constructor there, so we retrieve it here to create a new instance of the
    // JS class the constructor represents.
    Napi::FunctionReference* constructor =
        info.Env().GetInstanceData<Napi::FunctionReference>();
    Napi::Number value;
    if(info[0].IsNumber()){
        value= info[0].As<Napi::Number>();
        glboalInstanceVal = value;
    }else{
        value  = Napi::Number::New(info.Env(), ++glboalInstanceVal);
    }
    return constructor->New({ Napi::Number::New(info.Env(), value)});
}

Napi::Value MyLuaState::DoFile(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    if(info.Length()<1){
        Napi::Error::New(info.Env(), "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if(!info[0].IsString()){
        Napi::Error::New(info.Env(), "arg 1 is not a string  need filepath").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if(info.Length() > 1 && !info[1].IsFunction()){
        Napi::Error::New(info.Env(), "arg 2 is not a function").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    //可能要copy出来
    auto filename = info[0].ToString().Utf8Value();
    const char* fn = filename.c_str();
    char* nfn = new char[filename.length()+1];
 //   printf(" fnfnfnfnfn :%s\n",fn);
    strcpy(nfn,fn);
//    printf(" fnfnfnfnfn1111 :%s\n",nfn);
    Napi::Function callback;
    if(info.Length()>1){
        callback = info[1].As<Napi::Function>();
    }
    
    MyLuaWorker* worker = new MyLuaWorker(callback,[=](MyLuaWorker* worker){
        auto L = this->getLuaState();
  //      printf("worker int:%p\n",nfn);
  //      printf("begin do file :%s\n",nfn);
        int top = lua_gettop(L);
        worker->getUserData().customVal = top;
  //      printf("top:%d  111str :%s\n",top,nfn);
        auto hasErr = luaL_dofile(L, nfn);
   //     printf("top:%d  2222str :%s\n",top,nfn);
        if(hasErr){
            worker->setUserData(true,lua_tostring(L, -1));
            lua_pop(L, 1);
        }else{
            worker->setUserData(false,"");
        }
  //      printf("do file  end:%s\n",(char*)nfn);
        //要释放 fn
        delete []nfn;
    },[=](Napi::Function& cb,MyLuaWorker* worker){
        this->normalGetRetCallBack(cb, worker);
    });
    worker->userParam = this;
 //   printf("worker out:%p\n",nfn);
    int nowqueue = this->workerQueue.addQueue(worker);
    return Napi::Number::New(env, nowqueue);
}





Napi::Value MyLuaState::DoString(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    if(info.Length()<1){
        Napi::Error::New(info.Env(), "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if(!info[0].IsString()){
        Napi::Error::New(info.Env(), "arg 1 is not a string  need lua string").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if(info.Length() > 1 && !info[1].IsFunction()){
        Napi::Error::New(info.Env(), "arg 2 is not a function").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    //可能要copy出来
    auto filename = info[0].ToString().Utf8Value();
    const char* fn = filename.c_str();
    char* nfn = new char[filename.length()+1];
    //   printf(" fnfnfnfnfn :%s\n",fn);
    strcpy(nfn,fn);
    // printf(" fnfnfnfnfn1111 :%s\n",nfn);
    Napi::Function callback;
    if(info.Length()>1){
        callback = info[1].As<Napi::Function>();
    }
    
    MyLuaWorker* worker = new MyLuaWorker(callback,[=](MyLuaWorker* worker){
        // printf("DoString worker int:%p\n",nfn);
        auto L = this->getLuaState();
        //
        //      printf("begin do file :%s\n",nfn);
        int top = lua_gettop(L);
        worker->getUserData().customVal = top;
    //    printf("top:%d  str :%s\n",top,nfn);
        auto hasErr = luaL_dostring(L, nfn);
  //      printf("top:%d \n",top);
        if(hasErr){
            worker->setUserData(true,lua_tostring(L, -1));
            lua_pop(L, 1);
        }else{
            worker->setUserData(false,"");
        }
        // printf("DoString  end:%s\n",(char*)nfn);
        // 要释放 fn
        delete []nfn;
    },[=](Napi::Function& cb,MyLuaWorker* worker){
        // printf("DoString  callback\n");
        this->normalGetRetCallBack(cb, worker);
    });
    worker->userParam = this;
    //   printf("worker out:%p\n",nfn);
    int nowqueue = this->workerQueue.addQueue(worker);
    return Napi::Number::New(env, nowqueue);
}


Napi::Value MyLuaState::Status(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    if(info.Length()<1){
        Napi::Error::New(info.Env(), "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if(!info[0].IsFunction()){
        Napi::Error::New(info.Env(), "arg 1 is not a function  need function").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    Napi::Function callback= info[0].As<Napi::Function>();
    
    MyLuaWorker* worker = new MyLuaWorker(callback,[=](MyLuaWorker* worker){
        auto L = this->getLuaState();
        int status = lua_status(L);
        worker->userParam = reinterpret_cast<void*>(status);
        worker->setUserData(false,"");
    },[=](Napi::Function& __cb,MyLuaWorker* worker){
        auto env = worker->Callback().Env();
        long status = reinterpret_cast<long>(worker->userParam);
        worker->Callback().Call({env.Null(),Napi::Number::New(env, status)});
    });
    int nowqueue = this->workerQueue.addQueue(worker);
    return Napi::Number::New(env, nowqueue);

}



struct Prams{
    enum ParmType {
        NUMBER,
        STRING,
        TABLE,
        BOOLEAN,
        NIL
    };
    ParmType type;
    Prams* tableKey;
    int tableLen;
    union  {
        bool valBool;
        char *valStr;
        double valNum;
        Prams* valTable;
    };
};



char* getValStr(Napi::Value val){
    if(!val.IsString()){
        return NULL;
    }
    auto val_string = val.ToString().Utf8Value();
    char * val_char_ptr = new char[val_string.length() + 1];
    strcpy(val_char_ptr, val_string.c_str());
    return val_char_ptr;
}

void transVal(Napi::Value value,Prams* nowVal){
    if (value.IsString()){
        nowVal->type = Prams::ParmType::STRING;
        nowVal->valStr = getValStr(value);
    }else if(value.IsNumber()){
        double i_value = value.ToNumber();
        nowVal->type = Prams::NUMBER;
        nowVal->valNum = i_value;
    }else if(value.IsBoolean()){
        nowVal->valBool = (int)value.ToBoolean();
        nowVal->type = Prams::BOOLEAN;
    }else if(value.IsObject()){
        Napi::Object obj = value.ToObject();
        Napi::Array keys = obj.GetPropertyNames();
        nowVal->type = Prams::TABLE;
        Prams* table = new Prams[keys.Length()];
        nowVal->valTable = table;
        nowVal->tableLen = keys.Length();
        for(uint32_t i = 0; i < keys.Length(); ++i){
            Napi::Value key = keys.Get(i);
            Napi::Value val = obj.Get(key);
            table[i].tableKey = new Prams;
            transVal(key, table[i].tableKey);
            transVal(val, &table[i]);
        }
    }else{
        nowVal->type = Prams::NIL;
    }
}



Prams* transData2Params(const Napi::CallbackInfo& info,int start,int end){
    int len = end-start;
    if (len<=0) {
        return nullptr;
    }
    Prams* retArr = new Prams[len];
    int i = 0;
    while (i<len) {
        transVal(info[start++], &retArr[i]);
        i++;
    }
    return retArr;
}


void transLuaVal(lua_State* L,Prams* val){
    if (val->type == Prams::STRING){
        lua_pushstring(L, val->valStr);
        delete []val->valStr;
    }else if(val->type == Prams::NUMBER){
        lua_pushinteger(L, val->valNum);
    }else if(val->type == Prams::BOOLEAN){
        lua_pushboolean(L, val->valBool);
    }else if(val->type == Prams::TABLE){
        lua_newtable(L);
        Prams* valTblArr = val->valTable;
        int tableLen = val->tableLen;
        for(int i = 0; i < tableLen; ++i){
            transLuaVal(L, valTblArr[i].tableKey);
            delete valTblArr[i].tableKey;
            transLuaVal(L, &valTblArr[i]);
            lua_settable(L, -3);
        }
        delete[] valTblArr;
    }else{
        lua_pushnil(L);
    }
}

void transParams2LuaData(lua_State* L,Prams* arr,int len){
    int i = 0;
    while (i<len) {
        transLuaVal(L,&arr[i]);
        i++;
    }
    delete []arr;
}

Napi::Value MyLuaState::CallGlobalFunction(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    if(info.Length()<1){
        Napi::Error::New(info.Env(), "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    if(!info[0].IsString()){
        Napi::Error::New(info.Env(), "arg 1 is not a String  need String").ThrowAsJavaScriptException();
        return env.Undefined();
    }
    auto funName = info[0].ToString().Utf8Value();
    char* functionName = new char[funName.length()+1];
    //   printf(" fnfnfnfnfn :%s\n",fn);
    strcpy(functionName,funName.c_str());
    Napi::Function callback;
    int end = (int)info.Length();
    if(info[info.Length()-1].IsFunction()){
        callback = info[info.Length()-1].As<Napi::Function>();
        end-=1;
    }
    Prams* parameters = transData2Params(info, 1, end);
    MyLuaWorker* worker = new MyLuaWorker(callback,[=](MyLuaWorker* worker){
        auto L = this->getLuaState();
        int top = lua_gettop(L);
        worker->getUserData().customVal = top;
        lua_getglobal(L, functionName);
        transParams2LuaData(L,parameters,end-1);
        if(lua_pcall(L, end-1, LUA_MULTRET, 0)){
            worker->setUserData(true,lua_tostring(L, -1));
            lua_pop(L, 1);
        }else{
            worker->setUserData(false,"");
        }
        delete []functionName;
    },[=](Napi::Function& cb,MyLuaWorker* worker){
        this->normalGetRetCallBack(cb, worker);
    });
    worker->userParam = this;
    int nowqueue = this->workerQueue.addQueue(worker);
    return Napi::Number::New(env, nowqueue);
    
}







