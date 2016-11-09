# audio-mpg123

> A native node binding to write raw PCM data to an OS driver.

This is a pure native node binding for the library mpg123. This is used particularly with audio-speaker
which provides a nice API over this native binding to play audio. 

**It is highly recommended you use audio-speaker if you are looking for a way to play audio. Please
look at [audio-speaker][speaker-link] before using this module.**

## Install

Basic install (pre-built): `npm install audio-mpg123`
 
*Advanced install is not recommended at this time as it is difficult to use at production.
We are working on a fix for this.*

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
