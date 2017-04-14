# audio-mpg123

[![Greenkeeper badge](https://badges.greenkeeper.io/audiojs/audio-mpg123.svg)](https://greenkeeper.io/)

> A native node binding to write raw PCM data to an OS driver.

This is a pure native node binding for the library mpg123. This is used particularly with audio-speaker
which provides a nice API over this native binding to play audio.

**It is highly recommended you use audio-speaker if you are looking for a way to play audio. Please
look at [audio-speaker][speaker-link] before using this module.**

## Install

Basic install (pre-built): `npm install audio-mpg123`

*Advanced install is not recommended at this time as it is difficult to use at production.
We are working on a fix for this.*

## Usage

### `mpg123.create(finish)`

Creates new `out123_handle` and returns pointer that is used in subsequent calls.  The `finish` param is a callback as `finish(success)` with either `1` or `0`.

```js
var pointer = mpg123.create(function (success) {
  if (success === 0) {
    // ...
  }
})
```

### `mpg123.open(pointer, sampleRate, channels, encoding, finish)`

Start out123 with `sampleRate`, `channels`, and `encoding`.  The `finish` param is a callback as `finish(success)` with either `1` or `0`

```js
mpg123.open(pointer, 44100, 2, mpg123.MPG123_ENC_FLOAT_32, function (success) {
  if (success === 0) // ...
})
```

The different formats are constants in the form of:

```js
mpg123.MPG123_ENV_<SIGNED|UNSIGNED>_<8|16|24|32>
mpg123.MPG123_ENV_FLOAT_<32|64>
```

This specifies if it is signed/unsigned, the bitdepth, and if it is a float.

### `mpg123.write(pointer, buf, length, finish)`

Write to out123 with `buf` and `length`.  `finish` is called as `finish(success)` with `1` and `0`

```js
mpg123.write(pointer, buf, buf.length, function (success) {
  if (success === 0) // ...
})
```

### `mpg123.flush(pointer, finish)`

Flush out123 (clears `write` buffer) and handle `finish(success)` with either `1` or `0`

```js
mpg123.flush(pointer, function (success) {
  if (success === 0) // ...
})
```

### `mpg123.close(pointer, finish)`

Close out123 and handle `finish(success)` with either `1` or `0`

```js
mpg123.close(pointer, function (success) {
  if (success === 0) // ...
})
```

## Support

Out123 Version: 2

The following device support table below only applies to those wanting the pre-built binary.

|      Operating System       |             Node             |            Arch             |          Driver             |
| :-------------------------: | :--------------------------: | :-------------------------: | :-------------------------: |
|          Windows            |        4.x, 6.x, 7.x         |            x64              |           win32             |
|           Linux             |      4.x, 5.x, 6.x, 7.x      |            x64              |           alsa              |

It is important to note that if you need support other than what's in this table, it is
possible to build the binary yourself.

NOTE: Windows, Linux and MacOS are currently the only supported operating systems.
We are unable to provide a prebuilt binary for Windows ia32 and MacOS x64 at this time and when you install the module,
you will need build tools to build it yourself.

## Credits

| ![connor][connor-avatar]      | ![jamen][jamen-avatar]       |
| :---------------------------: | :---------------------------: |
| [Connor Hartley][connor-link] | [Jamen Marz][jamen-link]      |

  [speaker-link]: https://github.com/audiojs/audio-speaker

  [connor-avatar]: https://avatars0.githubusercontent.com/u/12867785?v=3&s=125
  [connor-link]: https://github.com/connorhartley
  [jamen-avatar]: https://avatars.githubusercontent.com/u/6251703?v=3&s=125
  [jamen-link]: https://github.com/jamen
