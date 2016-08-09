//
//  MyLuaWorker.hpp
//  binding
//
//  Created by mac on 16/8/9.
//
//

#ifndef MyLuaWorker_hpp
#define MyLuaWorker_hpp

#include <stdio.h>
#include <nan.h>
#include <functional>
class MyWorkerQueue;


//typedef void(*FinishCallBack)(Nan::Callback *);
typedef std::function<void(Nan::Callback *)> FinishCallBack;
//typedef void(*WorkerCall)(void);
typedef std::function<void(void)> WorkerCall;

class MyLuaWorker : public Nan::AsyncWorker {
public:
    MyLuaWorker(Nan::Callback *callback,WorkerCall workerCall,FinishCallBack finishCb) :
        Nan::AsyncWorker(callback),_finishCb(finishCb),_workerCall(workerCall)
    {
        
    }
    ~MyLuaWorker(){}
    
    void Execute ();
    
    // Executed when the async work is complete
    // this function will be run inside the main event loop
    // so it is safe to use V8 again
    void HandleOKCallback ();
    
    void setQueueNotify(WorkerCall qn){
        _queueNotify = qn;
    }
private:
    FinishCallBack _finishCb;
    WorkerCall _workerCall;
    WorkerCall _queueNotify;
};
#endif /* MyLuaWorker_hpp */
