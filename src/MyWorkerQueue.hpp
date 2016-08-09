//
//  MyWorkerQueue.hpp
//  binding
//
//  Created by mac on 16/8/9.
//
//

#ifndef MyWorkerQueue_hpp
#define MyWorkerQueue_hpp

#include <stdio.h>
#include <nan.h>
#include <deque>
class MyLuaWorker;

class MyWorkerQueue {
public:
    MyWorkerQueue():isRunning(false){}
    int addQueue(MyLuaWorker*);
    
private:
    bool isRunning;
    std::deque<MyLuaWorker*> myqueue;
    
    void popQueue();
};

#endif /* MyWorkerQueue_hpp */
