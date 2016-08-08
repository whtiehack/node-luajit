var nodelua = null;

try{
    nodelua = require('./build/Release/node-luajit');
}catch(e){
    console.log('```  release load err:',e);
    nodelua = require('./build/Debug/node-luajit');
}

module.exports = nodelua;