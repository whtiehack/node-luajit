'use strict';
var nodelua = null;

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
    this.lua = new MyCLua();
    //init path
    
};

var prop = MyLua.prototype;


prop.doFile = function(fn,cb){
    this.lua.doFile(fn,cb)
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
