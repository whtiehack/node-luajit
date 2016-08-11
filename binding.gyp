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
            ],
            "actions": [
              {
                'action_name': 'move_cjson',
                'inputs': [
                  '<(module_root_dir)/cjsonlib/cjson.dll'
                ],
                'outputs': [
                  '<(module_root_dir)/build/Release/cjson.dll'
                ],
                'action': [
                  'cp',
                  '<(module_root_dir)/cjsonlib/cjson.dll',
                  '<(module_root_dir)/build/Release/cjson.dll'
                ]
              },
              {
                'action_name': 'move_lua',
                'inputs': [
                  '<(module_root_dir)/win64luajit/lua51.dll'
                ],
                'outputs': [
                  '<(module_root_dir)/build/Release/lua51.dll'
                ],
                'action': [
                  'cp',
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
              "./maclualib/include"
            ],
            "libraries": [
              "../maclualib/lib/liblua.a"
            ],
            "actions": [
              {
                'action_name': 'move_cjson',
                'inputs': [
                  '<(module_root_dir)/cjsonlib/mac_cjson.so'
                ],
                'outputs': [
                  '<(module_root_dir)/build/Release/cjson.so'
                ],
                'action': [
                  'cp',
                  '<(module_root_dir)/cjsonlib/mac_cjson.so',
                  '<(module_root_dir)/build/Release/cjson.so'
                ]
              }
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
              "<!(find /usr/include /usr/local/include $NODELUA_INCLUDE -name lua.h | sed s/lua.h//)"
            ],
            "library_dirs": [
              "/usr/local/lib"
            ],
            "libraries": [
              "/usr/local/lib/libluajit-5.1.so.2.0.4"
            ],
            "actions": [
              {
                'action_name': 'move_cjson',
                'inputs': [
                  '<(module_root_dir)/cjsonlib/linux_cjson.so'
                ],
                'outputs': [
                  '<(module_root_dir)/build/Release/cjson.so'
                ],
                'action': [
                  'cp',
                  '<(module_root_dir)/cjsonlib/linux_cjson.so',
                  '<(module_root_dir)/build/Release/cjson.so'
                ]
              }
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
        "src/MyLuaState.cpp"
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}