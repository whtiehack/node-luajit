{
  "targets": [
    {
      "target_name": "node-luajit",
      "variables": {
        "lua_include": "",
        "lib_dirs": ""
      },
      "conditions": [
        [
          "OS=='win'",
          {
            "include_dirs": [
              "D:\\Develop\\LuaJIT-2.0.3\\src"
            ],
            "library_dirs": [
              "D:\\Develop\\LuaJIT-2.0.3\\src"
            ],
            "libraries": [
              "lua51.lib"
            ]
          }
        ],
        [
          'OS=="linux"',
          {
            "include_dirs": [
              "<!(find /usr/include /usr/local/include $NODELUA_INCLUDE -name lua.h | sed s/lua.h//)"
            ],
          }
        ],
        [
          'OS=="mac"',
          {
            "include_dirs": [
              "./maclualib/include"
            ],
            "libraries": [
              "../maclualib/lib/liblua.a"
            ]
          }
        ],
        [
          'OS=="linux"',
          {
            "library_dirs": [
              "/usr/local/lib"
            ],
            "libraries": [
              "/usr/local/lib/libluajit-5.1.so.2.0.4"
            ]
          }
        ]
      ],
      "sources": [
        "src/utils.cc",
        "src/luastate.cc",
        "src/nodelua.cc"
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}