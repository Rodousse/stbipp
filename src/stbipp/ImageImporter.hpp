#pragma once
#include "stbipp/Image.hpp"
#include "stbipp/TypeTraits.hpp"

#include "StbippSymbols.h"

#include <string>

namespace stbipp {

template <stbipp::ImageFormat pixelFormat>
stbipp::Image<PixelTypeTrait_t<pixelFormat>> loadImage(
        const std::string& path);

STBIPP_API unsigned char* loadUCharImage(const std::string& path, int& width, int& height,
        const stbipp::ImageFormat& format);
STBIPP_API unsigned short* loadUShortImage(const std::string& path, int& width, int& height,
        const stbipp::ImageFormat& format);
STBIPP_API float* loadFloatImage(const std::string& path, int& width, int& height,
                                 const stbipp::ImageFormat& format);

}



namespace {

template <class PixelType>
stbipp::Image<PixelType> loadImage(const std::string& path,
                                   const stbipp::ImageFormat& format);

template <>
stbipp::Image<float> loadImage<float>(const std::string& path, const stbipp::ImageFormat& format)
{
    int width;
    int height;
    float* data = stbipp::loadFloatImage(path, width, height, format);

    stbipp::Image<float> image(data, width, height, format);
    return image;
}

template <>
stbipp::Image<unsigned char> loadImage<unsigned char>(const std::string& path,
        const stbipp::ImageFormat& format)
{
    int width;
    int height;
    unsigned char* data = stbipp::loadUCharImage(path, width, height, format);
    stbipp::Image<unsigned char> image(data, width, height, format);
    return image;
}


template <>
stbipp::Image<unsigned short> loadImage<unsigned short>(const std::string& path,
        const stbipp::ImageFormat& format)
{
    int width;
    int height;
    unsigned short* data = stbipp::loadUShortImage(path, width, height, format);

    stbipp::Image<unsigned short> image(data, width, height, format);
    return image;
}

}

namespace stbipp {

template <stbipp::ImageFormat pixelFormat>
stbipp::Image<PixelTypeTrait_t<pixelFormat>> loadImage(
        const std::string& path)
{
    return ::loadImage<PixelTypeTrait_t<pixelFormat>>(path, pixelFormat);
}

}
