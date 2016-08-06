var nodelua = null;

try{
    nodelua = require('./build/Release/node-luajit');
}catch(e){
    nodelua = require('./build/Debug/node-luajit');
}

module.exports = nodelua;