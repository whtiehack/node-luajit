'use strict';
console.time('luabegin');
var MyLua = require('../');
console.timeEnd('luabegin');
console.log('test');

var co = require('co');
testAsyncAndSingle();
co(function*() {
    var lua = new MyLua();
    console.time('dostr');
    var strret = yield (done)=> {
        lua.doString(`
            -- cjson = require("cjson"); 
            return {1,2,3}
        `, done);
    };
    console.log('dostr test :',strret);
    console.timeEnd('dostr');
    console.time('dostr2');
    strret = yield (done)=> {
        lua.doString(`
            -- cjson = require("cjson"); 
            return {1,2,3}
        `, done);
    };
    console.log('dostr test :',strret);
    console.timeEnd('dostr2');
    console.time('dofile');
    var dofileret = yield (done)=>{
        lua.doFile(__dirname+'/luatest.lua',done);
    };
    console.log('do file test retret:',dofileret);
    console.timeEnd('dofile');
    console.time('status');
    var status = yield (done)=>{
        lua.status(done);
    };
    console.log('lua status:',status,MyLua.STATUS);
    console.timeEnd('status');


    var fs = require('fs');
    console.time('fs1');
    var file = yield (done)=>{
        fs.readFile(__dirname+'/luatest.lua',done);
    };
    console.log('file:',file.toString().split('\n')[0]);
    console.timeEnd('fs1');


    yield (done)=>{
        lua.callGlobalFunction('testArgAndRetGlobalCall',11,22,[666,888,{'key1':'arrval1','key2':'arrval2'}],function(err,ret,ret2,table){
            console.log('callGlobalFunction!!:',err,ret,ret2,table);
            done();
        })
    };


}).catch((err)=>{
    console.log('!! test err:',err);
});




function testAsyncAndSingle(){

    var lua1 = new MyLua();
    var lua2 = new MyLua();

    lua1.doString('print("hello world") return "rettest"',function(err,ret){
        console.log('lua1 dostring ret:',err,ret)
    });
    lua2.doString('print("hello world") return "rettest"',function(err,ret){
        console.log('lua2 dostring ret:',err,ret)
    });


    lua1.doFile(__dirname+'/luatest.lua',function(err,ret){
        console.log('lua1 doFile ret:',err,ret)
    });



    lua2.doFile(__dirname+'/luatest.lua',function(err,ret){
        console.log('lua2 doFile ret:',err,ret)
    });

}

