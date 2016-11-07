var path = require('path')

module.exports = require(require('node-pre-gyp').find(path.resolve(path.join(__dirname, './package.json'))))
