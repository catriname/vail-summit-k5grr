# Build Environment Setup Notes

This document covers the build environment configuration for this fork.
Library versions are pinned to match upstream exactly (see upstream DEVELOPMENT.md).

## Pinned Library Versions

Most versions match upstream exactly. Exceptions are noted below the table.

| Library | Version |
|---------|---------|
| ESP32 Core | 2.0.14 |
| LovyanGFX | 1.1.16 |
| LVGL | 8.3.11 |
| NimBLE-Arduino | 1.4.2 |
| ArduinoJson | 7.4.3 |
| ESP Async WebServer | 3.6.0 |

**ArduinoJson divergence:** Upstream pins 7.0.4, but this fork requires 7.4.3.
ArduinoJson 7.0.4 uses double-precision floats that overflow the Xtensa `l32r`
literal range on large sketches. This fork's additional features push the binary
past the threshold where 7.0.4 triggers a linker error. 7.4.3 resolves this
internally and is otherwise API-compatible.

Install or reinstall any library with:
```
C:\acli\arduino-cli.exe lib install "LibraryName@version" --config-file C:\acli\arduino-cli.yaml
```

## lv_conf.h Placement

LVGL 8.3.x looks for `lv_conf.h` two levels up from its source directory.
With the library installed at `C:\acli\user\libraries\lvgl\`, the correct placement is:

```
C:\acli\user\libraries\lv_conf.h
```

After any changes to `lv_conf.h`, re-copy it to that location before building.

## Uploading

The build script upload command requires the Bluetooth virtual COM ports to be
**enabled** in Device Manager. Disabling them causes esptool to fail to open the
port even though the device is present.

To enter bootloader mode for upload:
1. Hold **BOOT** button
2. Press and release **RESET**
3. Release **BOOT**
4. Run `.\build.bat upload COMXX` immediately
