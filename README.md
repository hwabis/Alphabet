# Alphabet

Alphabet is a rhythm game written in SDL. It can load any Taiko beatmap from the rhythm game [osu!](https://osu.ppy.sh/home). 

https://user-images.githubusercontent.com/62194990/121930565-85080c00-cd10-11eb-825d-a10befbde4c4.mov

<sup>[ARForest - Altros [Futsuu] by Eyenine](https://osu.ppy.sh/beatmapsets/1184727#taiko/2469843)</sup>

## Running

When running Alphabet.exe, if you get an error about MSVCP140.dll or VCRUNTIME140.dll, make sure you have both the x86 and x64 versions of [Microsoft Visual C++ Redistributable for Visual Studio 2015, 2017 and 2019](https://support.microsoft.com/en-us/topic/the-latest-supported-visual-c-downloads-2647da03-1eea-4433-9aff-95f26a218cc0) installed.

If Windows Defender SmartScreen appears, click "More info" and "Run anyway". (I know this doesn't look good, and I don't know how to fix this...)

## Loading a map

First, make sure your map can be opened and played in osu!. (In other words, make sure the mapset .osz file is extracted.)

Then enter the map path; make sure to get the full name. For example, given an osu! installation in the default path, you could enter:

```
C:\Users\<Username>\AppData\Local\osu!\Songs\1184727 ARForest - Altros\ARForest - Altros (Eyenine) [Futsuu].osu
```

A quick way to get the path is to open the beatmap in the osu! editor, and then go to File > Open Song Folder.

## Notes

This game is difficult compared to the traditional osu! gamemodes. Even if you are experienced in rhythm games, I'd suggest starting at a Futsuu difficulty or below. Scoring an S rank on a Muzukashii difficulty would be very impressive. :)

Source of the included example map: [Ray - Nagi [Kantan] by mingmichael](https://osu.ppy.sh/beatmapsets/146008#taiko/364949)
