'use strict';

var MyLua = require('../');
console.log('test');




var lua = new MyLua();

lua.doString(`
local oriPrint = print;
function print(...)
    oriPrint('lua:',...)
end
cjson = require("cjson"); 
return {1,2,3}
`,function(err,ret){
    console.log('dostr test :',err,ret);
});


lua.doFile(__dirname+'/luatest.lua',function(err,ret){
    console.log('do file test err:',err,'retret:',ret);
});


