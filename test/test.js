'use strict';
let co = require('co')
console.time('luabegin');
let MyLua = require('../');
console.timeEnd('luabegin');
console.log('test', MyLua.GC, MyLua.INFO, MyLua.STATUS);
testAsyncAndSingle();
co(function* () {
    let lua = new MyLua();
    console.log('test cjson')
    console.time('dostr');
    let strret = yield (done) => {
        lua.doString(`
            -- cjson = require("cjson");
            return {1,2,3}
        `, done);
    };
    console.log('dostr test :', strret);
    console.timeEnd('dostr');
    console.time('dostr2');
    strret = yield (done) => {
        lua.doString(`
            -- cjson = require("cjson");
            return {1,2,3}
        `, done);
    };
    console.log('dostr test :', strret);
    console.timeEnd('dostr2');
    console.time('dofile');
    let dofileret = yield (done) => {
        lua.doFile(__dirname + '/luatest.lua', done);
    };
    console.log('do file test retret:', dofileret);
    console.timeEnd('dofile');
    console.time('status');
    let status = yield (done) => {
        lua.status(done);
    };
    console.log('lua status:', status, MyLua.STATUS);
    console.timeEnd('status');


    let fs = require('fs');
    console.time('fs1');
    let file = yield (done) => {
        fs.readFile(__dirname + '/luatest.lua', done);
    };
    console.log('file:', file.toString().split('\n')[0]);
    console.timeEnd('fs1');


    yield (done) => {
        lua.callGlobalFunction('testArgAndRetGlobalCall', 11, 22, [666, 888, {
            'key1': 'arrval1',
            'key2': 'arrval2'
        }], function (err, ret, ret2, table) {
            console.log('callGlobalFunction!!:', err, ret, ret2, table);
            done();
        })
    };


}).catch((err) => {
    console.log('!! test err:', err);
});


function testAsyncAndSingle() {

    let lua1 = new MyLua();
    let lua2 = new MyLua();

    lua1.doString('print("hello world") return "rettest"', function (err, ret) {
        console.log('lua1 dostring ret:', err, ret)
    });
    lua2.doString('print("hello world") return "rettest"', function (err, ret) {
        console.log('lua2 dostring ret:', err, ret)
    });


    lua1.doFile(__dirname + '/luatest.lua', function (err, ret) {
        console.log('lua1 doFile ret:', err, ret)
    });


    lua2.doFile(__dirname + '/luatest.lua', function (err, ret) {
        console.log('lua2 doFile ret:', err, ret)
    });

}

