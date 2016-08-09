//
//  MyLuaWorker.cpp
//  binding
//
//  Created by mac on 16/8/9.
//
//

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


void MyLuaWorker::Execute () {
    printf("WorkerCall begin:%ld\n",time(0));
    _workerCall(this);
    printf("WorkerCall end  :%ld\n",time(0));
}



void MyLuaWorker::HandleOKCallback () {
    printf("WorkerCall  handle ok callback:%ld\n",time(0));
    _finishCb(callback,this);
    printf("WorkerCall  handle ok callback end:%ld\n",time(0));
    _queueNotify(this);
//    Nan::HandleScope scope;
//    
//    Local<Value> argv[] = {
//        Null()
//        , New<Number>(estimate)
//    };
//    
//    callback->Call(2, argv);
}