--
-- Created by IntelliJ IDEA.
-- User: mac
-- Date: 16/8/9
-- Time: 下午6:53
-- To change this template use File | Settings | File Templates.
--

print('hello lua!! version:' .. _VERSION);


print('cjson:',cjson.encode({5,6,7}))



function testArgAndRetGlobalCall(arg1,arg2,arg3tbl)
    print('testArgAndRetGlobalCall',arg1,arg2,arg3tbl)
    PrintTable(arg3tbl);
    return arg1 .. arg2,'fdafd',{'myval',666,nestedTbl={'val1','val2'}};
end

print("luatest.lua run finished")
