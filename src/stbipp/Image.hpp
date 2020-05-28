#pragma once

#include "StbippSymbols.h"

#include <memory>


namespace stbipp {

STBIPP_API void freeStbData(void* data);

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

template <class PixelType>
class Image
{
    PixelType* m_data;
    int m_width;
    int m_height;
    ImageFormat m_format;


public:
    Image(PixelType* data, const int& width, const int& height, const ImageFormat& format):
        m_data(data),
        m_width(width),
        m_height(height),
        m_format(format)
    {
    }

    template<class otherPixelType>
    Image(const Image<otherPixelType>& other) = delete;

    Image(const Image& other):
        m_data(other.m_data),
        m_width(other.width()),
        m_height(other.height()),
        m_format(other.format())
    {
    }

    Image(Image&& other):
        m_data(other.m_data),
        m_width(other.width()),
        m_height(other.height()),
        m_format(other.format())
    {
        other.m_data = nullptr;
    }

    ~Image()
    {
        freeStbData(m_data);
    }

    const PixelType* data() const
    {
        return m_data;
    }

    const ImageFormat& format() const
    {
        return m_format;
    }

    const int& height() const
    {
        return m_height;
    }

    const int& width() const
    {
        return m_width;
    }

};

STBIPP_API bool isFormat8Bits(const ImageFormat& format);

STBIPP_API bool isFormat16Bits(const ImageFormat& format);

STBIPP_API bool isFormat32Bits(const ImageFormat& format);

}

