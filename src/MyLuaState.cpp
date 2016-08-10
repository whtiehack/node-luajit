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
#include <node.h>

using v8::Function;
using v8::Local;
using v8::Number;
using v8::Value;
using Nan::AsyncQueueWorker;
using Nan::AsyncWorker;
using Nan::Callback;
using Nan::HandleScope;
using Nan::New;
using Nan::Null;
using Nan::To;

Nan::Persistent<v8::Function> MyLuaState::constructor;


MyLuaState::MyLuaState(double value) {
    _idVal = value;
    _L = lua_open();
    luaL_openlibs(_L);
}

MyLuaState::~MyLuaState() {
    printf("My LuaState ~~~ 析构");
    fflush(stdout);
    lua_close(_L);
}

void MyLuaState::normalCallBack(Nan::Callback* cb,MyLuaWorker* worker){
    HandleScope scope;
    if(!cb){
        return;
    }
    auto ret = worker->getUserData();
    v8::Local<v8::Value> err;
    v8::Local<v8::Value> arg2;
    if(ret.hasErr){
        err = Nan::New(ret.buff).ToLocalChecked();
        arg2 = Nan::Undefined();
    }else{
        err = Nan::Null();
        arg2 = Nan::New(ret.buff).ToLocalChecked();
    }
    v8::Local<v8::Value> argv[] = {
        err,arg2
    };
    cb->Call(2, argv);
}


// worker->userParam = obj; 要设置成 MyLuaState 实例
void MyLuaState::normalGetRetCallBack(Nan::Callback* cb,MyLuaWorker* worker){
    HandleScope scope;
    if(!cb){
        return;
    }
    auto ret = worker->getUserData();
    v8::Local<v8::Value> err;
    if(ret.hasErr){
        v8::Local<v8::Value> arg2;
        err = Nan::New(ret.buff).ToLocalChecked();
        arg2 = Nan::Undefined();
        v8::Local<v8::Value> argv[] = {
            err,arg2
        };
        cb->Call(2, argv);
    }else{
        MyLuaState* obj = (MyLuaState*)worker->userParam;
        err = Nan::Null();
        auto L = obj->getLuaState();
        int len = lua_gettop(L) - worker->getUserData().customVal;
        if(len){
            //lua_to_value
            v8::Local<v8::Value> *argv  = new v8::Local<v8::Value>[len+1];
            argv[0] = Nan::Null();
            int i = 1;
            while (i<=len) {
                argv[i] = lua_to_value(L, -1);
                i++;
                lua_pop(L,1);
            }
            cb->Call(len+1, argv);
            delete []argv;
        }else{
            v8::Local<v8::Value> argv[] = {
                err,Nan::New(ret.buff).ToLocalChecked()
            };
            cb->Call(2, argv);
        }
    }

    
}



void MyLuaState::Init(v8::Local<v8::Object> exports) {
    Nan::HandleScope scope;
    
    // Prepare constructor template
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("MyLuaState").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    
    // Prototype
    Nan::SetPrototypeMethod(tpl, "doFile", DoFile);
    Nan::SetPrototypeMethod(tpl, "doString", DoString);
    Nan::SetPrototypeMethod(tpl, "status", Status);
    Nan::SetPrototypeMethod(tpl, "callGlobalFunction", CallGlobalFunction);
    
    
    constructor.Reset(tpl->GetFunction());
    exports->Set(Nan::New("MyLuaState").ToLocalChecked(), tpl->GetFunction());
}

void MyLuaState::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    if (info.IsConstructCall()) {
        // Invoked as constructor: `new MyObject(...)`
        double value = info[0]->IsUndefined() ? 0 : info[0]->NumberValue();
        MyLuaState* obj = new MyLuaState(value);
        obj->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
    } else {
        // Invoked as plain function `MyObject(...)`, turn into construct call.
        const int argc = 1;
        v8::Local<v8::Value> argv[argc] = { info[0] };
        v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
        info.GetReturnValue().Set(cons->NewInstance(argc, argv));
    }
}




