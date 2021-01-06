'use strict';
let path = require('path');
const binary = require('node-pre-gyp');
const binding_path = binary.find(path.resolve(path.join(__dirname, 'package.json')));
const nodelua = require(binding_path);

let MyCLua = nodelua['MyLuaState'];

if (!nodelua) {
    console.error('no node lua')
    return;
}
let singleIdx = 0;

class MyLua {
    constructor(formatprint) {
        if (typeof (formatprint) == 'undefined') {
            formatprint = true;
        }
        singleIdx++;
        let self = this;
        self.lua = new MyCLua(singleIdx);
        //init path
        let paths = ';' + __dirname + '/?.so;' + __dirname + '/build/Release/?.so;' + __dirname + '/build/Release/?.dll';
        let luapaths = ';' + __dirname + '/?.lua;' + __dirname + '/test/?.lua;' + process.cwd() + '/?.lua';
        let luastr = 'package.cpath = package.cpath .. "' + paths + '";package.path = package.path .. "' + luapaths + '";LUASINGLEIDX = ' + singleIdx + ';';
        if (formatprint) {
            luastr += 'require("initlua.formatPrint");';
        }
        if (process.platform === 'win32') {
            luastr = luastr.replace(new RegExp('\\\\', 'g'), '/');
        }
        self.lua.doString(luastr, function (err, ret) {
            // console.log('  package path:',err,ret);
            if (err) {
                console.log('!!add find pash err:', err);
                console.log('lua:', luastr);
            }
        });
    }

    doFile(fn, cb) {
        return this.lua.doFile(fn, cb);
    }

    doString(str, cb) {
        return this.lua.doString(str, cb);
    }

    /**
     * cb(null,status)
     * @param cb
     */
    status(cb) {
        return this.lua.status(cb);
    }

    addPachagePath(path, isC) {
        let luavar = 'package.path';
        if (isC) {
            luavar = 'package.cpath';
        }
        let luastr = luavar + ' = ' + luavar + ' .. ";' + path + '";';
        return this.lua.doString(luastr);
    }

    /**
     *  call(funname[,args][,cb])  cb(err,ret)
     * @param funName
     * @returns {number}
     */
    callGlobalFunction(funName) {
        return this.lua.callGlobalFunction.apply(this.lua, arguments);
    }

    static GC = nodelua.GC;
    static STATUS = nodelua.STATUS;
    static INFO = nodelua.INFO;
}

module.exports = MyLua;
