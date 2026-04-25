# Build Environment Setup Notes

This document covers required library versions and configuration changes discovered during build troubleshooting. These are not obvious from the standard BUILDING.md instructions.

## Library Versions

### LovyanGFX — must be 1.2.19

**Do not use 1.2.20 or newer.**

LovyanGFX 1.2.20 (released April 2026) added `src/lvgl.h` and `src/lgfx/v1/lvgl.h`, which intercept `#include <lvgl.h>` and silently substitute LVGL 9.3.0 in place of the standalone LVGL library. This causes the build to fail with LVGL 8 API errors (`lv_disp_drv_t`, `lv_color_t`, etc. not declared).

Install the correct version:
```
arduino-cli\arduino-cli.exe lib install "LovyanGFX@1.2.19" --config-file arduino-cli\arduino-cli.yaml
```

### LVGL — 8.3.11

Install via Arduino Library Manager or CLI. LVGL 9.x has breaking API changes and will not compile.

```
arduino-cli\arduino-cli.exe lib install "lvgl@8.3.11" --config-file arduino-cli\arduino-cli.yaml
```

## lv_conf.h Placement

LVGL 8.3.x looks for `lv_conf.h` two levels up from its source directory. With the library installed at `C:\acli\user\libraries\lvgl\`, the correct placement is:

```
C:\acli\user\libraries\lv_conf.h
```

After any changes to `lv_conf.h`, re-copy it to that location before building.

## lv_conf.h Font Settings

The project `lv_conf.h` originally had all Montserrat fonts set to `0`, with comments noting they were "provided by LovyanGFX". With LovyanGFX 1.2.19 (which does not provide fonts), these must be enabled directly.

The following must be set to `1`:

```c
#define LV_FONT_MONTSERRAT_12 1
#define LV_FONT_MONTSERRAT_14 1
#define LV_FONT_MONTSERRAT_16 1
#define LV_FONT_MONTSERRAT_18 1
#define LV_FONT_MONTSERRAT_20 1
#define LV_FONT_MONTSERRAT_24 1
#define LV_FONT_MONTSERRAT_28 1
```

These are already set correctly in the project's `lv_conf.h`. Just ensure the file has been copied to `C:\acli\user\libraries\lv_conf.h` as described above.

## Uploading

The build script upload command requires the Bluetooth virtual COM ports to be **enabled** in Device Manager. Disabling them causes esptool to fail to open the port even though the device is present.

To enter bootloader mode for upload:
1. Hold **BOOT** button
2. Press and release **RESET**
3. Release **BOOT**
4. Run `.\build.bat upload COMXX` immediately
