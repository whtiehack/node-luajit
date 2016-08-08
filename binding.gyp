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
          'OS=="mac" or OS=="linux"',
          {
            "include_dirs": [
              "<!(find /usr/include /usr/local/include $NODELUA_INCLUDE -name lua.h | sed s/lua.h//)"
            ],
          }
        ],
        [
          'OS=="mac"',
          {
            "library_dirs": [
              "/usr/local/lib"
            ],
            "libraries": [
              "libluajit-5.1.dylib"
            ],
            'xcode_settings': {
              'OTHER_LDFLAGS': [
                '-pagezero_size 10000 -image_base 100000000'
              ],
            }
          }
        ],
        [
          'OS=="linux"',
          {
            "library_dirs": [
              "/usr/local/lib"
            ],
            "libraries": [
              "libluajit-5.1.a"
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