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
    worker->setQueueNotify([&](void)->void{
        isRunning = false;
        popQueue();
    });
    popQueue();
    return myqueue.size();
}

void MyWorkerQueue::popQueue(){
    if(isRunning){
        return;
    }
    
}