v8::Local<v8::Object> MyLuaState::NewInstance(v8::Local<v8::Value> arg) {
    Nan::EscapableHandleScope scope;
    
    const unsigned argc = 1;
    v8::Local<v8::Value> argv[argc] = { arg };
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);
    
    return scope.Escape(instance);
}

void MyLuaState::DoFile(const Nan::FunctionCallbackInfo<v8::Value>& info){
    if(info.Length()<1){
        Nan::ThrowTypeError("Wrong number of arguments");
        return;
    }
    if(!info[0]->IsString()){
        Nan::ThrowTypeError("arg 1 is not a string  need filepath");
        return;
    }
    if(info.Length() > 1 && !info[1]->IsFunction()){
        Nan::ThrowTypeError("arg 2 is not a function ");
        return;
    }
    //可能要copy出来
    v8::String::Utf8Value filename(info[0]->ToString());
    const char* fn = *filename;
    char* nfn = new char[filename.length()+1];
 //   printf(" fnfnfnfnfn :%s\n",fn);
    strcpy(nfn,fn);
//    printf(" fnfnfnfnfn1111 :%s\n",nfn);
    MyLuaState* obj = ObjectWrap::Unwrap<MyLuaState>(info.This());
    Nan::Callback *callback = nullptr;
    if(info.Length()>1){
        callback = new Nan::Callback(info[1].As<Function>());
    }
    
    MyLuaWorker* worker = new MyLuaWorker(callback,[=](MyLuaWorker* worker){
        auto L = obj->getLuaState();
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
            const char * buff = nullptr;
            if(lua_gettop(L) - worker->getUserData().customVal){
                buff = lua_tostring(L, -1);
                lua_pop(L,1);
            }
            worker->setUserData(false,buff);
        }
  //      printf("do file  end:%s\n",(char*)nfn);
        //要释放 fn
        delete []nfn;
    },normalCallBack);
 //   printf("worker out:%p\n",nfn);
    obj->workerQueue.addQueue(worker);
    info.GetReturnValue().Set(Nan::Undefined());
}





void MyLuaState::DoString(const Nan::FunctionCallbackInfo<v8::Value>& info){
    if(info.Length()<1){
        Nan::ThrowTypeError("Wrong number of arguments");
        return;
    }
    if(!info[0]->IsString()){
        Nan::ThrowTypeError("arg 1 is not a string  need filepath");
        return;
    }
    if(info.Length() > 1 && !info[1]->IsFunction()){
        Nan::ThrowTypeError("arg 2 is not a function ");
        return;
    }
    //可能要copy出来
    v8::String::Utf8Value filename(info[0]->ToString());
    const char* fn = *filename;
    char* nfn = new char[filename.length()+1];
    //   printf(" fnfnfnfnfn :%s\n",fn);
    strcpy(nfn,fn);
    //    printf(" fnfnfnfnfn1111 :%s\n",nfn);
    MyLuaState* obj = ObjectWrap::Unwrap<MyLuaState>(info.This());
    Nan::Callback *callback = nullptr;
    if(info.Length()>1){
        callback = new Nan::Callback(info[1].As<Function>());
    }
    
    MyLuaWorker* worker = new MyLuaWorker(callback,[=](MyLuaWorker* worker){
        auto L = obj->getLuaState();
        //      printf("worker int:%p\n",nfn);
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
        //      printf("do file  end:%s\n",(char*)nfn);
        //要释放 fn
        delete []nfn;
    },normalGetRetCallBack);
    worker->userParam = obj;
    //   printf("worker out:%p\n",nfn);
    obj->workerQueue.addQueue(worker);
    info.GetReturnValue().Set(Nan::Undefined());
}


