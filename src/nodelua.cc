#include <node.h>
#include <v8.h>
#include <nan.h>

#include "luastate.h"

extern "C"{
#include <lua.h>
#include <luajit.h>
}

using namespace v8;

void init_info_constants(v8::Local<v8::Object> target){
  Local<Object> constants = Nan::New<v8::Object>();
    constants->Set(Nan::New("VERSION").ToLocalChecked(),Nan::New(LUA_VERSION).ToLocalChecked());
    constants->Set(Nan::New("VERSION_JIT").ToLocalChecked(),Nan::New(LUAJIT_VERSION).ToLocalChecked());
    constants->Set(Nan::New("VERSION_NUM").ToLocalChecked(), Nan::New(LUA_VERSION_NUM));
    constants->Set(Nan::New("COPYRIGHT").ToLocalChecked(), Nan::New(LUA_COPYRIGHT).ToLocalChecked());
    constants->Set(Nan::New("COPYRIGHT_JIT").ToLocalChecked(), Nan::New(LUAJIT_COPYRIGHT).ToLocalChecked());
    constants->Set(Nan::New("AUTHORS").ToLocalChecked(), Nan::New(LUA_AUTHORS).ToLocalChecked());
    target->Set(Nan::New("INFO").ToLocalChecked(), constants);
}


void init_status_constants(Handle<Object> target){
    Local<Object> constants = Nan::New<v8::Object>();
    constants->Set(Nan::New("YIELD").ToLocalChecked(), Nan::New(LUA_YIELD));
    constants->Set(Nan::New("ERRRUN").ToLocalChecked(), Nan::New(LUA_ERRRUN));
    constants->Set(Nan::New("ERRSYNTAX").ToLocalChecked(), Nan::New(LUA_ERRSYNTAX));
    constants->Set(Nan::New("ERRMEM").ToLocalChecked(), Nan::New(LUA_ERRMEM));
    constants->Set(Nan::New("ERRERR").ToLocalChecked(), Nan::New(LUA_ERRERR));
    target->Set(Nan::New("STATUS").ToLocalChecked(), constants);
}


void init_gc_constants(Handle<Object> target){
    Local<Object> constants = Nan::New<v8::Object>();
    constants->Set(Nan::New("STOP").ToLocalChecked(), Nan::New(LUA_GCSTOP));
    constants->Set(Nan::New("RESTART").ToLocalChecked(), Nan::New(LUA_GCRESTART));
    constants->Set(Nan::New("COLLECT").ToLocalChecked(), Nan::New(LUA_GCCOLLECT));
    constants->Set(Nan::New("COUNT").ToLocalChecked(), Nan::New(LUA_GCCOUNT));
    constants->Set(Nan::New("COUNTB").ToLocalChecked(), Nan::New(LUA_GCCOUNTB));
    constants->Set(Nan::New("STEP").ToLocalChecked(), Nan::New(LUA_GCSTEP));
    constants->Set(Nan::New("SETPAUSE").ToLocalChecked(), Nan::New(LUA_GCSETPAUSE));
    constants->Set(Nan::New("SETSTEPMUL").ToLocalChecked(), Nan::New(LUA_GCSETSTEPMUL));
    target->Set(Nan::New("GC").ToLocalChecked(), constants);
}


void init(v8::Local<v8::Object> exports, v8::Local<v8::Object> module) {
//  LuaState::Init(exports);
  init_gc_constants(exports);
  init_status_constants(exports);
  init_info_constants(exports);
}
NODE_MODULE(nodelua, init)
