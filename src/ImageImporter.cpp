#define STB_IMAGE_IMPLEMENTATION

#include "stbipp/ImageImporter.hpp"

#include <stb_image.h>

#include <iostream>
#include <exception>
#include <string>
namespace {



int deduceSTBIType(const stbipp::ImageFormat& format)
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

}



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

void freeStbData(void* data)
{
    if(data)
    {
        stbi_image_free(data);
    }
}

}

namespace stbipp {

Image loadImage(const std::string& path, const ImageFormat pixelFormat, bool& success)
{
    int width{};
    int height{};
    void* data{nullptr};
    success = false;
    if(isFormat8Bits(pixelFormat))
    {
        data = loadUCharImage(path, width, height, pixelFormat);
    }
    else if(isFormat16Bits(pixelFormat))
    {
        data = loadUShortImage(path, width, height, pixelFormat);
    }
    else if(isFormat32Bits(pixelFormat))
    {
        data = loadFloatImage(path, width, height, pixelFormat);
    }
    success = data != nullptr;
    if(success)
    {
        Image image(data, static_cast<unsigned int>(width), static_cast<unsigned int>(height),
                    pixelFormat);
        freeStbData(data);
        return image;
    }
    else
    {
        return Image();
    }

}

}
