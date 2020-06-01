#pragma once
#include "stbipp/Image.hpp"
#include "stbipp/TypeTraits.hpp"

#include "StbippSymbols.h"

#include <string>

namespace stbipp {

template <ImageFormat pixelFormat = ImageFormat::RGBA8>
Image<pixelFormat> loadImage(const std::string& path);

STBIPP_API unsigned char* loadUCharImage(const std::string& path, int& width, int& height,
        const stbipp::ImageFormat& format);
STBIPP_API unsigned short* loadUShortImage(const std::string& path, int& width, int& height,
        const stbipp::ImageFormat& format);
STBIPP_API float* loadFloatImage(const std::string& path, int& width, int& height,
                                 const stbipp::ImageFormat& format);


STBIPP_API void freeStbData(void* data);

}



namespace {

template <class PixelType>
PixelType* loadRawImage(const std::string& path, int& width, int& height,
                        const stbipp::ImageFormat& format);

template <>
float* loadRawImage<float>(const std::string& path, int& width, int& height,
                           const stbipp::ImageFormat& format)
{
    return stbipp::loadFloatImage(path, width, height, format);
}

template <>
unsigned char* loadRawImage<unsigned char>(const std::string& path, int& width,
        int& height,
        const stbipp::ImageFormat& format)
{
    return stbipp::loadUCharImage(path, width, height, format);
}


template <>
unsigned short* loadRawImage<unsigned short>(const std::string& path, int& width,
        int& height,
        const stbipp::ImageFormat& format)
{
    return stbipp::loadUShortImage(path, width, height, format);
}

}

namespace stbipp {

template <ImageFormat pixelFormat>
Image<pixelFormat> loadImage(const std::string& path, bool& success)
{
    int width{};
    int height{};
    auto data = ::loadRawImage<PixelTypeTrait_t<pixelFormat>>(path, width, height, pixelFormat);
    success = data != nullptr;
    auto image = Image<pixelFormat>(data, width, height);
    freeStbData(data);
    return image;
}

}
