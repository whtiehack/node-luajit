//
//  MyWorkerQueue.cpp
//  binding
//
//  Created by mac on 16/8/9.
//
//

#include "MyWorkerQueue.hpp"
#include "MyLuaWorker.hpp"
#include <functional>


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

int MyWorkerQueue::addQueue(MyLuaWorker* worker){
    myqueue.push_front(worker);
    worker->setQueueNotify([&](MyLuaWorker* worker)->void{
        isRunning = false;
        popQueue();
    });
    popQueue();
    return myqueue.size();
}

void MyWorkerQueue::popQueue(){
    if(isRunning || myqueue.empty()){
        return;
    }
    auto worker = myqueue.back();
    isRunning = true;
    myqueue.pop_back();
    AsyncQueueWorker(worker);
}