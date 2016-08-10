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
var singleIdx = 0;
var MyLua = function(formatprint,loadcjson){
    if(typeof(formatprint)== 'undefined'){
        formatprint = true;
    }
    if(typeof(loadcjson)=='undefined'){
        loadcjson = true;
    }
    singleIdx++;
    var self = this;
    self.lua = new MyCLua();
    //init path
    var paths = ';'+__dirname+'/?.so;'+__dirname+'/build/Release/?.so';
    var luapaths = ';'+__dirname+'/?.lua;'+__dirname+'/test/?.lua;'+process.cwd()+'/?.lua';
    var luastr  = 'package.cpath = package.cpath .. "'+paths+'";package.path = package.path .. "'+luapaths+'";LUASINGLEIDX = '+singleIdx+';';;
    if(formatprint){
        luastr += 'require("initlua.formatPrint");';
    }
    if(loadcjson){
        luastr += 'cjson = require("cjson")';
    }
    self.lua.doString(luastr,function(err,ret){
     //   console.log('  package path:',err,ret);
        if(err){
            console.log('!!add find pash err:',err);
        }
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

/**
 * cb(null,status)
 * @param cb
 */
prop.status = function(cb){
    this.lua.status(cb);
};

prop.addPachagePath = function(path,isC){
    var luavar = 'package.path';
    if(isC){
        luavar = 'package.cpath';
    }
    var luastr  = luavar +' = ' + luavar+' .. ";' + path + '";';
    this.lua.doString(luastr);
};

/**
 *  call(funname[,args][,cb])  cb(err,ret)
 * @param funName
 */
prop.callGlobalFunction = function(funName){
    this.lua.callGlobalFunction.apply(this.lua,arguments);
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
