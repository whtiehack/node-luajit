'use strict';
var nodelua = null;
var path = require('path');
try{
    nodelua = require('./build/Release/node-luajit');
}catch(e){
    console.log('```  release load err:',e);
    nodelua = require('./build/Debug/node-luajit');
}

var MyCLua = nodelua.MyLuaState;

if(!nodelua){
    return;
}
var MyLua = function(){
    var self = this;
    self.lua = new MyCLua();
    //init path
    var paths = ';'+__dirname+'/?.so;'+__dirname+'/build/Release/?.so';
    self.lua.doString('package.cpath = package.cpath .. "'+paths+'";',function(err,ret){
     //   console.log('  package path:',err,ret);
    });
 //   self.lua.doString("print(package.path)")
};

var prop = MyLua.prototype;


prop.doFile = function(fn,cb){
    this.lua.doFile(fn,cb);
};


prop.doString = function(str,cb){
    this.lua.doString(str,cb);
};

MyLua.GC = nodelua.GC;
MyLua.STATUS = nodelua.STATUS;
MyLua.INFO = nodelua.INFO;
// { MyLuaState: [Function: MyLuaState],
//     GC:
//     { STOP: 0,
//         RESTART: 1,
//         COLLECT: 2,
//         COUNT: 3,
//         COUNTB: 4,
//         STEP: 5,
//         SETPAUSE: 6,
//         SETSTEPMUL: 7 },
//     STATUS: { YIELD: 1, ERRRUN: 2, ERRSYNTAX: 3, ERRMEM: 4, ERRERR: 5 },
//     INFO:
//     { VERSION: 'Lua 5.1',
//         VERSION_NUM: 501,
//         COPYRIGHT: 'Copyright (C) 1994-2012 Lua.org, PUC-Rio',
//         AUTHORS: 'R. Ierusalimschy, L. H. de Figueiredo & W. Celes' } }
module.exports = MyLua;