void MyLuaState::Status(const Nan::FunctionCallbackInfo<v8::Value>& info){
    if(info.Length()<1){
        Nan::ThrowTypeError("Wrong number of arguments");
        return;
    }
    if(!info[0]->IsFunction()){
        Nan::ThrowTypeError("arg 1 is not a function  need function");
        return;
    }
    MyLuaState* obj = ObjectWrap::Unwrap<MyLuaState>(info.This());
    Nan::Callback *callback = nullptr;
    callback = new Nan::Callback(info[0].As<Function>());
    
    MyLuaWorker* worker = new MyLuaWorker(callback,[=](MyLuaWorker* worker){
        auto L = obj->getLuaState();
        int status = lua_status(L);
        worker->userParam = reinterpret_cast<void*>(status);
        worker->setUserData(false,"");
    },[](Nan::Callback * cb,MyLuaWorker* worker){
        long status = reinterpret_cast<long>(worker->userParam);
        v8::Local<v8::Value> argv[] = {
            Nan::Null(),Nan::New((int)status)
        };
        cb->Call(2, argv);
    });
    obj->workerQueue.addQueue(worker);
    info.GetReturnValue().Set(Nan::Undefined());

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



char* getValStr(v8::Local<v8::Value>& val){
    if(!val->IsString()){
        return NULL;
    }
    v8::String::Utf8Value val_string(val);
    char * val_char_ptr = new char[val_string.length() + 1];
    strcpy(val_char_ptr, *val_string);
    return val_char_ptr;
}

void transVal(v8::Local<v8::Value> value,Prams* nowVal){
    if (value->IsString()){
        nowVal->type = Prams::ParmType::STRING;
        strcpy(nowVal->valStr, get_str(value->ToString()));
        nowVal->valStr = getValStr(value);
    }else if(value->IsNumber()){
        double i_value = value->ToNumber()->Value();
        nowVal->type = Prams::NUMBER;
        nowVal->valNum = i_value;
    }else if(value->IsBoolean()){
        nowVal->valBool = (int)value->ToBoolean()->Value();
        nowVal->type = Prams::BOOLEAN;
    }else if(value->IsObject()){
        
        v8::Local<v8::Object> obj = value->ToObject();
        v8::Local<v8::Array> keys = obj->GetPropertyNames();
        nowVal->type = Prams::TABLE;
        Prams* table = new Prams[keys->Length()];
        nowVal->valTable = table;
        nowVal->tableLen = keys->Length();
        for(uint32_t i = 0; i < keys->Length(); ++i){
            v8::Local<v8::Value> key = keys->Get(i);
            v8::Local<v8::Value> val = obj->Get(key);
            table[i].tableKey = new Prams;
            transVal(key, table[i].tableKey);
            transVal(val, &table[i]);
        }
    }else{
        nowVal->type = Prams::NIL;
    }
}



Prams* transData2Params(const Nan::FunctionCallbackInfo<v8::Value>& info,int start,int end){
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

void MyLuaState::CallGlobalFunction(const Nan::FunctionCallbackInfo<v8::Value>& info){
    if(info.Length()<1){
        Nan::ThrowTypeError("Wrong number of arguments");
        return;
    }
    if(!info[0]->IsString()){
        Nan::ThrowTypeError("arg 1 is not a String  need String");
        return;
    }
    v8::String::Utf8Value funName(info[0]->ToString());
    char* functionName = new char[funName.length()+1];
    //   printf(" fnfnfnfnfn :%s\n",fn);
    strcpy(functionName,*funName);
    MyLuaState* obj = ObjectWrap::Unwrap<MyLuaState>(info.This());
    Nan::Callback *callback = nullptr;
    int end = info.Length();
    if(info[info.Length()-1]->IsFunction()){
        callback = new Nan::Callback(info[info.Length()-1].As<Function>());
        end-=1;
    }
    Prams* parameters = transData2Params(info, 1, end);
    MyLuaWorker* worker = new MyLuaWorker(callback,[=](MyLuaWorker* worker){
        auto L = obj->getLuaState();
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
    },normalGetRetCallBack);
    worker->userParam = obj;
    obj->workerQueue.addQueue(worker);
    info.GetReturnValue().Set(Nan::Undefined());
    
}







