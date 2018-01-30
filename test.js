
const speaker = require('./audio-speaker-native.js')
const lenaBuffer = require('audio-lena/raw')
const audioBufferFrom = require('audio-buffer-from')

const buffer = audioBufferFrom(lenaBuffer)

const write = speaker()

write(buffer)
