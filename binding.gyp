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
              "<(module_root_dir)/3rdlibs/LuaJIT/src"
            ],
            "library_dirs": [
              "./win64luajit"
            ],
            "libraries": [
              "lua51.lib"
            ],
            "actions": [
              {
                'action_name': 'move_lua',
                'inputs': [
                  '<(module_root_dir)/win64luajit/lua51.dll'
                ],
                'outputs': [
                  '<(module_root_dir)/build/Release/lua51.dll'
                ],
                'action': [
                  'copy',
                  '<(module_root_dir)/win64luajit/lua51.dll',
                  '<(module_root_dir)/build/Release/lua51.dll'
                ]
              }
            ],
          }
        ],
        [
          'OS=="mac"',
          {
            "include_dirs": [
              "<(module_root_dir)/maclualib/include"
            ],
            "libraries": [
              "<(module_root_dir)/maclualib/lib/liblua.a"
            ],
            "actions": [
            ],
            "cflags": [
              "-std=c++11",
              "-stdlib=libc++"
            ],
            "xcode_settings": {
              "CLANG_CXX_LANGUAGE_STANDARD": "c++0x",
              "CLANG_CXX_LIBRARY": "libc++"
            }
          }
        ],
        [
          'OS=="linux"',
          {
            "include_dirs": [
              "<(module_root_dir)/3rdlibs/LuaJIT/src"
            ],
            "library_dirs": [
              "<(module_root_dir)/3rdlibs/LuaJIT/src"
            ],
            "libraries": [
              "<(module_root_dir)/3rdlibs/LuaJIT/src/libluajit.so"
            ],
            "actions": [
            ]
          }
        ]
      ],
      "sources": [
        "src/utils.cc",
        "src/luastate.cc",
        "src/nodelua.cc",
        "src/MyLuaWorker.cpp",
        "src/MyWorkerQueue.cpp",
        "src/MyLuaState.cpp",
        "3rdlibs/lua-cjson/fpconv.c",
        "3rdlibs/lua-cjson/lua_cjson.c",
        "3rdlibs/lua-cjson/strbuf.c"
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}