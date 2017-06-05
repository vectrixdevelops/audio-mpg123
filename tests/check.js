
var test = require('tape')
var mpg123 = require('../lib/audio_mpg123.node')

test('exports functions', function (t) {
  t.plan(5)
  
  console.log(mpg123)

  t.true(mpg123.create, 'mpg123.create')
  t.true(mpg123.open, 'mmpg123.open')
  t.true(mpg123.close, 'mpg123.close')
  t.true(mpg123.write, 'mpg123.write')
  t.true(mpg123.flush, 'mpg123.flush')

})
