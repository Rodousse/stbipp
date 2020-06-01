#pragma once


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

}
