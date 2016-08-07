{
  "targets": [
    {
      "target_name": "node-luajit",
      "variables": {
        "lua_include": "",
        "lib_dirs":""
        },
      "conditions":[
        ["OS=='win'",{
          "include_dirs":["D:\\Develop\\LuaJIT-2.0.3\\src"],
          "library_dirs":["D:\\Develop\\LuaJIT-2.0.3\\src"],
          "libraries": [ "lua51.lib" ]
        }],
        [
          'OS=="mac" or OS=="linux"',{
            "include_dirs":["<!(find /usr/include /usr/local/include $NODELUA_INCLUDE -name lua.h | sed s/lua.h//)"]
          }
        ]
      ],
      "sources": [ "src/utils.cc" ,"src/luastate.cc","src/nodelua.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}