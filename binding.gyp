{
    'targets': [
        {
            'target_name': 'audio-speaker-native',
            'sources': [
                'audio-speaker-native.cc'
            ],
            'include_dirs': [
                '<!@(node -p "require(\'node-addon-api\').include")',
                '<!@(pkg-config --cflags-only-I libout123 | sed s/-I//g)'
            ],
            'dependencies': [
                '<!(node -p "require(\'node-addon-api\').gyp")'
            ],
            'ldflags': [
                '<!@(pkg-config --libs-only-L libout123)'
            ],
            'libraries': [
                '<!@(pkg-config --libs-only-l libout123)'
            ],
            'defines': [
                'NAPI_DISABLE_CPP_EXCEPTIONS'
            ],
        }
    ]
}
