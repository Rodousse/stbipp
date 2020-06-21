#pragma once

#include "StbippSymbols.h"

#include "stbipp/Color.hpp"

#include <vector>
#include <memory>


namespace stbipp {


class STBIPP_API Image
{
public:
    using Color = Color4f;

    explicit Image() = default;

    Image(unsigned int width, unsigned int height);

    Image(void* data, unsigned int width, unsigned int height, ImageFormat pixelFormat);

    Image(const Image& other);

    Image(Image&& other);

    ~Image() = default;

    const Color* data() const;

    template<class ColorType>
    std::vector<ColorType> castData() const
    {
        std::size_t size = m_width * m_height;
        std::vector<ColorType> castedValue(size);
        for(std::size_t index = 0; index < size; ++index)
        {
            castedValue[index] = m_data[index];
        }
        return castedValue;
    }

    unsigned int  height() const;

    unsigned int  width() const;

    Color operator()(unsigned int column, unsigned int row) const;

    Color& operator()(unsigned int column, unsigned int row);

    Image& operator=(const Image& other);



private:

    void copyData(const Image& other);

    void copyData(unsigned char* data, unsigned int width, unsigned int height,
                  ImageFormat pixelFormat);

    void copyData(unsigned short* data, unsigned int width, unsigned int height,
                  ImageFormat pixelFormat);

    void copyData(float* data, unsigned int width, unsigned int height, ImageFormat pixelFormat);

    void resizeData(unsigned int width, unsigned int height);

    std::vector<Color> m_data;
    unsigned int m_width;
    unsigned int m_height;

};



}



