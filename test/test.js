

var MyLua = require('../');
console.log('test');




var lua = new MyLua();


lua.doFile('fdafda',function(err,ret){
    console.log('hahahah err:',err,'retret:',ret);
});

lua.doString('print("12121"); local cjson; cjson = require("cjson"); ',function(err,ret){
    console.log('ha dostr :',err,ret);
});

setTimeout(function(){
    console.log('eddd');
},2000);