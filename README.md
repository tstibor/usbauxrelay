# USB ⇆ Nexstar AUX Relay for Celestron Mounts

[![Tag Version](https://img.shields.io/github/tag/tstibor/usbauxrelay.svg)](https://github.com/tstibor/usbauxrelay/tags)
[![License](http://img.shields.io/:license-gpl3-blue.svg)](http://www.gnu.org/licenses/gpl-3.0.html)

## Control Celestron Mounts via AUX Protocol (without Handcontrol)
Based on the excellent [NexStar AUX Command Set](https://github.com/tstibor/usbauxrelay/blob/main/doc/NexStar_AUX_Commands_10.pdf) documentation and previous projects
1) [NexStar Direct Telescope Mount Control](https://sites.google.com/site/wayneholder/nexstar-direct-telescope-mount-control)
2) [An Arduino-based controller for Celestron CG5-series equatorial mounts](https://github.com/juanmb/nextdriver/)
3) [Homebrew Mount-USB Connection for AUX-Port](https://www.cloudynights.com/topic/812944-homebrew-mount-usb-connection-for-aux-port/)

an USB ⇆ AUX relay is developed. The circuit (50k resistor and 1N4148 diode) is explained in 1) and also depicted in 2)
and emulates a Tri-State logic.

The used microcontroller in this project is a [Seeed Studio XIAO SAMD21](https://wiki.seeedstudio.com/Seeeduino-XIAO/)
ARM Cortex-M0+ 32bit 48MHz microcontroller(SAMD21G18) with 256KB Flash, 32KB SRAM and Arduino library compatible.

The final USB ⇆ Nexstar AUX relay dongle is depicted below:
![Final version USB ⇆ AUX relay](https://github.com/tstibor/usbauxrelay/blob/main/doc/usbauxrelay.png)

## Compiling the Firmware
Install [PlatformIO](https://platformio.org/) and run
```
$ pio run -t upload
...
...
Auto-detected: /dev/ttyACM0
Forcing reset using 1200bps open/close on port /dev/ttyACM0
Waiting for the new upload port...
Uploading .pio/build/seeed_xiao/firmware.bin
Atmel SMART device 0x10010005 found
Erase flash
done in 0.922 seconds

Write 27816 bytes to flash (435 pages)

[====                          ] 14% (64/435 pages)
[========                      ] 29% (128/435 pages)
[=============                 ] 44% (192/435 pages)
[=================             ] 58% (256/435 pages)
[======================        ] 73% (320/435 pages)
[==========================    ] 88% (384/435 pages)
[==============================] 100% (435/435 pages)
done in 0.173 seconds

Verify 27816 bytes of flash with checksum.
Verify successful
done in 0.036 seconds
CPU reset.
```

## Tracing AUX Packets
For tracing transmitted and received AUX packets attach the TX/RX pins of USB-TTL PL2303TA 3.3V cable to
pins 0 and 1 of the MCU. The MCU uses soft serial communication for tracing as the USART communication is already occupied for the AUX
communication. In addition make sure the [PlatformIO](https://platformio.org/) config file platformio.ini contains *build_flags = '-DAUX_DEBUG'*, that is,
```
[platformio]
default_envs = seeed_xiao

[env:seeed_xiao]
platform = atmelsam
board = seeed_xiao
framework = arduino
monitor_speed = 19200
monitor_port = /dev/ttyUSB0
build_flags = '-DAUX_DEBUG'
```

![Prototype version USB ⇆ AUX relay](https://github.com/tstibor/usbauxrelay/blob/main/doc/usbauxrelay_debug.png)

Celestron uses the AUX protocol for communicating with all devices connected to the mount. That is, one can see e.g. the AUX packets
transmitted and received to/from the handcontrol:
```
$ pio device monitor
[00544457ms,aux] Nexstar+ HC -> ALT MC, cmd MTR_GET_MODEL: AUX packet <0x3b, 0x03, 0x0d, 0x11, 0x05, 0xda> (checksum 0xda)
[00544603ms,aux] ALT MC -> Nexstar+ HC, cmd MTR_GET_MODEL: AUX packet <0x3b, 0x05, 0x11, 0x0d, 0x05, (0x14 0x85), 0x3f> (checksum 0x3f)
[00544736ms,aux] Nexstar+ HC -> AZM MC, cmd MTR_GET_MODEL: AUX packet <0x3b, 0x03, 0x0d, 0x10, 0x05, 0xdb> (checksum 0xdb)
[00544882ms,aux] AZM MC -> Nexstar+ HC, cmd MTR_GET_MODEL: AUX packet <0x3b, 0x05, 0x10, 0x0d, 0x05, (0x14 0x85), 0x40> (checksum 0x40)
[00545015ms,aux] Nexstar+ HC -> AZM MC, cmd MTR_GET_VERSION: AUX packet <0x3b, 0x03, 0x0d, 0x10, 0xfe, 0xe2> (checksum 0xe2)
[00545182ms,aux] AZM MC -> Nexstar+ HC, cmd NXS_GET_FW_VER: AUX packet <0x3b, 0x07, 0x10, 0x0d, 0xfe, (0x07 0x0f 0x20 0x4e), 0x5a> (checksum 0x5a)
[00545321ms,aux] Nexstar+ HC -> AZM MC, cmd MTR_IS_APPROACH_DIR_NEG: AUX packet <0x3b, 0x03, 0x0d, 0x10, 0xfc, 0xe4> (checksum 0xe4)
[00545463ms,aux] AZM MC -> Nexstar+ HC, cmd MTR_IS_APPROACH_DIR_NEG: AUX packet <0x3b, 0x04, 0x10, 0x0d, 0xfc, (0x00), 0xe3> (checksum 0xe3)
[00545598ms,aux] Nexstar+ HC -> ALT MC, cmd MTR_IS_APPROACH_DIR_NEG: AUX packet <0x3b, 0x03, 0x0d, 0x11, 0xfc, 0xe3> (checksum 0xe3)
[00545740ms,aux] ALT MC -> Nexstar+ HC, cmd MTR_IS_APPROACH_DIR_NEG: AUX packet <0x3b, 0x04, 0x11, 0x0d, 0xfc, (0x00), 0xe2> (checksum 0xe2)
[00545875ms,aux] Nexstar+ HC -> Focuser, cmd FUCUS_GET_FW_VER: AUX packet <0x3b, 0x03, 0x0d, 0x12, 0xfe, 0xe0> (checksum 0xe0)
[00546003ms,aux] Nexstar+ HC -> Focuser, cmd FUCUS_GET_FW_VER: AUX packet <0x3b, 0x03, 0x0d, 0x12, 0xfe, 0xe0> (checksum 0xe0)
[00546132ms,aux] Nexstar+ HC -> Focuser, cmd FUCUS_GET_FW_VER: AUX packet <0x3b, 0x03, 0x0d, 0x12, 0xfe, 0xe0> (checksum 0xe0)
[00546260ms,aux] Nexstar+ HC -> Focuser, cmd FUCUS_GET_FW_VER: AUX packet <0x3b, 0x03, 0x0d, 0x12, 0xfe, 0xe0> (checksum 0xe0)
[00546388ms,aux] Nexstar+ HC -> Focuser, cmd FUCUS_GET_FW_VER: AUX packet <0x3b, 0x03, 0x0d, 0x12, 0xfe, 0xe0> (checksum 0xe0)
[00546516ms,aux] Nexstar+ HC -> Dew Heater Controller, cmd DEWHEATER_GET_FW_VER: AUX packet <0x3b, 0x03, 0x0d, 0xbb, 0xfe, 0x37> (checksum 0x37)
[00546790ms,aux] Nexstar+ HC -> Dew Heater Controller, cmd DEWHEATER_GET_FW_VER: AUX packet <0x3b, 0x03, 0x0d, 0xbb, 0xfe, 0x37> (checksum 0x37)
[00547143ms,aux] Nexstar+ HC -> Dew Heater Controller, cmd DEWHEATER_GET_FW_VER: AUX packet <0x3b, 0x03, 0x0d, 0xbb, 0xfe, 0x37> (checksum 0x37)
[00547496ms,aux] Nexstar+ HC -> Dew Heater Controller, cmd DEWHEATER_GET_FW_VER: AUX packet <0x3b, 0x03, 0x0d, 0xbb, 0xfe, 0x37> (checksum 0x37)
[00547849ms,aux] Nexstar+ HC -> Dew Heater Controller, cmd DEWHEATER_GET_FW_VER: AUX packet <0x3b, 0x03, 0x0d, 0xbb, 0xfe, 0x37> (checksum 0x37)
[00548232ms,aux] Nexstar+ HC -> AZM MC, cmd MTR_SET_POSITION: AUX packet <0x3b, 0x06, 0x0d, 0x10, 0x04, (0x40 0x00 0x00), 0x99> (checksum 0x99)
[00548370ms,aux] AZM MC -> Nexstar+ HC, cmd MTR_SET_POSITION: AUX packet <0x3b, 0x03, 0x10, 0x0d, 0x04, 0xdc> (checksum 0xdc)
[00548527ms,aux] Nexstar+ HC -> ALT MC, cmd MTR_SET_POSITION: AUX packet <0x3b, 0x06, 0x0d, 0x11, 0x04, (0x40 0x00 0x00), 0x98> (checksum 0x98)
[00548665ms,aux] ALT MC -> Nexstar+ HC, cmd MTR_SET_POSITION: AUX packet <0x3b, 0x03, 0x11, 0x0d, 0x04, 0xdb> (checksum 0xdb)
[00548822ms,aux] Nexstar+ HC -> AZM MC, cmd MTR_SET_CORDWRAP_POSITION: AUX packet <0x3b, 0x06, 0x0d, 0x10, 0x3a, (0xc0 0x00 0x00), 0xe3> (checksum 0xe3)
[00548964ms,aux] AZM MC -> Nexstar+ HC, cmd MTR_SET_CORDWRAP_POSITION: AUX packet <0x3b, 0x03, 0x10, 0x0d, 0x3a, 0xa6> (checksum 0xa6)
[00549097ms,aux] Nexstar+ HC -> AZM MC, cmd MTR_CORDWRAP_ON: AUX packet <0x3b, 0x03, 0x0d, 0x10, 0x38, 0xa8> (checksum 0xa8)
[00549224ms,aux] AZM MC -> Nexstar+ HC, cmd MTR_CORDWRAP_ON: AUX packet <0x3b, 0x03, 0x10, 0x0d, 0x38, 0xa8> (checksum 0xa8)
[00549381ms,aux] Nexstar+ HC -> ALT MC, cmd MTR_SET_CORDWRAP_POSITION: AUX packet <0x3b, 0x06, 0x0d, 0x11, 0x3a, (0xc0 0x00 0x00), 0xe2> (checksum 0xe2)
[00549523ms,aux] ALT MC -> Nexstar+ HC, cmd MTR_SET_CORDWRAP_POSITION: AUX packet <0x3b, 0x03, 0x11, 0x0d, 0x3a, 0xa5> (checksum 0xa5)
[00549656ms,aux] Nexstar+ HC -> ALT MC, cmd MTR_CORDWRAP_ON: AUX packet <0x3b, 0x03, 0x0d, 0x11, 0x38, 0xa7> (checksum 0xa7)
[00549783ms,aux] ALT MC -> Nexstar+ HC, cmd MTR_CORDWRAP_ON: AUX packet <0x3b, 0x03, 0x11, 0x0d, 0x38, 0xa7> (checksum 0xa7)
[00616314ms,aux] Nexstar+ HC -> AZM MC, cmd MTR_SET_POSITION: AUX packet <0x3b, 0x06, 0x0d, 0x10, 0x04, (0x40 0x00 0x00), 0x99> (checksum 0x99)
[00616451ms,aux] AZM MC -> Nexstar+ HC, cmd MTR_SET_POSITION: AUX packet <0x3b, 0x03, 0x10, 0x0d, 0x04, 0xdc> (checksum 0xdc)
[00616609ms,aux] Nexstar+ HC -> ALT MC, cmd MTR_SET_POSITION: AUX packet <0x3b, 0x06, 0x0d, 0x11, 0x04, (0x40 0x00 0x00), 0x98> (checksum 0x98)
[00616746ms,aux] ALT MC -> Nexstar+ HC, cmd MTR_SET_POSITION: AUX packet <0x3b, 0x03, 0x11, 0x0d, 0x04, 0xdb> (checksum 0xdb)
[00616904ms,aux] Nexstar+ HC -> AZM MC, cmd MTR_SET_CORDWRAP_POSITION: AUX packet <0x3b, 0x06, 0x0d, 0x10, 0x3a, (0xc0 0x00 0x00), 0xe3> (checksum 0xe3)
[00617046ms,aux] AZM MC -> Nexstar+ HC, cmd MTR_SET_CORDWRAP_POSITION: AUX packet <0x3b, 0x03, 0x10, 0x0d, 0x3a, 0xa6> (checksum 0xa6)
[00617178ms,aux] Nexstar+ HC -> AZM MC, cmd MTR_CORDWRAP_ON: AUX packet <0x3b, 0x03, 0x0d, 0x10, 0x38, 0xa8> (checksum 0xa8)
[00617306ms,aux] AZM MC -> Nexstar+ HC, cmd MTR_CORDWRAP_ON: AUX packet <0x3b, 0x03, 0x10, 0x0d, 0x38, 0xa8> (checksum 0xa8)
[00617463ms,aux] Nexstar+ HC -> ALT MC, cmd MTR_SET_CORDWRAP_POSITION: AUX packet <0x3b, 0x06, 0x0d, 0x11, 0x3a, (0xc0 0x00 0x00), 0xe2> (checksum 0xe2)
[00617605ms,aux] ALT MC -> Nexstar+ HC, cmd MTR_SET_CORDWRAP_POSITION: AUX packet <0x3b, 0x03, 0x11, 0x0d, 0x3a, 0xa5> (checksum 0xa5)
[00617737ms,aux] Nexstar+ HC -> ALT MC, cmd MTR_CORDWRAP_ON: AUX packet <0x3b, 0x03, 0x0d, 0x11, 0x38, 0xa7> (checksum 0xa7)
[00617864ms,aux] ALT MC -> Nexstar+ HC, cmd MTR_CORDWRAP_ON: AUX packet <0x3b, 0x03, 0x11, 0x0d, 0x38, 0xa7> (checksum 0xa7)
[00618021ms,aux] Nexstar+ HC -> AZM MC, cmd MTR_PTRACK: AUX packet <0x3b, 0x06, 0x0d, 0x10, 0x06, (0x00 0x00 0x00), 0xd7> (checksum 0xd7)
[00618156ms,aux] AZM MC -> Nexstar+ HC, cmd MTR_PTRACK: AUX packet <0x3b, 0x03, 0x10, 0x0d, 0x06, 0xda> (checksum 0xda)
[00618310ms,aux] Nexstar+ HC -> ALT MC, cmd MTR_PTRACK: AUX packet <0x3b, 0x06, 0x0d, 0x11, 0x06, (0x00 0x00 0x00), 0xd6> (checksum 0xd6)
[00618444ms,aux] ALT MC -> Nexstar+ HC, cmd MTR_PTRACK: AUX packet <0x3b, 0x03, 0x11, 0x0d, 0x06, 0xd9> (checksum 0xd9)
[00618589ms,aux] Nexstar+ HC -> AZM MC, cmd MTR_PTRACK: AUX packet <0x3b, 0x05, 0x0d, 0x10, 0x06, (0xff 0xff), 0xda> (checksum 0xda)
[00618720ms,aux] AZM MC -> Nexstar+ HC, cmd MTR_PTRACK: AUX packet <0x3b, 0x03, 0x10, 0x0d, 0x06, 0xda> (checksum 0xda)
```

The communication between [INDI Celestron AUX driver](https://github.com/indilib/indi-3rdparty/tree/master/indi-celestronaux) and the USB ⇆ AUX relay looks as follows:
```
[00123927ms,usb] INDI Celestron AUX -> AZM MC, cmd MTR_GET_VERSION: AUX packet <0x3b, 0x03, 0x20, 0x10, 0xfe, 0xcf> (checksum 0xcf)
[00124099ms,aux] AZM MC -> INDI Celestron AUX, cmd NXS_GET_FW_VER: AUX packet <0x3b, 0x07, 0x10, 0x20, 0xfe, (0x07 0x0f 0x20 0x4e), 0x47> (checksum 0x47)
[00124203ms,usb] INDI Celestron AUX -> ALT MC, cmd MTR_GET_VERSION: AUX packet <0x3b, 0x03, 0x20, 0x11, 0xfe, 0xce> (checksum 0xce)
[00124374ms,aux] ALT MC -> INDI Celestron AUX, cmd NXS_GET_FW_VER: AUX packet <0x3b, 0x07, 0x11, 0x20, 0xfe, (0x07 0x0f 0x20 0x4e), 0x46> (checksum 0x46)
[00124478ms,usb] INDI Celestron AUX -> AZM MC, cmd MTR_GET_AUTOGUIDE_RATE: AUX packet <0x3b, 0x03, 0x20, 0x10, 0x47, 0x86> (checksum 0x86)
[00124623ms,aux] AZM MC -> INDI Celestron AUX, cmd MTR_GET_AUTOGUIDE_RATE: AUX packet <0x3b, 0x04, 0x10, 0x20, 0x47, (0x33), 0x52> (checksum 0x52)
[00124723ms,usb] INDI Celestron AUX -> ALT MC, cmd MTR_GET_AUTOGUIDE_RATE: AUX packet <0x3b, 0x03, 0x20, 0x11, 0x47, 0x85> (checksum 0x85)
[00124868ms,aux] ALT MC -> INDI Celestron AUX, cmd MTR_GET_AUTOGUIDE_RATE: AUX packet <0x3b, 0x04, 0x11, 0x20, 0x47, (0xcc), 0xb8> (checksum 0xb8)
[00124969ms,usb] INDI Celestron AUX -> AZM MC, cmd MTR_IS_CORDWRAP_ON: AUX packet <0x3b, 0x03, 0x20, 0x10, 0x3b, 0x92> (checksum 0x92)
[00125112ms,aux] AZM MC -> INDI Celestron AUX, cmd MTR_IS_CORDWRAP_ON: AUX packet <0x3b, 0x04, 0x10, 0x20, 0x3b, (0x00), 0x91> (checksum 0x91)
[00125210ms,usb] INDI Celestron AUX -> AZM MC, cmd MTR_GET_CORDWRAP_POSITION: AUX packet <0x3b, 0x03, 0x20, 0x10, 0x3c, 0x91> (checksum 0x91)
[00125376ms,aux] AZM MC -> INDI Celestron AUX, cmd MTR_GET_CORDWRAP_POSITION: AUX packet <0x3b, 0x06, 0x10, 0x20, 0x3c, (0x00 0x00 0x00), 0x8e> (checksum 0x8e)
[00125484ms,usb] INDI Celestron AUX -> AZM MC, cmd MTR_GET_MODEL: AUX packet <0x3b, 0x03, 0x20, 0x10, 0x05, 0xc8> (checksum 0xc8)
[00125634ms,aux] AZM MC -> INDI Celestron AUX, cmd MTR_GET_MODEL: AUX packet <0x3b, 0x05, 0x10, 0x20, 0x05, (0x14 0x85), 0x2d> (checksum 0x2d)
[00125732ms,usb] INDI Celestron AUX -> Main Board, cmd MB_GET_FW_VER: AUX packet <0x3b, 0x03, 0x20, 0x01, 0xfe, 0xde> (checksum 0xde)
[00126828ms,usb] INDI Celestron AUX -> Nexstar HC, cmd NXS_GET_FW_VER: AUX packet <0x3b, 0x03, 0x20, 0x04, 0xfe, 0xdb> (checksum 0xdb)
[00127924ms,usb] INDI Celestron AUX -> Nexstar+ HC, cmd NXS_GET_FW_VER: AUX packet <0x3b, 0x03, 0x20, 0x0d, 0xfe, 0xd2> (checksum 0xd2)
[00129021ms,usb] INDI Celestron AUX -> AZM MC, cmd MTR_GET_VERSION: AUX packet <0x3b, 0x03, 0x20, 0x10, 0xfe, 0xcf> (checksum 0xcf)
[00129193ms,aux] AZM MC -> INDI Celestron AUX, cmd NXS_GET_FW_VER: AUX packet <0x3b, 0x07, 0x10, 0x20, 0xfe, (0x07 0x0f 0x20 0x4e), 0x47> (checksum 0x47)
[00129297ms,usb] INDI Celestron AUX -> ALT MC, cmd MTR_GET_VERSION: AUX packet <0x3b, 0x03, 0x20, 0x11, 0xfe, 0xce> (checksum 0xce)
[00129468ms,aux] ALT MC -> INDI Celestron AUX, cmd NXS_GET_FW_VER: AUX packet <0x3b, 0x07, 0x11, 0x20, 0xfe, (0x07 0x0f 0x20 0x4e), 0x46> (checksum 0x46)
[00129572ms,usb] INDI Celestron AUX -> GPS, cmd GPS_GET_FW_VER: AUX packet <0x3b, 0x03, 0x20, 0xb0, 0xfe, 0x2f> (checksum 0x2f)
[00130665ms,usb] INDI Celestron AUX -> Nexstar EVO WiFi, cmd WIFI_GET_FW_VER: AUX packet <0x3b, 0x03, 0x20, 0xb5, 0xfe, 0x2a> (checksum 0x2a)
[00131765ms,usb] INDI Celestron AUX -> Battery Power Cont, cmd BAT_GET_FW_VER: AUX packet <0x3b, 0x03, 0x20, 0xb6, 0xfe, 0x29> (checksum 0x29)
[00132867ms,usb] INDI Celestron AUX -> AZM MC, cmd MTR_GET_POSITION: AUX packet <0x3b, 0x03, 0x20, 0x10, 0x01, 0xcc> (checksum 0xcc)
[00133030ms,aux] AZM MC -> INDI Celestron AUX, cmd MTR_GET_POSITION: AUX packet <0x3b, 0x06, 0x10, 0x20, 0x01, (0xff 0xff 0xff), 0xcc> (checksum 0xcc)
[00133132ms,usb] INDI Celestron AUX -> ALT MC, cmd MTR_GET_POSITION: AUX packet <0x3b, 0x03, 0x20, 0x11, 0x01, 0xcb> (checksum 0xcb)
[00133294ms,aux] ALT MC -> INDI Celestron AUX, cmd MTR_GET_POSITION: AUX packet <0x3b, 0x06, 0x11, 0x20, 0x01, (0x00 0x00 0x00), 0xc8> (checksum 0xc8)
[00133397ms,usb] INDI Celestron AUX -> ALT MC, cmd MTR_AUX_GUIDE: AUX packet <0x3b, 0x05, 0x20, 0x11, 0x26, (0x50 0x14), 0x40> (checksum 0x40)
[00133534ms,aux] ALT MC -> INDI Celestron AUX, cmd MTR_AUX_GUIDE: AUX packet <0x3b, 0x03, 0x11, 0x20, 0x26, 0xa6> (checksum 0xa6)
[00134399ms,usb] INDI Celestron AUX -> AZM MC, cmd MTR_GET_POSITION: AUX packet <0x3b, 0x03, 0x20, 0x10, 0x01, 0xcc> (checksum 0xcc)
```
