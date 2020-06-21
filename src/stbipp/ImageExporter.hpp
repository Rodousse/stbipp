#pragma once

#include "stbipp/Image.hpp"

#include <string>


namespace stbipp {

enum class ImageSaveFormat
{
    LUM,
    LUMA,
    RGB,
    RGBA
};

STBIPP_API bool saveImage(const std::string& path, const Image& image,
                          const ImageSaveFormat pixelFormat);


STBIPP_API int formatChannelCount(const ImageSaveFormat& format);

}


