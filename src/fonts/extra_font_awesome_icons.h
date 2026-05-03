/*
 * UTF-8 macros for glyphs in extra_font_awesome_icons_* (LVGL 8.3.x only; not LVGL 9).
 * Regenerate bitmaps: paste into extra_font_awesome_icons_generated.inc — docs/EXTRA_FONT_AWESOME_ICONS.md
 * LVGL 8.3 font/symbol usage: https://docs.lvgl.io/8.3/overview/font.html
 *
 * Runtime: lv_label_set_text(label, FA_EXTRA_*); lv_obj_set_style_text_font(label, &ExtraFontAwesomeIcons, 0);
 * When you add/change a codepoint here, update the .inc from lv_font_conv and keep macros in sync.
 */

#ifndef EXTRA_FONT_AWESOME_ICONS_H
#define EXTRA_FONT_AWESOME_ICONS_H

#include <lvgl.h>

LV_FONT_DECLARE(ExtraFontAwesomeIcons);

/* U+F0AC — FA5 "globe" (Americas-style globe in older sets) */
#define FA_EXTRA_GLOBE "\xEF\x82\xAC"

/* U+F549 — school */
#define FA_EXTRA_SCHOOL "\xEF\x95\x89"

/* U+F501 — user-graduate */
#define FA_EXTRA_USER_GRADUATE "\xEF\x94\x81"

/* U+F19D — graduation-cap */
#define FA_EXTRA_GRADUATION_CAP "\xEF\x86\x9D"

/* U+F70E — scroll */
#define FA_EXTRA_SCROLL "\xEF\x9C\x8E"

/* U+F025 — microphone */
#define FA_EXTRA_MICROPHONE "\xEF\x80\xA5"

/* U+F2A2 — assistive-listening-systems */
#define FA_EXTRA_ASSISTIVE_LISTENING "\xEF\x8A\xA2"

/* U+F249 — sticky-note */
#define FA_EXTRA_STICKY_NOTE "\xEF\x89\x89"

/* U+F518 — book-open */
#define FA_EXTRA_BOOK_OPEN "\xEF\x94\x98"

/* U+F044 — edit */
#define FA_EXTRA_EDIT "\xEF\x81\x84"

/* U+F03D — video (LICW); cmap in extra_font_awesome_icons.c */
#define FA_EXTRA_VIDEO "\xEF\x80\xBD"

/* U+F086 — comments (speech bubbles) */
#define FA_EXTRA_COMMENTS "\xEF\x82\x86"

#endif /* EXTRA_FONT_AWESOME_ICONS_H */
