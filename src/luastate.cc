#define BUILDING_NODELUA
#include "luastate.h"
#include <v8.h>
#include <nan.h>
using namespace v8;
//
//uv_async_t async;
//std::map<char*, Nan::Persistent<Function> > functions;
//
//struct async_baton{
//  bool has_cb;
//  Persistent<Function> callback;
//  char* data;
//  bool error;
//  char msg[1000];
//  LuaState* state;
//};
//
//struct simple_baton{
//  bool has_cb;
//  Nan::Persistent<v8::Function> callback;
//  int data;
//  int result;
//  LuaState* state;
//};
//
//
//void do_file(uv_work_t *req){
//  async_baton* baton = static_cast<async_baton*>(req->data);
//
//  if(luaL_dofile(baton->state->lua_, baton->data)){
//    baton->error = true;
//    sprintf(baton->msg, "Exception In File %s Has Failed:\n%s\n", baton->data, lua_tostring(baton->state->lua_, -1));
//  }
//}
//
//
//void do_gc(uv_work_t *req){
//  simple_baton* baton = static_cast<simple_baton*>(req->data);
//
//  baton->result = lua_gc(baton->state->lua_, baton->data, 0);
//}
//
//
//void do_status(uv_work_t *req){
//  simple_baton* baton = static_cast<simple_baton*>(req->data);
//
//  baton->result = lua_status(baton->state->lua_);
//}
//
//
//void simple_after(uv_work_t *req, int status){
//  Nan::HandleScope scope;
//
//  simple_baton* baton = static_cast<simple_baton*>(req->data);
//
//  const int argc = 1;
//  Local<Value> argv[] = { Nan::New(baton->result) };
//
//  TryCatch try_catch;
//
//  if(baton->has_cb){
//  //    baton->callback.Call(Nan::GetCurrentContext->Global(), argc, argv);
//    //  auto cb = baton->callback.As<v8::Function>();
//   //   Nan::MakeCallback(Nan::GetCurrentContext()->Global(), cb, argc, argv);
//      Nan::MakeCallback(Nan::GetCurrentContext()->Global(), Nan::New(baton->callback), argc, argv);
//  }
//
////  baton->callback.Dispose();
//  delete baton;
//  delete req;
//
//  if(try_catch.HasCaught()){
//    node::FatalException(try_catch);
//  }
//}
//
//void do_string(uv_work_t *req){
//  async_baton* baton = static_cast<async_baton*>(req->data);
//
//  if(luaL_dostring(baton->state->lua_, baton->data)){
//    baton->error = true;
//    sprintf(baton->msg, "Exception Of Lua Code Has Failed:\n%s\n", lua_tostring(baton->state->lua_, -1));
//  }
//}
//
//
//void async_after(uv_work_t *req, int status){
//  Nan::HandleScope scope;
//
//  async_baton* baton = (async_baton *)req->data;
//
//  Local<Value> argv[2];
//  const int argc = 2;
//
//  if(baton->error){
//      argv[0] = Nan::New(baton->msg).ToLocalChecked();
//      argv[1] = Nan::Undefined();
//  } else{
//    argv[0] = Nan::Undefined();
//    if(lua_gettop(baton->state->lua_)){
//      argv[1] = lua_to_value(baton->state->lua_, -1);
//    } else{
//      argv[1] = Nan::Undefined();
//    }
//  }
//
//  TryCatch try_catch;
//
//  if(baton->has_cb){
//    //baton->callback->Call(Context::GetCurrent()->Global(), argc, argv);
//      Nan::MakeCallback(Nan::GetCurrentContext()->Global(), Nan::New(baton->callback), argc, argv);
//  }
//
// // baton->callback.Dispose();
//  delete baton;
//  delete req;
//
//  if(try_catch.HasCaught()){
//    node::FatalException(try_catch);
//  }
//}
//
//
//LuaState::LuaState(){};
//LuaState::~LuaState(){};
//
//
//void LuaState::Init(Handle<Object> target){
//  Local<FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
//  tpl->SetClassName(Nan::New("LuaState").ToLocalChecked());
//  tpl->InstanceTemplate()->SetInternalFieldCount(2);
//
//    tpl->PrototypeTemplate()->Set(Nan::New("doFileSync").ToLocalChecked(),
//				Nan::New<v8::FunctionTemplate>(DoFileSync)->GetFunction());
//  tpl->PrototypeTemplate()->Set(Nan::New("doFile").ToLocalChecked(),
//				Nan::New<v8::FunctionTemplate>(DoFile)->GetFunction());
//
//  tpl->PrototypeTemplate()->Set(Nan::New("doStringSync").ToLocalChecked(),
//				Nan::New<v8::FunctionTemplate>(DoStringSync)->GetFunction());
//  tpl->PrototypeTemplate()->Set(Nan::New("doString").ToLocalChecked(),
//				Nan::New<v8::FunctionTemplate>(DoString)->GetFunction());
//
//  tpl->PrototypeTemplate()->Set(Nan::New("setGlobal").ToLocalChecked(),
//				Nan::New<v8::FunctionTemplate>(SetGlobal)->GetFunction());
//  tpl->PrototypeTemplate()->Set(Nan::New("getGlobal").ToLocalChecked(),
//				Nan::New<v8::FunctionTemplate>(GetGlobal)->GetFunction());
//
//    
//    tpl->PrototypeTemplate()->Set(Nan::New("status").ToLocalChecked(),
//                                  Nan::New<v8::FunctionTemplate>(Status)->GetFunction());
//    tpl->PrototypeTemplate()->Set(Nan::New("statusSync").ToLocalChecked(),
//                                  Nan::New<v8::FunctionTemplate>(StatusSync)->GetFunction());
//    
//    tpl->PrototypeTemplate()->Set(Nan::New("collectGarbage").ToLocalChecked(),
//                                  Nan::New<v8::FunctionTemplate>(CollectGarbage)->GetFunction());
//    tpl->PrototypeTemplate()->Set(Nan::New("collectGarbageSync").ToLocalChecked(),
//                                  Nan::New<v8::FunctionTemplate>(CollectGarbageSync)->GetFunction());
//    
//    tpl->PrototypeTemplate()->Set(Nan::New("close").ToLocalChecked(),
//                                  Nan::New<v8::FunctionTemplate>(Close)->GetFunction());
//    tpl->PrototypeTemplate()->Set(Nan::New("getName").ToLocalChecked(),
//                                  Nan::New<v8::FunctionTemplate>(GetName)->GetFunction());
//    
//    tpl->PrototypeTemplate()->Set(Nan::New("registerFunction").ToLocalChecked(),
//                                  Nan::New<v8::FunctionTemplate>(RegisterFunction)->GetFunction());
//    
//    tpl->PrototypeTemplate()->Set(Nan::New("push").ToLocalChecked(),
//                                  Nan::New<v8::FunctionTemplate>(Push)->GetFunction());
//    tpl->PrototypeTemplate()->Set(Nan::New("pop").ToLocalChecked(),
//                                  Nan::New<v8::FunctionTemplate>(Pop)->GetFunction());
//    tpl->PrototypeTemplate()->Set(Nan::New("getTop").ToLocalChecked(),
//                                  Nan::New<v8::FunctionTemplate>(GetTop)->GetFunction());
//    tpl->PrototypeTemplate()->Set(Nan::New("setTop").ToLocalChecked(),
//                                  Nan::New<v8::FunctionTemplate>(SetTop)->GetFunction());
//    tpl->PrototypeTemplate()->Set(Nan::New("replace").ToLocalChecked(),
//                                  Nan::New<v8::FunctionTemplate>(Replace)->GetFunction());
//
//    Nan::Persistent<v8::Function> constructor;
//    constructor.Reset(tpl->GetFunction());
////  Persistent<Function> constructor = Persistent<Function>::New(tpl->GetFunction());
////  target->Set(String::NewSymbol("LuaState"), constructor);
//}
//
//
//int LuaState::CallFunction(lua_State* L){
//  int n = lua_gettop(L);
//
//  char * func_name = (char *)lua_tostring(L, lua_upvalueindex(1));
//
//  const unsigned argc = n;
//  Local<Value>* argv = new Local<Value>[argc];
//  int i;
//  for(i = 1; i <= n; ++i){
//    argv[i - 1] = lua_to_value(L, i);
//  }
//
//    Handle<Value> ret_val = Nan::Undefined();
//
//    std::map<char *,Nan::Persistent<Function> >::iterator iter;
//  for(iter = functions.begin(); iter != functions.end(); iter++){
//    if(strcmp(iter->first, func_name) == 0){
//        Nan::Persistent<Function> func = iter->second;
//     // ret_val = func->Call(Context::GetCurrent()->Global(), argc, argv);
//        ret_val = Nan::MakeCallback(Nan::GetCurrentContext()->Global(), Nan::New(func), argc, argv);
//      break;
//    }
//  }
//
//  push_value_to_lua(L, ret_val);
//  return 1;
//}
//
//
//Handle<Value> LuaState::New(const Nan::FunctionCallbackInfo<v8::Value>& args){
//    Nan::HandleScope scope;
//
//  if(!args.IsConstructCall()) {
//      return v8::Isolate::GetCurrent()->ThrowException(Nan::New("LuaState Requires The 'new' Operator To Create An Instance").ToLocalChecked());
//   // return ThrowException(Exception::TypeError(String::New("LuaState Requires The 'new' Operator To Create An Instance")));
//  }
//
//  if(args.Length()<=0){
//      return v8::Isolate::GetCurrent()->ThrowException(Nan::New("LuaState Requires 1 Argument").ToLocalChecked());
//    //  return ThrowException(Exception::TypeError(Nan::New("LuaState Requires 1 Argument").ToLocalChecked()));
//  }
//
//  if(!args[0]->IsString()){
//      return v8::Isolate::GetCurrent()->ThrowException(Nan::New("LuaState First Argument Must Be A String").ToLocalChecked());
//    //return ThrowException(Exception::TypeError(String::New("LuaState First Argument Must Be A String")));
//  }
//
//  LuaState* obj = new LuaState();
//  obj->name_ = get_str(args[0]);
//  obj->lua_ = lua_open();
//  luaL_openlibs(obj->lua_);
//  obj->Wrap(args.This());
//
//  return args.This();
//}
//
//
//Handle<Value> LuaState::GetName(const Nan::FunctionCallbackInfo<v8::Value>& args){
//    Nan::HandleScope scope;
//
//  LuaState* obj = ObjectWrap::Unwrap<LuaState>(args.This());
////  return scope.Close(String::New(obj->name_));
//    return Nan::New(obj->name_).ToLocalChecked();
//}
//
//
//Handle<Value> LuaState::DoFileSync(const Nan::FunctionCallbackInfo<v8::Value>& args){
//    Nan::HandleScope scope;
//    
//    if(args.Length() < 1){
//        return v8::Isolate::GetCurrent()->ThrowException(Nan::New("LuaState.doFileSync Takes Only 1 Argument").ToLocalChecked());
//        //        return scope.Close(Undefined());
//    }
//    
//    if(!args[0]->IsString()){
//        return v8::Isolate::GetCurrent()->ThrowException(Nan::New("LuaState.doFileSync Argument 1 Must Be A String").ToLocalChecked());
//        //        return scope.Close(Undefined());
//    }
//    
//    char* file_name = get_str(args[0]);
//    
//    LuaState* obj = ObjectWrap::Unwrap<LuaState>(args.This());
//    if(luaL_dofile(obj->lua_, file_name)){
//        char buf[1000];
//        sprintf(buf, "Exception Of File %s Has Failed:\n%s\n", file_name, lua_tostring(obj->lua_, -1));
//     //   ThrowException(Exception::Error(String::New(buf)));
//        return v8::Isolate::GetCurrent()->ThrowException(Nan::New(buf).ToLocalChecked());
//    }
//    
//    if(lua_gettop(obj->lua_)){
//        return lua_to_value(obj->lua_, -1);
//    } else{
//        return Nan::Undefined();
//    }
//}
//
//
//Handle<Value> LuaState::DoFile(const Nan::FunctionCallbackInfo<v8::Value>& args){
//    Nan::HandleScope scope;
//    
//    if(args.Length() < 1){
//        return v8::Isolate::GetCurrent()->ThrowException(Nan::New("LuaState.doFile Requires At Least 1 Argument").ToLocalChecked());
//        //        return scope.Close(Undefined());
//    }
//    
//    if(!args[0]->IsString()){
//        return v8::Isolate::GetCurrent()->ThrowException(Nan::New("LuaState.doFile First Argument Must Be A String").ToLocalChecked());
//        //        return scope.Close(Undefined());
//    }
//    
//    if(args.Length() > 1 && !args[1]->IsFunction()){
//        return v8::Isolate::GetCurrent()->ThrowException(Nan::New("LuaState.doFile Second Argument Must Be A Function").ToLocalChecked());
//        //        return scope.Close(Undefined());
//    }
//    
//    LuaState* obj = ObjectWrap::Unwrap<LuaState>(args.This());
//    async_baton* baton = new async_baton();
//    baton->data = get_str(args[0]);
//    baton->state = obj;
//    obj->Ref();
//    
//    if(args.Length() > 1){
//        baton->has_cb = true;
//    //    baton->callback = Persistent<Function>::New(Local<Function>::Cast(args[1]));
//        baton->callback = Nan::Persistent<Function>(Local<Function>::Cast(args[1]));
//     //   baton->callback.Reset(args[1].As<v8::Function>()->GetBoundFunction());// = Nan::New<>(args[1]);
//    }
//    
//    uv_work_t *req = new uv_work_t;
//    req->data = baton;
//    uv_queue_work(uv_default_loop(), req, do_file, async_after);
//    
//    return Nan::Undefined();
//}
//
//
//Handle<Value> LuaState::DoStringSync(const Nan::FunctionCallbackInfo<v8::Value>& args) {
//    Nan::HandleScope scope;
//    
//    if(args.Length() < 1){
//        return v8::Isolate::GetCurrent()->ThrowException(Nan::New("LuaState.doStringSync Requires 1 Argument").ToLocalChecked());
//        //        return scope.Close(Undefined());
//    }
//    
//    char *lua_code = get_str(args[0]);
//    
//    LuaState* obj = ObjectWrap::Unwrap<LuaState>(args.This());
//    if(luaL_dostring(obj->lua_, lua_code)){
//        char buf[1000];
//        sprintf(buf, "Execution Of Lua Code Has Failed:\n%s\n", lua_tostring(obj->lua_, -1));
//     //   ThrowException(Exception::Error(String::New(buf)));
//      //  return scope.Close(Undefined());
//        return v8::Isolate::GetCurrent()->ThrowException(Nan::New(buf).ToLocalChecked());
//    }
//    
//    if(lua_gettop(obj->lua_)){
//        return lua_to_value(obj->lua_, -1);
//    } else{
//        return Nan::Undefined();
//    }
//}
//
//
//Handle<Value> LuaState::DoString(const Nan::FunctionCallbackInfo<v8::Value>& args){
//    Nan::HandleScope scope;
//    
//    if(args.Length() < 1){
//        return v8::Isolate::GetCurrent()->ThrowException(Nan::New("LuaState.doString Requires At Least 1 Argument").ToLocalChecked());
//        //        return scope.Close(Undefined());
//    }
//    
//    if(!args[0]->IsString()){
//        return v8::Isolate::GetCurrent()->ThrowException(Nan::New("LuaState.doString: First Argument Must Be A String").ToLocalChecked());
//        //        return scope.Close(Undefined());
//    }
//    
//    LuaState* obj = ObjectWrap::Unwrap<LuaState>(args.This());
//    async_baton* baton = new async_baton();
//    baton->data = get_str(args[0]);
//    baton->state = obj;
//    obj->Ref();
//    
//    if(args.Length() > 1 && !args[1]->IsFunction()){
//        return v8::Isolate::GetCurrent()->ThrowException(Nan::New("LuaState.doString Second Argument Must Be A Function").ToLocalChecked());
//        //        return scope.Close(Undefined());
//    }
//    
//    if(args.Length() > 1){
//        baton->has_cb = true;
//      //  baton->callback = Persistent<Function>::New(Local<Function>::Cast(args[1]));
//        baton->callback = Nan::Persistent<Function>(Local<Function>::Cast(args[1]));
//    }
//    
//    uv_work_t *req = new uv_work_t;
//    req->data = baton;
//    uv_queue_work(uv_default_loop(), req, do_string, async_after);
//    
//    return Nan::Undefined();
//}
//
//
//Handle<Value> LuaState::SetGlobal(const Nan::FunctionCallbackInfo<v8::Value>& args) {
//    Nan::HandleScope scope;
//    
//    if(args.Length() < 2){
//        return v8::Isolate::GetCurrent()->ThrowException(Nan::New("LuaState.setGlobal Requires 2 Arguments").ToLocalChecked());
//        //        return scope.Close(Undefined());
//    }
//    
//    if(!args[0]->IsString()){
//        return v8::Isolate::GetCurrent()->ThrowException(Nan::New("LuaState.setGlobal Argument 1 Must Be A String").ToLocalChecked());
//        //        return scope.Close(Undefined());
//    }
//    
//    char *global_name = get_str(args[0]);
//    
//    LuaState* obj = ObjectWrap::Unwrap<LuaState>(args.This());
//    
//    push_value_to_lua(obj->lua_, args[1]);
//    lua_setglobal(obj->lua_, global_name);
//    
//    return Nan::Undefined();
//}
//
//
//Handle<Value> LuaState::GetGlobal(const Nan::FunctionCallbackInfo<v8::Value>& args) {
//    Nan::HandleScope scope;
//    
//    if(args.Length() < 1){
//        return v8::Isolate::GetCurrent()->ThrowException(Nan::New("LuaState.getGlobal Requires 1 Argument").ToLocalChecked());
//        //        return scope.Close(Undefined());
//    }
//    
//    if(!args[0]->IsString()){
//        return v8::Isolate::GetCurrent()->ThrowException(Nan::New("LuaState.getGlobal Argument 1 Must Be A String").ToLocalChecked());
//        //        return scope.Close(Undefined());
//    }
//    
//    char *global_name = get_str(args[0]);
//    
//    LuaState* obj = ObjectWrap::Unwrap<LuaState>(args.This());
//    lua_getglobal(obj->lua_, global_name);
//    
//    Local<Value> val = lua_to_value(obj->lua_, -1);
//    
//    return val;
//}
//
//Handle<Value> LuaState::Close(const Nan::FunctionCallbackInfo<v8::Value>& args){
//    Nan::HandleScope scope;
//    LuaState* obj = ObjectWrap::Unwrap<LuaState>(args.This());
//    lua_close(obj->lua_);
//    return Nan::Undefined();
//}
//
//
//Handle<Value> LuaState::Status(const Nan::FunctionCallbackInfo<v8::Value>& args){
//    Nan::HandleScope scope;
//    LuaState* obj = ObjectWrap::Unwrap<LuaState>(args.This());
//    simple_baton* baton = new simple_baton();
//    baton->state = obj;
//    obj->Ref();
//    
//    if(args.Length() > 0 && !args[0]->IsFunction()){
//        return v8::Isolate::GetCurrent()->ThrowException(Nan::New("LuaState.status First Argument Must Be A Function").ToLocalChecked());
//        //        return scope.Close(Undefined());
//    }
//    
//    if(args.Length() > 0){
//        baton->has_cb = true;
//  //      baton->callback = Persistent<Function>::New(Local<Function>::Cast(args[0]));
//        baton->callback = Nan::Persistent<Function>(Local<Function>::Cast(args[0]));
//    }
//    
//    uv_work_t *req = new uv_work_t;
//    req->data = baton;
//    uv_queue_work(uv_default_loop(), req, do_status, simple_after);
//    
//    return Nan::Undefined();
//}
//
//
//Handle<Value> LuaState::StatusSync(const Nan::FunctionCallbackInfo<v8::Value>& args){
//    Nan::HandleScope scope;
//    LuaState* obj = ObjectWrap::Unwrap<LuaState>(args.This());
//    int status = lua_status(obj->lua_);
//    
//    return Nan::New(status);
//}
//
//
//Handle<Value> LuaState::CollectGarbage(const Nan::FunctionCallbackInfo<v8::Value>& args){
//    Nan::HandleScope scope;
//    
//    if(args.Length() < 1){
//        return v8::Isolate::GetCurrent()->ThrowException(Nan::New("LuaState.collectGarbage Requires 1 Argument").ToLocalChecked());
//        //        return scope.Close(Undefined());
//    }
//    
//    if(!args[0]->IsNumber()){
//        return v8::Isolate::GetCurrent()->ThrowException(Nan::New("LuaSatte.collectGarbage Argument 1 Must Be A Number, try nodelua.GC.[TYPE]").ToLocalChecked());
//        //        return scope.Close(Undefined());
//    }
//    
//    LuaState* obj = ObjectWrap::Unwrap<LuaState>(args.This());
//    int type = (int)args[0]->ToNumber()->Value();
//    
//    simple_baton* baton = new simple_baton();
//    baton->data = type;
//    baton->state = obj;
//    obj->Ref();
//    
//    if(args.Length() > 1 && !args[1]->IsFunction()){
//        return v8::Isolate::GetCurrent()->ThrowException(Nan::New("LuaState.collectGarbage Second Argument Must Be A Function").ToLocalChecked());
//        //        return scope.Close(Undefined());
//    }
//    
//    if(args.Length() > 1){
//        baton->has_cb = true;
//     //   baton->callback = Persistent<Function>::New(Local<Function>::Cast(args[1]));
//        baton->callback = Nan::Persistent<Function>(Local<Function>::Cast(args[1]));
//    }
//    
//    uv_work_t *req = new uv_work_t;
//    req->data = baton;
//    uv_queue_work(uv_default_loop(), req, do_gc, simple_after);
//    
//    return Nan::Undefined();
//}
//
//
//Handle<Value> LuaState::CollectGarbageSync(const Nan::FunctionCallbackInfo<v8::Value>& args){
//    Nan::HandleScope scope;
//    
//    if(args.Length() < 1){
//        return v8::Isolate::GetCurrent()->ThrowException(Nan::New("LuaState.collectGarbageSync Requires 1 Argument").ToLocalChecked());
//        //        return scope.Close(Undefined());
//    }
//    
//    if(!args[0]->IsNumber()){
//        return v8::Isolate::GetCurrent()->ThrowException(Nan::New("LuaSatte.collectGarbageSync Argument 1 Must Be A Number, try nodelua.GC.[TYPE]").ToLocalChecked());
//        //        return scope.Close(Undefined());
//    }
//    
//    LuaState* obj = ObjectWrap::Unwrap<LuaState>(args.This());
//    int type = (int)args[0]->ToNumber()->Value();
//    int gc = lua_gc(obj->lua_, type, 0);
//    
//    return Nan::New(gc);
//}
//
//
//Handle<Value> LuaState::RegisterFunction(const Nan::FunctionCallbackInfo<v8::Value>& args){
//    Nan::HandleScope scope;
//    
//    if(args.Length() < 1){
//        return v8::Isolate::GetCurrent()->ThrowException(Nan::New("nodelua.registerFunction Must Have 2 Arguments").ToLocalChecked());
//        //        return scope.Close(Undefined());
//    }
//    
//    if(!args[0]->IsString()){
//        return v8::Isolate::GetCurrent()->ThrowException(Nan::New("nodelua.registerFunction Argument 1 Must Be A String").ToLocalChecked());
//        //        return scope.Close(Undefined());
//    }
//    
//    if(!args[1]->IsFunction()){
//        return v8::Isolate::GetCurrent()->ThrowException(Nan::New("nodelua.registerFunction Argument 2 Must Be A Function").ToLocalChecked());
//        //        return scope.Close(Undefined());
//    }
//    
//    LuaState* obj = ObjectWrap::Unwrap<LuaState>(args.This());
//    
//    Nan::Persistent<Function> func = Nan::Persistent<Function>(Local<Function>::Cast(args[1]));
//    char* func_name = get_str(args[0]);
//    Local<String> func_key = String::Concat(Nan::New(func_name).ToLocalChecked(), Nan::New(":").ToLocalChecked());
//    func_key = String::Concat(func_key, Nan::New(obj->name_).ToLocalChecked());
//    functions[get_str(func_key)] = func;
//    
//    lua_pushstring(obj->lua_, get_str(func_key));
//    lua_pushcclosure(obj->lua_, CallFunction, 1);
//    lua_setglobal(obj->lua_, func_name);
//    
//    return Nan::Undefined();
//}
//
//
//Handle<Value> LuaState::Push(const Nan::FunctionCallbackInfo<v8::Value>& args) {
//    Nan::HandleScope scope;
//    
//    if(args.Length() < 1){
//        return v8::Isolate::GetCurrent()->ThrowException(Nan::New("LuaState.push Requires 1 Argument").ToLocalChecked());
//        //        return scope.Close(Undefined());
//    }
//    
//    LuaState* obj = ObjectWrap::Unwrap<LuaState>(args.This());
//    
//    push_value_to_lua(obj->lua_, args[0]);
//    
//    return Nan::Undefined();
//}
//
//
//Handle<Value> LuaState::Pop(const Nan::FunctionCallbackInfo<v8::Value>& args) {
//    Nan::HandleScope scope;
//    
//    int pop_n = 1;
//    if(args.Length() > 0 && args[0]->IsNumber()){
//        pop_n = (int)args[0]->ToNumber()->Value();
//    }
//    
//    LuaState* obj = ObjectWrap::Unwrap<LuaState>(args.This());
//    lua_pop(obj->lua_, pop_n);
//    
//    return Nan::Undefined();
//}
//
//
//Handle<Value> LuaState::GetTop(const Nan::FunctionCallbackInfo<v8::Value>& args) {
//    Nan::HandleScope scope;
//    
//    LuaState* obj = ObjectWrap::Unwrap<LuaState>(args.This());
//    int n = lua_gettop(obj->lua_);
//    
//    return Nan::New(n);
//}
//
//
//Handle<Value> LuaState::SetTop(const Nan::FunctionCallbackInfo<v8::Value>& args) {
//    Nan::HandleScope scope;
//    
//    int set_n = 0;
//    if(args.Length() > 0 && args[0]->IsNumber()){
//        set_n = (int)args[0]->ToNumber()->Value();
//    }
//    
//    LuaState* obj = ObjectWrap::Unwrap<LuaState>(args.This());
//    lua_settop(obj->lua_, set_n);
//    
//    return Nan::Undefined();
//}
//
//
//Handle<Value> LuaState::Replace(const Nan::FunctionCallbackInfo<v8::Value>& args) {
//    Nan::HandleScope scope;
//    
//    if(args.Length() < 1){
//        return v8::Isolate::GetCurrent()->ThrowException(Nan::New("LuaState.replace Requires 1 Argument").ToLocalChecked());
//        //        return scope.Close(Undefined());
//    }
//    
//    if(!args[0]->IsNumber()){
//        return v8::Isolate::GetCurrent()->ThrowException(Nan::New("LuaState.replace Argument 1 Must Be A Number").ToLocalChecked());
//        //        return scope.Close(Undefined());
//    }
//    
//    int index = (int)args[0]->ToNumber()->Value();
//    
//    LuaState* obj = ObjectWrap::Unwrap<LuaState>(args.This());
//    lua_replace(obj->lua_, index);
//    
//    return Nan::Undefined();
//}
