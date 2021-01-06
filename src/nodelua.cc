#include <napi.h>

#include "luastate.h"
#ifndef WIN32
#include <unistd.h>
#else
//TODO
#endif
#include "MyLuaState.hpp"

extern "C"{
#include <lua.h>
}


void init_info_constants(Napi::Env env,Napi::Object exports){
    Napi::Object constants = Napi::Object::New(env);
    constants.Set("VERSION", LUA_VERSION);
    constants.Set("VERSION_NUM", LUA_VERSION_NUM);
    constants.Set("COPYRIGHT", LUA_COPYRIGHT);
    constants.Set("AUTHORS", LUA_AUTHORS);
    exports.Set("INFO", constants);
}


void init_status_constants(Napi::Env env,Napi::Object exports){
    Napi::Object constants = Napi::Object::New(env);
    constants.Set("YIELD", LUA_YIELD);
    constants.Set("ERRRUN", LUA_ERRRUN);
    constants.Set("ERRSYNTAX", LUA_ERRSYNTAX);
    constants.Set("ERRMEM", LUA_ERRMEM);
    constants.Set("ERRERR", LUA_ERRERR);
    exports.Set("STATUS", constants);
}


void init_gc_constants(Napi::Env env,Napi::Object exports){
    Napi::Object constants = Napi::Object::New(env);
    constants.Set("STOP", LUA_GCSTOP);
    constants.Set("RESTART", LUA_GCRESTART);
    constants.Set("COLLECT", LUA_GCCOLLECT);
    constants.Set("COUNT", LUA_GCCOUNT);
    constants.Set("COUNTB", LUA_GCCOUNTB);
    constants.Set("STEP", LUA_GCSTEP);
    constants.Set("SETPAUSE", LUA_GCSETPAUSE);
    constants.Set("SETSTEPMUL", LUA_GCSETSTEPMUL);
    exports.Set("GC", constants);
}

/*
void init(v8::Local<v8::Object> exports, v8::Local<v8::Object> module) {
//  LuaState::Init(exports);
    MyLuaState::Init(exports);
    init_gc_constants(exports);
    init_status_constants(exports);
    init_info_constants(exports);
    printf("node-lua loaded\n");
    fflush(stdout);
//    auto L = luaL_newstate();
//    if(L){
//        char buf[80];
//        getcwd(buf,sizeof(buf));
//        printf("havahave  have2222\n");
//        printf("cwd:%s\n",buf);
//        luaL_openlibs(L);
//        auto ret = luaL_dostring(L,"print('path:' .. package.path);");
//        if(ret){
//            printf("err:%s\n",lua_tostring(L,-1));
//        }
//        lua_close(L);
//    }else{
//        printf("not not not \n");
//    }
    
}
*/


Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  // return List::Init(env, exports);
    MyLuaState::Init(env,exports);
    init_gc_constants(env,exports);
    init_status_constants(env,exports);
    init_info_constants(env,exports);
    printf("node-lua loaded\n");
    fflush(stdout);
    return exports;
}

NODE_API_MODULE(nodelua, InitAll)
