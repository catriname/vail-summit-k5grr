#ifndef MORSE_DECODER_DIRECT_H
#define MORSE_DECODER_DIRECT_H

#include "morse_decoder_adaptive.h"

// Direct decoder backend is pending redesign.
// Currently an alias for MorseDecoderAdaptive so the settings
// infrastructure compiles while the backend is being reworked.
using MorseDecoderDirect = MorseDecoderAdaptive;

#endif // MORSE_DECODER_DIRECT_H
