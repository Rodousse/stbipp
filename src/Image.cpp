#include "stbipp/Image.hpp"

#include "stbipp/TypeTraits.hpp"

#include <exception>

namespace stbipp {

Image::Image(int width, int height)
{
    resizeData(width, height);
}

Image::Image(void* data, int width, int height, ImageFormat pixelFormat):
    Image(width, height)
{
    if(isFormat8Bits(pixelFormat))
    {
        auto* ucdata = static_cast<unsigned char*>(data);
        copyData(ucdata, width, height, pixelFormat);
    }
    else if(isFormat16Bits(pixelFormat))
    {
        auto* usdata = static_cast<unsigned short*>(data);
        copyData(usdata, width, height, pixelFormat);
    }
    else if(isFormat32Bits(pixelFormat))
    {
        auto* fdata = static_cast<float*>(data);
        copyData(fdata, width, height, pixelFormat);
    }
}

Image::Image(const Image& other):
    Image(other.m_width, other.m_height)
{
    copyData(other);
}

Image::Image(Image&& other):
    m_width(other.width()),
    m_height(other.height())
{
    std::swap(m_data, other.m_data);
}


const Image::Color* Image::data() const
{
    return m_data.data();
}

int Image::height() const
{
    return m_height;
}

int Image::width() const
{
    return m_width;
}

Image::Color Image::operator()(int column, int row) const
{
    if(column > m_width || column < 0 || row < 0 || row > m_height)
    {
        throw std::runtime_error("Trying to access out of range value");
    }
    return m_data[row * m_width + column];
}

Image::Color& Image::operator()(int column, int row)
{
    if(column > m_width || column < 0 || row < 0 || row > m_height)
    {
        throw std::runtime_error("Trying to access out of range value");
    }
    return m_data[row * m_width + column];
}

Image& Image::operator=(const Image& other)
{
    resizeData(other.width(), other.height());
    copyData(other);
    return *this;
}

void Image::copyData(const Image& other)
{
    for(int rowIndex = 0; rowIndex < other.m_height; ++rowIndex)
    {
        for(int columnIndex = 0; columnIndex < other.m_width; ++columnIndex)
        {
            (*this)(columnIndex, rowIndex) = static_cast<Color>(other(columnIndex, rowIndex));
        }
    }
}

void Image::copyData(unsigned char* data, int width, int height,
                     ImageFormat pixelFormat)
{
    for(int rowIndex = 0; rowIndex < height; ++rowIndex)
    {
        for(int columnIndex = 0; columnIndex < width; ++columnIndex)
        {
            Color4uc color{};
            for(unsigned int colorComponent = 0;
                colorComponent < static_cast<unsigned int>(formatChannelCount(pixelFormat));
                ++colorComponent)
            {
                color[colorComponent] = *(data + width * rowIndex + columnIndex + colorComponent);
            }
            (*this)(rowIndex, columnIndex) = color;
        }
    }
}

void Image::copyData(unsigned short* data, int width, int height,
                     ImageFormat pixelFormat)
{
    for(int rowIndex = 0; rowIndex < height; ++rowIndex)
    {
        for(int columnIndex = 0; columnIndex < width; ++columnIndex)
        {
            Color4us color{};
            for(int colorComponent = 0;
                colorComponent < formatChannelCount(pixelFormat);
                ++colorComponent)
            {
                color[colorComponent] = *(data + width * rowIndex + columnIndex + colorComponent);
            }
            (*this)(rowIndex, columnIndex) = color;
        }
    }
}

void Image::copyData(float* data, int width, int height, ImageFormat pixelFormat)
{
    for(int rowIndex = 0; rowIndex < height; ++rowIndex)
    {
        for(int columnIndex = 0; columnIndex < width; ++columnIndex)
        {
            Color4f color{};
            for(int colorComponent = 0;
                colorComponent < formatChannelCount(pixelFormat);
                ++colorComponent)
            {
                color[colorComponent] = *(data + width * rowIndex + columnIndex + colorComponent);
            }
            (*this)(rowIndex, columnIndex) = color;
        }
    }
}

void Image::resizeData(int width, int height)
{
    if(width < 0 || height < 0)
    {
        throw std::invalid_argument("New image dimensions must be positive integers!");
    }
    m_height = height;
    m_width = width;
    m_data.resize(height * width);
}

}


