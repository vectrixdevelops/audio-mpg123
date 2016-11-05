{
    'targets': [
        {
            'target_name': '<(module_name)',
            'win_delay_load_hook': 'true',
            'sources': [
                'src/binding.cpp',
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
            "dependencies": [ "<(module_name)" ],
            "copies": [
                {
                    "files": [ "<(PRODUCT_DIR)/<(module_name).node" ],
                    "destination": "<(module_path)"
                }
            ]
        }
    ]
}
