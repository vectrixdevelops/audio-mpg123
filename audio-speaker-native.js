
const binding = require('bindings')('audio-speaker-native')
const parseFormat = require('audio-format').parse
const convert = require('pcm-convert')

module.exports = (options = {}) => {
  options = Object.assign({
    format: 'mono 44100 float32',
    chunkSize: 10000
  }, options)

  let format = parseFormat(options.format)
  let type = binding.types[format.type]
  let ao = binding.open(format.channels, format.sampleRate, type)

  return function write (audioBuffer, done) {
    if (!audioBuffer) binding.close(ao)
    const buffer = convert(audioBuffer, 'float32 interleaved').buffer
    binding.write(ao, buffer, done)
  }
}
