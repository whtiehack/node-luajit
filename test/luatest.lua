--
-- Created by IntelliJ IDEA.
-- User: mac
-- Date: 16/8/9
-- Time: 下午6:53
-- To change this template use File | Settings | File Templates.
--

print('hello lua!! version:' .. _VERSION);


print('cjson:',cjson.encode({5,6,7}))


function testArgAndRetGlobalCall(arg1,arg2)
    print('testArgAndRetGlobalCall',arg1,arg2)
    return arg1 .. arg2,'fdafd';
end