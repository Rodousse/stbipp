#pragma once

#include "StbippSymbols.h"

#include "stbipp/Color.hpp"
#include "stbipp/TypeTraits.hpp"

#include <vector>
#include <memory>


namespace stbipp {



template <ImageFormat pixelFormat = ImageFormat::RGBA8>
class Image
{
public:
    using PixelDataType = PixelTypeTrait_t<pixelFormat>;
    using PixelType = Color<PixelTypeTrait_t<pixelFormat>, PixelTypeTrait_s<pixelFormat>>;


    Image(PixelDataType* data, const int& width, const int& height):
        m_width(width),
        m_height(height),
        m_format(pixelFormat)
    {
        m_data.resize(height);
        std::size_t rowIndex{0};
        for(auto& rowData : m_data)
        {
            rowData.resize(width);
            std::size_t columnIndex{0};
            for(auto& pixel : rowData)
            {
                PixelType color{};
                for(std::size_t colorComponent = 0; colorComponent < color.size(); ++colorComponent)
                {
                    color[colorComponent] = *(data + width * rowIndex + columnIndex + colorComponent);
                }
                m_data[rowIndex][columnIndex] = color;
                ++columnIndex;
            }
            ++rowIndex;
        }
    }

    template<ImageFormat otherPixelDataFormat> Image(const Image<otherPixelDataFormat>& other):
        m_width(other.width()),
        m_height(other.height()),
        m_format(pixelFormat)
    {
        m_data.resize(other.height());
        std::size_t rowIndex{0};
        for(auto& rowData : m_data)
        {
            rowData.resize(other.width());
            std::size_t columnIndex{0};
            for(auto& pixel : rowData)
            {
                m_data[rowIndex][columnIndex] = static_cast<PixelType>(other(rowIndex, columnIndex));
                ++columnIndex;
            }
            ++rowIndex;
        }
    };

    Image(const Image& other):
        m_data(other.m_data),
        m_width(other.width()),
        m_height(other.height()),
        m_format(other.format())
    {
    }

    Image(Image&& other):
        m_width(other.width()),
        m_height(other.height()),
        m_format(other.format())
    {
        std::swap(m_data, other.m_data);
    }

    ~Image() = default;

    const PixelDataType* data() const
    {
        return m_data;
    }

    const ImageFormat& format() const
    {
        return m_format;
    }

    int height() const
    {
        return m_height;
    }

    int width() const
    {
        return m_width;
    }

    PixelType operator()(std::size_t row, std::size_t column) const
    {
        return m_data[row][column];
    }

    PixelType& operator()(std::size_t row, std::size_t column)
    {
        return m_data[row][column];
    }

private:

    std::vector<std::vector<PixelType>> m_data;
    int m_width;
    int m_height;
    ImageFormat m_format;

};


STBIPP_API bool isFormat8Bits(const ImageFormat& format);

STBIPP_API bool isFormat16Bits(const ImageFormat& format);

STBIPP_API bool isFormat32Bits(const ImageFormat& format);


}



