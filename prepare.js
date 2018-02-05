

// prepare luajit cjson protobuf

var shell = require('shelljs');
// (test -d 3rdlibs || mkdir 3rdlibs) && cd 3rdlibs && wget http://luajit.org/download/LuaJIT-2.0.5.tar.gz && tar -xf LuaJIT-2.0.5.tar.gz

var url = 'http://luajit.org/download/LuaJIT-2.1.0-beta3.tar.gz';
var luajitname = 'LuaJIT-2.1.0-beta3';
var os = require('os');
if(os.platform() == 'darwin'){
//    console.error(new Error('auto prepare,maybe not support '+ os.platform()));
 //   return;
    console.log('os x can not use luajit');
    return;
}
if(os.platform()!='linux'){
    console.log('prepare only for linux');
    return;
}
if(!shell.test('-d','3rdlibs')){
    shell.mkdir('3rdlibs');
}

shell.cd('3rdlibs');
if(shell.test('-d',luajitname)){
    console.log(luajitname+' has exists');
    return 0;
}

shell.exec('wget '+ url);
shell.exec('tar -xf '+luajitname+'.tar.gz');
shell.rm(luajitname+'.tar.gz');
shell.cd(luajitname);
shell.exec('make');
if(os.platform != 'win32'){
  //  shell.exec('sudo make install');
}
return 0;

