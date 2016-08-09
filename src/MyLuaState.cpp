//
//  MyLuaState.cpp
//  binding
//
//  Created by mac on 16/8/9.
//
//

#include "MyLuaState.hpp"
#include "MyLuaWorker.hpp"

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
    lua_close(_L);
}

void MyLuaState::normalCallBack(Nan::Callback* cb,MyLuaWorker* worker){
    HandleScope scope;
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



void MyLuaState::Init(v8::Local<v8::Object> exports) {
    Nan::HandleScope scope;
    
    // Prepare constructor template
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("MyLuaState").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    
    // Prototype
    Nan::SetPrototypeMethod(tpl, "doFile", DoFile);
    
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
        auto hasErr = luaL_dofile(L, nfn);
        if(hasErr){
            worker->setUserData(true,lua_tostring(L, -1));
        }else{
            worker->setUserData(false,"");
        }
  //      printf("do file  end:%s\n",(char*)nfn);
        //要释放 fn
        delete []nfn;
    },normalCallBack);
 //   printf("worker out:%p\n",nfn);
    obj->workerQueue.addQueue(worker);
    info.GetReturnValue().Set(Nan::Undefined());
}






