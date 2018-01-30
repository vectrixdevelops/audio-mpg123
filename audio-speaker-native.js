
const binding = require('bindings')('audio-speaker-native')
const parseFormat = require('audio-format').parse

module.exports = (options = {}) => {
  options = Object.assign({
    format: 'mono 44100 float32'
  }, options)

  let format = parseFormat(options.format)
  let type = binding.types[format.type]
  let ao = binding.open(format.channels, format.sampleRate, type)

  function write (buffer) {
    if (!buffer) binding.close(ao)
    binding.write(ao, buffer)
  }

  return write
}
