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
              "./win64luajit"
            ],
            "library_dirs": [
              "./win64luajit"
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
              "<(module_root_dir)/maclualib/include"
            ],
            "libraries": [
              "<(module_root_dir)/maclualib/lib/liblua.a"
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
              "<(module_root_dir)/3rdlibs/LuaJIT/src"
            ],
            "library_dirs": [
              "/usr/local/lib"
            ],
            "libraries": [
              "<(module_root_dir)/3rdlibs/LuaJIT/src/libluajit.so"
            ],
            "actions": [
              {
                'action_name': 'move_cjson',
                'inputs': [
                  '<(module_root_dir)/3rdlibs/lua-cjson/cjson.so'
                ],
                'outputs': [
                  '<(module_root_dir)/build/Release/cjson.so'
                ],
                'action': [
                  'cp',
                  '<(module_root_dir)/3rdlibs/lua-cjson/cjson.so',
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