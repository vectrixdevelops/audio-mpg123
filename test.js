
var test = require('tape')
var mpg123 = require('./lib/audio_mpg123.node')

test('exports functions', function (t) {
  t.plan(1)
  console.log(mpg123)
  t.true(
    mpg123
    && mpg123.create
    && mpg123.open
    && mpg123.close
    && mpg123.write
    && mpg123.flush
  )
})

test('opens mpg123', function (t) {
  t.plan(3)

  var p = mpg123.create()
  t.true(p, 'got pointer')

  t.true(mpg123.open(p, 44100, 2, mpg123.F32), 'opened successfully')

  t.true(mpg123.close(p), 'closed successfully');
})
