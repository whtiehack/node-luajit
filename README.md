## Node-luajit binding
#### Cross platform.  (win,mac,linux)[x64]
similar as `https://github.com/brettlangdon/NodeLua`


## feature

1. nodejs -> lua  is async.
2. nodejs -> lua  in queue, so lua internal is sync.
3. all luaState  are independent.
4. now lua can't call nodejs direct.
5. add,linux auto compile luajit.[2018-01-29] http://luajit.org/download/LuaJIT-2.1.0-beta3.tar.gz
6. add, cjson compile and auto load.  [2018-01-29] https://github.com/openresty/lua-cjson/archive/master.zip
7. > win64 need fix.


##Installation

`npm install node-luajit`
```
// some times maybe need 
npm install node-luajit --unsafe-perm

```

#### node 8.x 10.x: 
Linux build luajit
```
git clone https://github.com/LuaJIT/LuaJIT.git
make
sudo make install
```

and need add one line `/usr/local/lib` to ` /etc/ld.so.conf` file, and run `「/sbin/ldconfig –v」` refresh. 

or

```
ln -s /usr/local/lib/libluajit-5.1.so.2.0.4 /usr/lib

sudo ldconfig
```


## simple usage

```js
var MyLua = require('node-luajit');
var lua = new MyLua();

lua.doString('print("hello world") return "rettest"',function(err,ret){
    console.log('dostring ret:',err,ret)
});



lua.doFile(__dirname+'/test/luatest.lua',function(err,ret){
    console.log('doFile ret:',err,ret)
});



lua.callGlobalFunction('print',11,22,function(err,ret){
    console.log('callGlobalFunction!!:',err,ret);
})

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

### development


generate xcode project:

`node-gyp configure --debug -- -f xcode`

if got `TypeError: 'cmp' is an invalid keyword argument for sort()` error.


use `python2` instead, such as  `PYTHON=/usr/bin/python node-gyp configure -- -f xcode`

Now you should have a ./build/binding.xcodeproj which you can open. 

Configure the executable of the project in Xcode as node and debug away :)


