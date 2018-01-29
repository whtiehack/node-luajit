

// prepare luajit cjson protobuf

const shell = require('shelljs');
// (test -d 3rdlibs || mkdir 3rdlibs) && cd 3rdlibs && wget http://luajit.org/download/LuaJIT-2.0.5.tar.gz && tar -xf LuaJIT-2.0.5.tar.gz

const url = 'http://luajit.org/download/LuaJIT-2.1.0-beta3.tar.gz';
const cjsonurl = 'https://github.com/openresty/lua-cjson/archive/master.zip';
const cjsonname = 'lua-cjson';
const luajitname = 'LuaJIT';
const os = require('os');
if(os.platform() === 'darwin'){
//    console.error(new Error('auto prepare,maybe not support '+ os.platform()));
 //   return;
    console.log('os x can not use luajit');
    return;
}
if(os.platform()!=='linux'){
    console.log('prepare only for linux');
    return;
}
if(!shell.test('-d','3rdlibs')){
    shell.mkdir('3rdlibs');
}else{
    shell.rm('-rf','3rdlibs/'+luajitname);
    shell.rm('-rf','3rdlibs/'+cjsonname);
}

shell.cd('3rdlibs');
if(shell.test('-d',luajitname)){
    console.log(luajitname+' has exists');
    return 0;
}

shell.exec('wget '+ url + ' -O '+luajitname+'.tar.gz');
shell.exec('mkdir '+luajitname);
shell.exec('tar -xf '+luajitname+'.tar.gz --strip-components 1 -C ./'+luajitname);
shell.rm(luajitname+'.tar.gz');
shell.cd(luajitname);
shell.exec('make');
shell.cd('..');
shell.exec('wget ' + cjsonurl + ' -O '+ cjsonname +'.zip');
shell.exec('unzip -d '+ cjsonname+ ' -j '+ cjsonname +'.zip');
shell.rm(cjsonname+'.zip');
shell.cd(cjsonname);
shell.exec('make LUA_INCLUDE_DIR="../'+luajitname+'/src" LUA_BIN_DIR="../'+ luajitname+'/src" LUA_CMODULE_DIR="../' + luajitname+'/src" LUA_MODULE_DIR="../'+luajitname+'/src"');
if(os.platform() !== 'win32'){
  //  shell.exec('sudo make install');
}
return 0;

