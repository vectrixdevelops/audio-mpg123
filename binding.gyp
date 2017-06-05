{
    'variables': {
        'target_arch%': 'ia32',
        'conditions': [
            ['OS=="mac"', {
                'mpg123_module%': 'coreaudio'
            }],
            ['OS=="win"', {
                'mpg123_module%': 'win32'
            }],
            ['OS=="linux"', {
                'mpg123_module%': 'alsa'
            }]
        ]
    },
    'target_defaults': {
        'configurations': {
            'Debug': {
                'defines': [
                    'DEBUG'
                ],
                'msvs_settings': {
                    'VCCLCompilerTool': {
                        'RuntimeLibrary': 1
                    }
                }
            },
            'Release': {
                'defines': [
                    'NDEBUG'
                ],
                'msvs_settings': {
                    'VCCLCompilerTool': {
                        'RuntimeLibrary': 0
                    }
                }
            }
        },
        'cflags!': [ '-fno-exceptions' ],
        'cflags_cc!': [ '-fno-exceptions' ],
        'xcode_settings': {
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
            'CLANG_CXX_LIBRARY': 'libc++',
            'MACOSX_DEPLOYMENT_TARGET': '10.7',
        },
        'msvs_settings': {
            'VCLinkerTool': {
                'GenerateDebugInformation': 'true',
                'CLCompilerTool': { 'ExceptionHandling': 1 }
            }
        },
        'conditions': [
            ['OS=="mac"', {
                'conditions': [
                    ['target_arch=="ia32"', { 'xcode_settings': { 'ARCHS': [ 'i386' ] } }],
                    ['target_arch=="x64"', { 'xcode_settings': { 'ARCHS': [ 'x86_64' ] } }]
                ]
            }]
        ]
    },
    'targets': [
        {
            'target_name': 'audio_mpg123',
            'win_delay_load_hook': 'true',
            'sources': [
                'src/audio-mpg123.cpp'
            ],
            'include_dirs': [
                "<!@(node -p \"require('node-addon-api').include\")",
                'src/util'
            ],
            'dependencies': [
                "<!(node -p \"require('node-addon-api').gyp\")",
                'module'
            ]
        },
        {
            'target_name': 'after_build',
            'type': 'none',
            'dependencies': [ 'audio_mpg123' ],
            'copies': [
                {
                    'files': [ '<(PRODUCT_DIR)/audio_mpg123.node' ],
                    'destination': 'lib/'
                }
            ]
        },
        {
            'target_name': 'out123',
            'type': 'static_library',
            'dependencies': [ 'compat' ],
            'include_dirs': [
                'src/mpg123/src/libout123',
                'src/config/<(OS)/<(target_arch)'
            ],
            'defines': [
                'PIC',
                'NOXFERMEM',
                'HAVE_CONFIG_H'
            ],
            'direct_dependent_settings': {
                'include_dirs': [
                    'src/mpg123/src/libout123',
                    'src/config/<(OS)/<(target_arch)'
                ]
            },
            'sources': [
                'src/mpg123/src/libout123/legacy_module.c',
                'src/mpg123/src/libout123/libout123.c',
                'src/mpg123/src/libout123/sfifo.c',
                'src/mpg123/src/libout123/stringlists.c',
                'src/mpg123/src/libout123/wav.c'
            ]
        },
        {
            'target_name': 'compat',
            'type': 'static_library',
            'defines': [
                'PIC',
                'NOXFERMEM',
                'HAVE_CONFIG_H'
            ],
            'sources': [
                'src/mpg123/src/compat/compat.c',
                'src/mpg123/src/compat/compat_str.c'
            ],
            'conditions': [
                ['mpg123_module=="coreaudio"', {
                    'direct_dependent_settings': {
                        'include_dirs': [
                            'src/mpg123/src',
                            'src/mpg123/src/compat',
                            'src/mpg123/src/libmpg123',
                            'src/config/<(OS)/<(target_arch)'
                        ]
                    },
                    'include_dirs': [
                        'src/mpg123/src',
                        'src/mpg123/src/compat',
                        'src/mpg123/src/libmpg123',
                        'src/config/<(OS)/<(target_arch)'
                    ],
                }],
                ['mpg123_module=="win32"', {
                    'direct_dependent_settings': {
                        'include_dirs': [
                            'src/util',
                            'src/mpg123/src',
                            'src/mpg123/src/compat',
                            'src/mpg123/src/libmpg123',
                            'src/config/<(OS)/<(target_arch)'
                        ]
                    },
                    'include_dirs': [
                        'src/util',
                        'src/mpg123/src',
                        'src/mpg123/src/compat',
                        'src/mpg123/src/libmpg123',
                        'src/config/<(OS)/<(target_arch)'
                    ],
                }],
                ['mpg123_module=="alsa"', {
                    'direct_dependent_settings': {
                        'include_dirs': [
                            'src/mpg123/src',
                            'src/mpg123/src/compat',
                            'src/mpg123/src/libmpg123',
                            'src/config/<(OS)/<(target_arch)'
                        ]
                    },
                    'include_dirs': [
                        'src/mpg123/src',
                        'src/mpg123/src/compat',
                        'src/mpg123/src/libmpg123',
                        'src/config/<(OS)/<(target_arch)'
                    ],
                }],
                ['mpg123_module=="dummy"', {
                    'direct_dependent_settings': {
                        'include_dirs': [
                            'src/mpg123/src',
                            'src/mpg123/src/compat',
                            'src/mpg123/src/libmpg123',
                            'src/config/<(OS)/<(target_arch)'
                        ]
                    },
                    'include_dirs': [
                        'src/mpg123/src',
                        'src/mpg123/src/compat',
                        'src/mpg123/src/libmpg123',
                        'src/config/<(OS)/<(target_arch)'
                    ],
                }]
            ],
        },
        {
            'target_name': 'module',
            'type': 'static_library',
            'dependencies': ['compat', 'out123' ],
            'include_dirs': [
                'src/mpg123/src',
                'src/mpg123/src/libout123/modules',
                'src/mpg123/src/libmpg123',
                'src/config/<(OS)/<(target_arch)'
            ],
            'defines': [
                'PIC',
                'NOXFERMEM',
                'REAL_IS_FLOAT',
                'HAVE_CONFIG_H',
                'BUILDING_OUTPUT_MODULES=1'
            ],
            'direct_dependent_settings': {
                'include_dirs': [
                    'src/mpg123/src',
                    'src/mpg123/src/libout123/modules',
                    'src/mpg123/src/libmpg123',
                    'src/config/<(OS)/<(target_arch)'
                ]
            },
            'conditions': [
                ['mpg123_module=="coreaudio"', {
                    'link_settings': {
                        'libraries': [
                            '-framework AudioToolbox',
                            '-framework AudioUnit',
                            '-framework CoreServices'
                        ]
                    }
                }],
                ['mpg123_module=="win32"', {
                    'link_settings': {
                        'libraries': [
                            '-lwinmm.lib'
                        ]
                    }
                }],
                ['mpg123_module=="alsa"', {
                    'link_settings': {
                        'libraries': [
                            '-lasound'
                        ]
                    }
                }]
            ],
            'sources': [ 'src/mpg123/src/libout123/modules/<(mpg123_module).c' ]
        }
    ]
}
