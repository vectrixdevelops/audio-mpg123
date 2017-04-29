{
    'targets': [
        {
            'target_name': 'audio_mpg123',
            'win_delay_load_hook': 'true',
            'sources': [
                'src/mpg123-wrapper.cpp',
                'src/util/getopt.c'
            ],
            'include_dirs': [
                'src/util',
                '<!(node -e "require(\'nan\')")'
            ],
            'dependencies': [
                'src/mpg123.gyp:module'
            ]
        },
        {
            "target_name": "after_build",
            "type": "none",
            "dependencies": [ "audio_mpg123" ],
            "copies": [
                {
                    "files": [ "<(PRODUCT_DIR)/audio_mpg123.node" ],
                    "destination": "./lib/"
                }
            ]
        }
    ]
}
