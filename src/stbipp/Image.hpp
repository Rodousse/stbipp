#pragma once

#include "StbippSymbols.h"
#include "stbipp/Color.hpp"

#include <memory>
#include <vector>

namespace stbipp
{
class STBIPP_API Image
{
  public:
    using Color = Color4f;

    explicit Image() = default;

    Image(int width, int height);

    Image(void* data, int width, int height, ImageFormat pixelFormat);

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

    int height() const;

    int width() const;

    Color operator()(int column, int row) const;

    Color& operator()(int column, int row);

    Image& operator=(const Image& other);

  private:
    void copyData(const Image& other);

    void copyData(unsigned char* data, int width, int height, ImageFormat pixelFormat);

    void copyData(unsigned short* data, int width, int height, ImageFormat pixelFormat);

    void copyData(float* data, int width, int height, ImageFormat pixelFormat);

    void resizeData(int width, int height);

    std::vector<Color> m_data;
    int m_width;
    int m_height;
};

} // namespace stbipp
