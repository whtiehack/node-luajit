//
//  MyLuaState.cpp
//  binding
//
//  Created by mac on 16/8/9.
//
//

#include "MyLuaState.hpp"


Nan::Persistent<v8::Function> MyLuaState::constructor;


MyLuaState::MyLuaState(double value) {
    _idVal = value;
}

MyLuaState::~MyLuaState() {
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
    
}


