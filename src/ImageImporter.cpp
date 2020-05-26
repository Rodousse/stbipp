#include "stbipp/ImageImporter.hpp"

#include <stb_image.h>

#include <iostream>
#include <exception>
#include <string>
namespace {

constexpr int deduceSTBIType(const stbipp::ImageFormat& format)
{
    using stbipp::ImageFormat;

    switch(format)
    {
        case ImageFormat::LUM8:
        case ImageFormat::LUM16:
        case ImageFormat::LUM32:
            return STBI_grey;

        case ImageFormat::LUMA8:
        case ImageFormat::LUMA16:
        case ImageFormat::LUMA32:
            return STBI_grey_alpha;

        case ImageFormat::RGB8:
        case ImageFormat::RGB16:
        case ImageFormat::RGB32:
            return STBI_rgb;

        case ImageFormat::RGBA8:
        case ImageFormat::RGBA16:
        case ImageFormat::RGBA32:
            return STBI_rgb_alpha;

        default:
            throw std::invalid_argument("[" + std::string(__func__) +
                                        "] : Can't deduce STB Type from value ImageFormat ");
    }

    return -1;

}
}

namespace stbipp {

unsigned char* loadUCharImage(const std::string& path, int& width, int& height,
                              const stbipp::ImageFormat& format)
{
    int channels;
    return stbi_load(path.data(), &width, &height, &channels, deduceSTBIType(format));
}

unsigned short* loadUShortImage(const std::string& path, int& width, int& height,
                                const stbipp::ImageFormat& format)
{
    int channels;
    return stbi_load_16(path.data(), &width, &height, &channels,
                        deduceSTBIType(format));

}

float* loadFloatImage(const std::string& path, int& width, int& height,
                      const stbipp::ImageFormat& format)
{
    int channels;
    return stbi_loadf(path.data(), &width, &height, &channels, deduceSTBIType(format));
}

}
