var check = true;

try {
  require.resolve('node-pre-gyp')
} catch (err) {
  check = false
  console.log('To install this module you must have "node-pre-gyp" installed globally or locally.')
  process.exit(1)
}

module.exports = check
