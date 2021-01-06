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
#include <napi.h>
#include <functional>
class MyWorkerQueue;

class MyLuaWorker;
//typedef void(*FinishCallBack)(Nan::Callback *);
typedef std::function<void(Napi::Function&,MyLuaWorker* worker)> FinishCallBack;
//typedef void(*WorkerCall)(void);
typedef std::function<void(MyLuaWorker*)> WorkerCall;

class MyLuaWorker : public Napi::AsyncWorker {
public:
    MyLuaWorker(Napi::Function&callback,WorkerCall workerCall,FinishCallBack finishCb) :
    Napi::AsyncWorker(callback),userParam(nullptr),callback(callback)
    {
        this->_workerCall = workerCall;
        _finishCb = finishCb;
        _userData.hasErr = false;
        _userData.customVal = 0;
        _userData.buff[0] = 0;
    }
    ~MyLuaWorker(){
    //    printf("~MyLuaWorker\n");
    }
    
    void Execute ();
    struct UserDatas{
        bool hasErr;
        char buff[3024];
        int customVal;
        
    };
    // Executed when the async work is complete
    // this function will be run inside the main event loop
    // so it is safe to use V8 again
    void OnOK();
    
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
    Napi::Function& callback;
    FinishCallBack _finishCb;
    WorkerCall _workerCall;
    WorkerCall _queueNotify;
    UserDatas _userData;
};
#endif /* MyLuaWorker_hpp */
