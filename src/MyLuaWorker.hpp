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

class MyLuaWorker;
//typedef void(*FinishCallBack)(Nan::Callback *);
typedef std::function<void(Nan::Callback *,MyLuaWorker* worker)> FinishCallBack;
//typedef void(*WorkerCall)(void);
typedef std::function<void(MyLuaWorker*)> WorkerCall;

class MyLuaWorker : public Nan::AsyncWorker {
public:
    MyLuaWorker(Nan::Callback *callback,WorkerCall workerCall,FinishCallBack finishCb) :
        Nan::AsyncWorker(callback),userParam(nullptr),_finishCb(finishCb),_workerCall(workerCall)
    {
        _userData.buff[0] = 0;
    }
    ~MyLuaWorker(){}
    
    void Execute ();
    struct UserDatas{
        bool hasErr = false;
        char buff[3024];
        int customVal= 0;
        
    };
    // Executed when the async work is complete
    // this function will be run inside the main event loop
    // so it is safe to use V8 again
    void HandleOKCallback ();
    
    void setQueueNotify(WorkerCall qn){
        _queueNotify = qn;
    }
    
    void setUserData(bool hasErr,const char* buff){
        _userData.hasErr = hasErr;
        if(buff){
            strcpy(_userData.buff, buff);
        }
    }
    UserDatas& getUserData(){
        return _userData;
    }
    
    void* userParam;
private:
    FinishCallBack _finishCb;
    WorkerCall _workerCall;
    WorkerCall _queueNotify;
    UserDatas _userData;
};
#endif /* MyLuaWorker_hpp */
