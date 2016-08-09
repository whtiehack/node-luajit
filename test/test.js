

var MyLua = require('../');
console.log('test');




var lua = new MyLua();

console.log('lua test:',lua);

lua.doFile('fdafda',function(err,ret){
    console.log('hahahah err:',err,'retret:',ret);
});

setTimeout(function(){
    console.log('eddd');
},2000);