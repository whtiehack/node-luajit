--
-- Created by IntelliJ IDEA.
-- User: mac
-- Date: 16/8/10
-- Time: 上午10:54
-- To change this template use File | Settings | File Templates.
--

-- LUASINGLEIDX

local oriPrint = print;
function print(...)
    oriPrint('[LUA-' .. LUASINGLEIDX ..' PRINT]',...)
    io.flush()
end