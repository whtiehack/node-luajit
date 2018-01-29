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
var MyLua = function(formatprint){
    if(typeof(formatprint)== 'undefined'){
        formatprint = true;
    }
    singleIdx++;
    var self = this;
    self.lua = new MyCLua(singleIdx);
    //init path
    var paths = ';'+__dirname+'/?.so;'+__dirname+'/build/Release/?.so;'+__dirname+'/build/Release/?.dll';
    var luapaths = ';'+__dirname+'/?.lua;'+__dirname+'/test/?.lua;'+process.cwd()+'/?.lua';
    var luastr  = 'package.cpath = package.cpath .. "'+paths+'";package.path = package.path .. "'+luapaths+'";LUASINGLEIDX = '+singleIdx+';';
    if(formatprint){
        luastr += 'require("initlua.formatPrint");';
    }
    if(process.platform=='win32'){
        luastr = luastr.replace(new RegExp('\\\\','g'),'/');
    }
    self.lua.doString(luastr,function(err,ret){
     //   console.log('  package path:',err,ret);
        if(err){
            console.log('!!add find pash err:',err);
            console.log('lua:',luastr);
        }
    });
 //   self.lua.doString("print(package.path)")
};

var prop = MyLua.prototype;


prop.doFile = function(fn,cb){
    return this.lua.doFile(fn,cb);
};


prop.doString = function(str,cb){
    return this.lua.doString(str,cb);
};

/**
 * cb(null,status)
 * @param cb
 */
prop.status = function(cb){
    return this.lua.status(cb);
};

prop.addPachagePath = function(path,isC){
    var luavar = 'package.path';
    if(isC){
        luavar = 'package.cpath';
    }
    var luastr  = luavar +' = ' + luavar+' .. ";' + path + '";';
    return this.lua.doString(luastr);
};

/**
 *  call(funname[,args][,cb])  cb(err,ret)
 * @param funName
 * @returns {number}
 */
prop.callGlobalFunction = function(funName){
    return this.lua.callGlobalFunction.apply(this.lua,arguments);
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
