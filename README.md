## Node-luajit binding

similar as `https://github.com/brettlangdon/NodeLua`


## feature

> nodejs -> lua  is async.
> nodejs -> lua  in queue, so lua internal is sync.
> all luaState  are independent.
> now lua can't call nodejs direct.



## simple usage

```
var MyLua = require('node-luajit');
var lua = new MyLua();

lua.doString('print("hello world") return "rettest"',function(err,ret){
    console.log('dostring ret:',err,ret)
});



lua.doFile(__dirname+'/test/luatest.lua',function(err,ret){
    console.log('doFile ret:',err,ret)
});



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


```

