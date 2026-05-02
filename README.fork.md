# VAIL SUMMIT — K5GRR Fork

A fork of [Vail-CW/vail-summit](https://github.com/Vail-CW/vail-summit) by K5GRR with UI fixes, decoder improvements, and a browser-based flasher.

## Web Flasher

Flash the latest K5GRR build straight from your browser — no Arduino IDE, no drivers:

**https://catriname.github.io/vail-summit-k5grr/**

Chrome, Edge, or Opera on desktop required (Web Serial).

## What's different in this fork

- **Direct Decoder is the default** for new installs (see callout below).
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

## Building locally

See upstream [README.md](README.md) and `build.ps1` / `build.bat`. The web flasher is built automatically by GitHub Actions on every push to `fork-main`.

## Upstream

This fork tracks `Vail-CW/vail-summit`. For the original project, documentation, and broader community, go upstream.
