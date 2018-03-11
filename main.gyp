{
  'targets': [
    {
      'target_name': 'main',
      'type': 'executable',
      'include_dirs': [
        '.',
        'third_party/node/src',
        'third_party/node/deps/v8/include',
        'third_party/node/deps/uv/include',
        'third_party/node/deps/cares/include',
      ],
      'sources': [
        'main.cc'
      ],
      'dependencies': [
        'third_party/node/node.gyp:node',
      ],
      'defines': [
        'NODE_WANT_INTERNALS=1',
        'NODE_SHARED_MODE',
        'HAVE_INSPECTOR=0',
        'NODE_USE_V8_PLATFORM=1',
        'HAVE_OPENSSL=1',
      ],
      'xcode_settings': {
        'GCC_VERSION': 'com.apple.compilers.llvm.clang.1_0',
        'CLANG_CXX_LANGUAGE_STANDARD': 'gnu++0x',  # -std=gnu++0x
        'CLANG_CXX_LIBRARY': 'libc++',
      },
      'postbuilds': [
        {
          'postbuild_name': 'Fix path of libnode',
          'action': [
            'install_name_tool',
            '-change',
            '/usr/local/lib/libnode.57.dylib',
            '@executable_path/libnode.57.dylib',
            '${BUILT_PRODUCTS_DIR}/main',
           ],
        },
      ]
    },
  ]
}
