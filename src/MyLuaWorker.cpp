//
//  MyLuaWorker.cpp
//  binding
//
//  Created by mac on 16/8/9.
//
//

#include "MyLuaWorker.hpp"



void MyLuaWorker::Execute () {
  //  printf("WorkerCall begin:%ld\n",time(0));
    _workerCall(this);
  //  printf("WorkerCall end  :%ld\n",time(0));
}



void MyLuaWorker::OnOK () {
    // printf("OnOK  handle ok callback:%ld\n",time(0));
    _finishCb(callback,this);
//    printf("WorkerCall  handle ok callback end:%ld\n",time(0));
    _queueNotify(this);
    // clear no need will delete by node
    // delete this;
//    Nan::HandleScope scope;
//    
//    Local<Value> argv[] = {
//        Null()
//        , New<Number>(estimate)
//    };
//    
//    callback->Call(2, argv);
}
