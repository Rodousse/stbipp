#pragma once

#include "StbippSymbols.h"

#include "stbipp/TypeTraits.hpp"

#include <memory>


namespace stbipp {

STBIPP_API void freeStbData(void* data);


template <ImageFormat pixelFormat>
class Image
{
public:
    using PixelDataType = PixelTypeTrait_t<pixelFormat>;


    Image(PixelDataType* data, const int& width, const int& height):
        m_data(data),
        m_width(width),
        m_height(height),
        m_format(pixelFormat)
    {
    }

    template<ImageFormat otherPixelDataFormat>
    Image(const Image<otherPixelDataFormat>& other) = delete;

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

    const PixelDataType* data() const
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

private:

    PixelDataType* m_data;
    int m_width;
    int m_height;
    ImageFormat m_format;

};


STBIPP_API bool isFormat8Bits(const ImageFormat& format);

STBIPP_API bool isFormat16Bits(const ImageFormat& format);

STBIPP_API bool isFormat32Bits(const ImageFormat& format);


}



