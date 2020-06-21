#pragma once

#include "StbippSymbols.h"


namespace stbipp {

enum class ImageFormat
{
    //Luminance
    LUM8,
    LUM16,
    LUM32,// Float Luminance
    // 2 Components per pixel
    LUMA8,
    LUMA16,
    LUMA32,// Float RG
    // 3 Components per pixel
    RGB8,
    RGB16,
    RGB32,// Float RGB
    //4 Components per pixel
    RGBA8,
    RGBA16,
    RGBA32,// Float RGBA

    UNDEFINED = -1
};



STBIPP_API bool isFormat8Bits(const ImageFormat& format);

STBIPP_API bool isFormat16Bits(const ImageFormat& format);

STBIPP_API bool isFormat32Bits(const ImageFormat& format);

STBIPP_API int formatChannelCount(const ImageFormat& format);

}
