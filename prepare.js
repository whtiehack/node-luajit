

// prepare luajit cjson protobuf

// (test -d 3rdlibs || mkdir 3rdlibs) && cd 3rdlibs && wget http://luajit.org/download/LuaJIT-2.0.5.tar.gz && tar -xf LuaJIT-2.0.5.tar.gz

const url = 'http://luajit.org/download/LuaJIT-2.1.0-beta3.tar.gz';
const cjsonurl = 'https://github.com/openresty/lua-cjson/archive/master.zip';
const cjsonname = 'lua-cjson';
const luajitname = 'LuaJIT';
const os = require('os');
const fs = require('fs');
const spawn = require('child_process').spawn;
if(os.platform() === 'win32'){
    //  shell.exec('sudo make install');
    // console.warn(' windows maybe trigger error. because windows not have wget,tar and unzip command!');
}

if(os.platform() === 'darwin'){
    console.warn('os x can not use luajit,use default maclualib');
    return 0;
}
let child;

if(os.platform() === 'win32'){
    child = spawn('cd 3rdlibs\\LuaJIT\\src && msvcbuild.bat',{shell:true});
}else{
    child = spawn('cd 3rdlibs/LuaJIT && make && make install',{shell:true});
}

child.stdout.pipe(process.stdout);

child.stderr.pipe(process.stderr);

child.on('close',function(code){
    console.log('compile LuaJIT result code:',code);
});


//shell.cd(cjsonname);
//shell.exec('make LUA_INCLUDE_DIR="../'+luajitname+'/src" LUA_BIN_DIR="../'+ luajitname+'/src" LUA_CMODULE_DIR="../' + luajitname+'/src" LUA_MODULE_DIR="../'+luajitname+'/src"');

return 0;

