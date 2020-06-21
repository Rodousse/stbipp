#include "stbipp/Image.hpp"

#include "stbipp/TypeTraits.hpp"

namespace stbipp {

Image::Image(unsigned int width, unsigned int height)
{
    resizeData(width, height);
}

Image::Image(void* data, unsigned int width, unsigned int height, ImageFormat pixelFormat):
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

unsigned int Image::height() const
{
    return m_height;
}

unsigned int Image::width() const
{
    return m_width;
}

Image::Color Image::operator()(unsigned int column, unsigned int row) const
{
    return m_data[row * m_width + column];
}

Image::Color& Image::operator()(unsigned int column, unsigned int row)
{
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
    for(unsigned int rowIndex = 0; rowIndex < other.m_height; ++rowIndex)
    {
        for(unsigned int columnIndex = 0; columnIndex < other.m_width; ++columnIndex)
        {
            (*this)(columnIndex, rowIndex) = static_cast<Color>(other(columnIndex, rowIndex));
        }
    }
}

void Image::copyData(unsigned char* data, unsigned int width, unsigned int height,
                     ImageFormat pixelFormat)
{
    for(unsigned int rowIndex = 0; rowIndex < height; ++rowIndex)
    {
        for(unsigned int columnIndex = 0; columnIndex < width; ++columnIndex)
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

void Image::copyData(unsigned short* data, unsigned int width, unsigned int height,
                     ImageFormat pixelFormat)
{
    for(unsigned int rowIndex = 0; rowIndex < height; ++rowIndex)
    {
        for(unsigned int columnIndex = 0; columnIndex < width; ++columnIndex)
        {
            Color4us color{};
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

void Image::copyData(float* data, unsigned int width, unsigned int height, ImageFormat pixelFormat)
{
    for(unsigned int rowIndex = 0; rowIndex < height; ++rowIndex)
    {
        for(unsigned int columnIndex = 0; columnIndex < width; ++columnIndex)
        {
            Color4f color{};
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

void Image::resizeData(unsigned int width, unsigned int height)
{
    m_height = height;
    m_width = width;
    m_data.resize(height * width);
}

}


