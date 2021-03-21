# My Keymap for the [Kyria](https://github.com/splitkb/kyria) Keyboard

## Keymap
This is my personal keymap for Kyria with some mods. It is inspired by [Miryoku](https://github.com/manna-harbour/miryoku) but without the MEDR and NSSL layer. Instead there is a symbol layer (both halves) and an adjustment layer (RGB & media). Further, the number layer was a bit modified and moved to the right side.

### TrackPoint

I am using a ThinkPad TrackPoint on the right halve (master).The controller board is attached to the OLED sockets and the PCB of the Trackpoint is mounted on the bottom of the keyboard. I am using a labret cheek piercing instead the red rubber nibble and it goes through the puck hole in the PCB.

| <img src="https://github.com/crehmann/qmk_firmware/raw/crehmann_kyria/keyboards/kyria/keymaps/crehmann/assets/img002.jpeg" style="zoom:50%;" /> | <img src="https://github.com/crehmann/qmk_firmware/raw/crehmann_kyria/keyboards/kyria/keymaps/crehmann/assets/img001.jpeg" style="zoom:50%;" /> |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| <img src="https://github.com/crehmann/qmk_firmware/raw/crehmann_kyria/keyboards/kyria/keymaps/crehmann/assets/img004.jpeg" style="zoom:50%;" /> |                                                              |

### Build

For the right halve with the TrackPoint:

`make kyria:crehmann TRACKPOINT=1`

For the left halve with OLED display:

`make kyria:crehmann TRACKPOINT=0`

### References

* [crkbd/readme.org at master · manna-harbour/crkbd (github.com)](https://github.com/manna-harbour/crkbd/blob/master/trackpoint/readme.org)
* [Trackpoint · joric/jorne Wiki (github.com)](https://github.com/joric/jorne/wiki/Trackpoint)
* [alonswartz/trackpoint: How to integrate a trackpoint in a mechanical keyboard (github.com)](https://github.com/alonswartz/trackpoint)