#include "stbipp/Image.hpp"

namespace stbipp {


bool isFormat8Bits(const ImageFormat& format)
{
    if(format == ImageFormat::LUM8
       || format == ImageFormat::LUMA8
       || format == ImageFormat::RGB8
       || format == ImageFormat::RGBA8)
    {
        return true;
    }

    return false;
}

bool isFormat16Bits(const ImageFormat& format)
{
    if(format == ImageFormat::LUM16
       || format == ImageFormat::LUMA16
       || format == ImageFormat::RGB16
       || format == ImageFormat::RGBA16)
    {
        return true;
    }

    return false;
}

bool isFormat32Bits(const ImageFormat& format)
{
    if(format == ImageFormat::LUM32
       || format == ImageFormat::LUMA32
       || format == ImageFormat::RGB32
       || format == ImageFormat::RGBA32)
    {
        return true;
    }

    return false;
}

}


