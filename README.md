# VAIL SUMMIT — K5GRR Fork

A fork of [Vail-CW/vail-summit](https://github.com/Vail-CW/vail-summit) by K5GRR with UI fixes, decoder improvements, and a browser-based flasher.

## Web Flasher

Flash the latest K5GRR build straight from your browser — no Arduino IDE, no drivers:

**https://catriname.github.io/vail-summit-k5grr/**

Chrome, Edge, or Opera on desktop required (Web Serial).

## What's different in this fork
|  Direct Decoder |
| ------------ |
|  This fork uses a completely different decoder.  All testing is done with this decoder, adaptive not tested yet.  If not already set, go to Settings and verify it is set to Direct.  Adjust WPM if accuracy or rythm is a bit off. |

- **Vail repeater chat** sends as morse audio with an RX decoded row above the TX morse row.
- **Sidetone audio** driven from Core 0 to eliminate underrun static.
- **CW School** UI cleanup: dot status indicators, focus-handling fixes, completed-lesson styling.
- **Alert dialogs** are now truly modal — events stop at the backdrop.
- **POTA recorder** drops the on-screen keyboard (the device has a physical one).
- **Lesson button focus styling** unified across screens.
- Many smaller theme/color cleanups: non-semantic color macros replaced with semantic theme names throughout.

## Notes for v0.1.0

- **Default to Direct Decoder** in settings if you haven't already.
- **Adaptive mode** is largely untested in this build.
- **Exit out of repeater** and return to go online — bug being worked on.
- Edits are ongoing — please file issues for anything you hit.

## Notes for v0.2.0

- **Custom Font Awesome icons (LVGL 8.3)** for many menu rows: a bitmap subset is embedded as `ExtraFontAwesomeIcons` (see `docs/EXTRA_FONT_AWESOME_ICONS.md`). Ham Tools, Training, Games, and other entries use these icons where the UI shows them.
- **POTA UI**: tree for **POTA** in Ham Tools; **Active Spots** and **Activate a Park** on the POTA screen use the new map/route-style icons; **POTA Recorder** still uses the built-in audio symbol.
- **Build / Arduino**: the generated font fragment is `extra_font_awesome_icons_generated.h` (with a legacy `.inc` include fallback) so the sketch build can resolve the file reliably.
- **CW School**: label cleanup; **Space** to replay; auto progression between levels and overlay text fix; exit from the school flow (mode 153) fixed.
- **WiFi settings**: show/hide password works on the correct security tab.
- **Account**: “link account” entry removed temporarily (pending a later design).

## Building locally

See upstream [README.md](README.md) and `build.ps1` / `build.bat`. The web flasher is built automatically by GitHub Actions on every push to `fork-main`.

## Upstream

This fork tracks `Vail-CW/vail-summit`. For the original project, documentation, and broader community, go upstream.
