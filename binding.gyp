{
  "targets": [
    {
      "target_name": "node-luajit",
      "variables": {
        "lua_include": "<!(find /usr/include /usr/local/include $NODELUA_INCLUDE -name lua.h | sed s/lua.h//)"
        },
      "sources": [ "src/utils.cc" ,"src/luastate.cc","src/nodelua.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "<@(lua_include)"
      ]
    }
  ]
}