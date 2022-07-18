#include <gtest/gtest.h>
#include <iostream>
#include <stbipp/Color.hpp>
#include <stbipp/Image.hpp>
#include <stbipp/ImageFormat.hpp>
#include <stdexcept>

TEST(Image, default_constructor)
{
    stbipp::Image image;
    EXPECT_EQ(image.height(), 0);
    EXPECT_EQ(image.width(), 0);
}

TEST(Image, size_parameter_constructor)
{
    constexpr int width = 100, height = 200;
    stbipp::Image image(width, height);
    EXPECT_EQ(image.height(), height);
    EXPECT_EQ(image.width(), width);
    for(int x = 0; x < width; ++x)
    {
        for(int y = 0; y < height; ++y)
        {
            EXPECT_NO_THROW(image(x, y));
        }
    }
}

TEST(Image, size_parameter_filled_constructor)
{
    constexpr int width = 100, height = 200;
    stbipp::Color4f color{2.0f, 1.0f, 14.0f, -13.0f};
    stbipp::Image image(width, height, color);
    EXPECT_EQ(image.height(), height);
    EXPECT_EQ(image.width(), width);
    for(int x = 0; x < width; ++x)
    {
        for(int y = 0; y < height; ++y)
        {
            EXPECT_NO_THROW(image(x, y));
            EXPECT_EQ(image(x, y), color);
        }
    }
}

template<typename T, int channels>
void testRawDataConstructor(const T* data, const int width, const int height, stbipp::ImageFormat format)
{
    using ColorTested = stbipp::Color<T, channels>;
    const stbipp::Image image(static_cast<const void*>(data), width, height, format);
    ASSERT_EQ(image.width(), width);
    ASSERT_EQ(image.height(), height);
    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            std::cout << x << y << std::endl;
            std::cout << image(x, y).r() << image(x, y).g() << std::endl;
            ASSERT_EQ(ColorTested(image(x, y)), ColorTested(data + y * width * channels + x * channels));
        }
    }
}

TEST(Image, raw_data_constructor)
{
    const unsigned char data[] = {0, 0, 0, 1, 1, 1, 1, 2, 3};
    testRawDataConstructor<unsigned char, 3>(data, 1, 3, stbipp::ImageFormat::RGB8);
}

TEST(Image, round_bracket_operator)
{
    constexpr int width = 100, height = 200;
    stbipp::Image image(width, height);
    for(int x = 0; x < width; ++x)
    {
        for(int y = 0; y < height; ++y)
        {
            EXPECT_NO_THROW(image(x, y));
        }
    }

    using error_type = std::out_of_range;
    EXPECT_THROW(image(width + 1, height), error_type);
    EXPECT_THROW(image(width, height + 1), error_type);
    EXPECT_THROW(image(width + 1, height + 1), error_type);
    EXPECT_THROW(image(-1, 0), error_type);
    EXPECT_THROW(image(0, -1), error_type);
    EXPECT_THROW(image(-1, -1), error_type);
}

