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


    Image() = default;

    Image(int width, int height):
        m_format(pixelFormat)
    {
        resizeData(width, height);
    }


    Image(PixelDataType* data, int width, int height):
        Image(width, height)
    {
        std::size_t rowIndex{0};
        for(auto& rowData : m_data)
        {
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
        Image(other.width(), other.height())
    {
        copyData(other);
    };

    Image(const Image& other):
        Image(other.width, other.height),
        m_data(other.m_data)
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
        return m_data[0][0].data();
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

    PixelType operator()(std::size_t column, std::size_t row) const
    {
        return m_data[row][column];
    }

    PixelType& operator()(std::size_t column, std::size_t row)
    {
        return m_data[row][column];
    }

    template<ImageFormat otherPixelDataFormat>
    Image& operator=(const Image<otherPixelDataFormat>& other)
    {
        resizeData(other.width(), other.height());
        copyData(other);
        return *this;
    }

    template<ImageFormat newPixelDataFormat>
    Image castTo()
    {
        return Image<newPixelDataFormat>(*this);
    }

private:

    template<ImageFormat otherPixelDataFormat>
    void copyData(const Image<otherPixelDataFormat>& other)
    {
        std::size_t rowIndex{0};
        for(auto& rowData : m_data)
        {
            std::size_t columnIndex{0};
            for(auto& pixel : rowData)
            {
                m_data[rowIndex][columnIndex] = static_cast<PixelType>(other(columnIndex, rowIndex));
                ++columnIndex;
            }
            ++rowIndex;
        }
    }

    void resizeData(int width, int height)
    {
        m_height = height;
        m_width = width;
        m_data.resize(height);
        for(auto& row : m_data)
        {
            row.resize(width);
        }
    }

    std::vector<std::vector<PixelType>> m_data;
    int m_width;
    int m_height;
    ImageFormat m_format;

};


STBIPP_API bool isFormat8Bits(const ImageFormat& format);

STBIPP_API bool isFormat16Bits(const ImageFormat& format);

STBIPP_API bool isFormat32Bits(const ImageFormat& format);


}



