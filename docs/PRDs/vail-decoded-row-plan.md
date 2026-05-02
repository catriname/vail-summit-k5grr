# Vail Repeater — RX Decoded Morse Row Plan

## Goal
Add a third row above the TX morse row in the Vail chat view that shows
**incoming** morse as dits/dahs (grey, same look as the TX morse row).
Settings toggle to hide it.

## What the Vail server provides
The Vail JSON message contains:
- `Duration[]` — alternating tone/silence ms (even index = key-down ms,
  odd index = key-up ms). **This *is* the morse**, just as raw timing.
- `TxTone` — sender's audio frequency as a MIDI note number (default 69
  = A4 = 440 Hz). Not morse content.
- `Timestamp`, `Callsign`, `Clients`, `Users`/`UsersInfo`, `Rooms`,
  optional `Text` (chat).

The server does **not** ship a dits/dahs string or decoded text. We
synthesize dits/dahs on-device from `Duration[]`.

## Approach
Mirror the TX-side trick from `vailKeyerCallback` (vail_repeater.h:783):

```cpp
vailTxMorseSymbols += (toneDuration <= ditMs * 2.0f) ? "." : "-";
```

For each tone element advanced in `playbackMessages()`, append `.` or
`-`. For silence elements, classify by length:
- silence ≤ ~2× dit → intra-character gap → just append a space
- silence ≤ ~5× dit → letter gap → append ` /`
- silence > ~5× dit → word gap → append ` //`

Standard CW thresholds (1-unit element gap, 3-unit letter gap, 7-unit
word gap) — at cwSpeed dit ≈ 1200/wpm ms.

**No need to run vailRxDecoder for this visualization** — direct timing
classification is enough and matches the TX row's look.

## Existing infra to reuse
- `vailShowDecoded` (vail_repeater.h:40) already exists and is persisted
  in NVS via `vailPrefs` (lines 51, 62). Currently used to gate feeding
  vailRxDecoder during playback (lines 952, 963). We'll repurpose it to
  also mean "show the decoded row" (or rename — see Open Questions).
- `vailShowMorseRow` (line 41) toggles the TX morse row, with a settings
  UI in lv_mode_screens.h at row index 4 (lines 1679, 1714, 1736, 1845,
  2673). Use as the template for the new toggle.
- TX row rendering pattern in lv_mode_screens.h:2663–2679 — copy/paste
  template for the decoded row.

## Implementation

### 1. Data layer (vail_repeater.h)
- Add `String vailRxMorseSymbols = "";` next to `vailTxMorseSymbols`
  (around line 130).
- In `playbackMessages()` where the playback advances to a new element
  (around lines 949–967), append to `vailRxMorseSymbols`:
  - On tone (even index): compare `elemDur` to `ditMs = 1200.0f /
    cwSpeed`, append `.` if `elemDur <= ditMs * 2.0f` else `-`. Add a
    leading space if symbols already has content (mirror line 784).
  - On silence (odd index): append ` /` if `elemDur >= ditMs * 2.0f`
    (letter gap) and promote to ` //` if `elemDur >= ditMs * 5.0f`
    (word gap). Skip the intra-char gap (≤ 2× dit) since it's the
    default spacing.
- Trim length when too long, mirror lines 786–790.
- Reset `vailRxMorseSymbols = ""` on disconnect / room change (search
  for places `vailTxMorseSymbols` is reset, do the same).

### 2. UI (lv_mode_screens.h, around 2647–2698)
- Add static handles:
  ```cpp
  static lv_obj_t* vail_decoded_row_bg = NULL;
  static lv_obj_t* vail_decoded_row_label = NULL;
  ```
- Recompute layout (chat panel section ~line 2647):
  ```cpp
  int chat_header_h   = 20;
  int input_row_h     = 38;
  int morse_row_h     = input_row_h;
  int decoded_row_h   = input_row_h;  // same as morse row
  int gap             = 2;
  int rows_h          = decoded_row_h + morse_row_h + input_row_h + gap*3;
  int history_h       = content_height - chat_header_h - rows_h - 6;
  ```
- Lay out top-to-bottom:
  ```
  [history] [decoded row] [morse row] [input row]
  ```
- Decoded row mirrors morse row: same size, same `font_special_elite_18`,
  text color `LV_COLOR_TEXT_SECONDARY` (grey) instead of accent.
- Hide on init: `if (!vailShowDecoded) lv_obj_add_flag(vail_decoded_row_bg, LV_OBJ_FLAG_HIDDEN);`
- Live update: where `vail_morse_row_label` is updated (search for
  `vail_morse_row_label` in updateVailScreenLVGL, around line 2917),
  add a parallel update setting `vail_decoded_row_label` text to
  `vailRxMorseSymbols`.

### 3. Settings UI (lv_mode_screens.h)
- Find the settings rows array and dialog. The current "Show Morse Row"
  toggle lives at row index 4 (cases at lines 1679, 1714, 1736, 1845).
  Add a new row "Show Decoded" — copy the morse-row case, swap variable
  to `vailShowDecoded`, swap target object to `vail_decoded_row_bg`.
- On toggle, also persist via `vailPrefs.putBool("showDecoded", ...)`
  (already wired at line 62 — just call the existing save function).

### 4. Layout-on-toggle
- **Phase 1 (recommended)**: leave the gap when the row is hidden (no
  reflow). Trivial, zero risk.
- **Phase 2 (optional)**: recompute row Y positions and history height
  when toggled. ~15 lines, do later if Phase 1 looks bad.

## Open questions
1. **Naming**: `vailShowDecoded` currently gates *feeding* vailRxDecoder.
   With the new approach, we don't need vailRxDecoder for this row —
   timing classification is enough. Options:
   - (a) Repurpose `vailShowDecoded` to gate the new row, drop the
     decoder feeding in playbackMessages (it had no UI consumer anyway
     unless `vailDecodedEntries` is shown elsewhere — check first).
   - (b) Add a new flag `vailShowDecodedRow` and leave `vailShowDecoded`
     alone.
   - Recommend (a) — simpler — but verify `vailDecodedEntries` isn't
     consumed anywhere visible before removing the decoder feeding.
2. **Self-echo behavior**: Echo filter (line 620–629) drops own
   transmissions before they reach playbackMessages. So the decoded row
   will only show *other people's* morse. Confirm that's desired (likely
   yes — symmetric with the TX morse row).
3. **Color**: `LV_COLOR_TEXT_SECONDARY` for grey, vs. a custom dimmer
   grey. User said "maybe in grey" — start with `LV_COLOR_TEXT_SECONDARY`.

## Files touched
- `src/network/vail_repeater.h` — accumulator, append logic, reset hooks.
- `src/lvgl/lv_mode_screens.h` — UI row, layout, settings toggle, live
  update.

## Status
- Plan drafted. Implementation not yet started.
- Last related commit: `c598cad` (sidetone Core 0 reapplied).
- Branch: `directDecoder-uiFixes`.
