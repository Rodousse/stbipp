#pragma once

#include "stbipp/ImageFormat.hpp"

#include <type_traits>

namespace stbipp {


template <ImageFormat pixelFormat>
struct PixelTypeTrait
{
    typedef void type;
    static constexpr int size = 0;
    static constexpr ImageFormat format8Bits = ImageFormat::RGB8;
    static constexpr ImageFormat format16Bits = ImageFormat::RGB16;
    static constexpr ImageFormat format32Bits = ImageFormat::RGB32;
};

template <>
struct PixelTypeTrait<ImageFormat::LUM8>
{
    typedef unsigned char type;
    static constexpr int size = 1;
    static constexpr ImageFormat format8Bits = ImageFormat::LUM8;
    static constexpr ImageFormat format16Bits = ImageFormat::LUM16;
    static constexpr ImageFormat format32Bits = ImageFormat::LUM32;
};

template <>
struct PixelTypeTrait<ImageFormat::LUMA8>
{
    typedef unsigned char type;
    static constexpr int size = 2;
    static constexpr ImageFormat format8Bits = ImageFormat::LUMA8;
    static constexpr ImageFormat format16Bits = ImageFormat::LUMA16;
    static constexpr ImageFormat format32Bits = ImageFormat::LUMA32;
};

template <>
struct PixelTypeTrait<ImageFormat::RGB8>
{
    typedef unsigned char type;
    static constexpr int size = 3;
    static constexpr ImageFormat format8Bits = ImageFormat::RGB8;
    static constexpr ImageFormat format16Bits = ImageFormat::RGB16;
    static constexpr ImageFormat format32Bits = ImageFormat::RGB32;
};

template <>
struct PixelTypeTrait<ImageFormat::RGBA8>
{
    typedef unsigned char type;
    static constexpr int size = 4;
    static constexpr ImageFormat format8Bits = ImageFormat::RGBA8;
    static constexpr ImageFormat format16Bits = ImageFormat::RGBA16;
    static constexpr ImageFormat format32Bits = ImageFormat::RGBA32;
};

template <>
struct PixelTypeTrait<ImageFormat::LUM16>
{
    typedef unsigned short type;
    static constexpr int size = 1;
    static constexpr ImageFormat format8Bits = ImageFormat::LUM8;
    static constexpr ImageFormat format16Bits = ImageFormat::LUM16;
    static constexpr ImageFormat format32Bits = ImageFormat::LUM32;
};

template <>
struct PixelTypeTrait<ImageFormat::LUMA16>
{
    typedef unsigned short type;
    static constexpr int size = 2;
    static constexpr ImageFormat format8Bits = ImageFormat::LUMA8;
    static constexpr ImageFormat format16Bits = ImageFormat::LUMA16;
    static constexpr ImageFormat format32Bits = ImageFormat::LUMA32;
};

template <>
struct PixelTypeTrait<ImageFormat::RGB16>
{
    typedef unsigned short type;
    static constexpr int size = 3;
    static constexpr ImageFormat format8Bits = ImageFormat::RGB8;
    static constexpr ImageFormat format16Bits = ImageFormat::RGB16;
    static constexpr ImageFormat format32Bits = ImageFormat::RGB32;
};

template <>
struct PixelTypeTrait<ImageFormat::RGBA16>
{
    typedef unsigned short type;
    static constexpr int size = 4;
    static constexpr ImageFormat format8Bits = ImageFormat::RGBA8;
    static constexpr ImageFormat format16Bits = ImageFormat::RGBA16;
    static constexpr ImageFormat format32Bits = ImageFormat::RGBA32;
};

template <>
struct PixelTypeTrait<ImageFormat::LUM32>
{
    typedef float type;
    static constexpr int size = 1;
    static constexpr ImageFormat format8Bits = ImageFormat::LUM8;
    static constexpr ImageFormat format16Bits = ImageFormat::LUM16;
    static constexpr ImageFormat format32Bits = ImageFormat::LUM32;
};

template <>
struct PixelTypeTrait<ImageFormat::LUMA32>
{
    typedef float type;
    static constexpr int size = 2;
    static constexpr ImageFormat format8Bits = ImageFormat::LUMA8;
    static constexpr ImageFormat format16Bits = ImageFormat::LUMA16;
    static constexpr ImageFormat format32Bits = ImageFormat::LUMA32;
};

template <>
struct PixelTypeTrait<ImageFormat::RGB32>
{
    typedef float type;
    static constexpr int size = 3;
    static constexpr ImageFormat format8Bits = ImageFormat::RGB8;
    static constexpr ImageFormat format16Bits = ImageFormat::RGB16;
    static constexpr ImageFormat format32Bits = ImageFormat::RGB32;
};

template <>
struct PixelTypeTrait<ImageFormat::RGBA32>
{
    typedef float type;
    static constexpr int size = 4;
    static constexpr ImageFormat format8Bits = ImageFormat::RGBA8;
    static constexpr ImageFormat format16Bits = ImageFormat::RGBA16;
    static constexpr ImageFormat format32Bits = ImageFormat::RGBA32;
};

}
