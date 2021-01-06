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
    
    // AsyncQueueWorker(worker);
    worker->Queue();
}
