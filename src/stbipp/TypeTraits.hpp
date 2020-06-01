#pragma once

#include "stbipp/ImageFormat.hpp"

#include <type_traits>

namespace stbipp {


template <ImageFormat pixelFormat>
struct PixelTypeTrait
{
    typedef void type;
    static constexpr int size = 0;
};

template <>
struct PixelTypeTrait<ImageFormat::LUM8>
{
    typedef unsigned char type;
    static constexpr int size = 1;
};

template <>
struct PixelTypeTrait<ImageFormat::LUMA8>
{
    typedef unsigned char type;
    static constexpr int size = 2;
};

template <>
struct PixelTypeTrait<ImageFormat::RGB8>
{
    typedef unsigned char type;
    static constexpr int size = 3;
};

template <>
struct PixelTypeTrait<ImageFormat::RGBA8>
{
    typedef unsigned char type;
    static constexpr int size = 4;
};

template <>
struct PixelTypeTrait<ImageFormat::LUM16>
{
    typedef unsigned short type;
    static constexpr int size = 1;
};

template <>
struct PixelTypeTrait<ImageFormat::LUMA16>
{
    typedef unsigned short type;
    static constexpr int size = 2;
};

template <>
struct PixelTypeTrait<ImageFormat::RGB16>
{
    typedef unsigned short type;
    static constexpr int size = 3;
};

template <>
struct PixelTypeTrait<ImageFormat::RGBA16>
{
    typedef unsigned short type;
    static constexpr int size = 4;
};

template <>
struct PixelTypeTrait<ImageFormat::LUM32>
{
    typedef float type;
    static constexpr int size = 1;
};

template <>
struct PixelTypeTrait<ImageFormat::LUMA32>
{
    typedef float type;
    static constexpr int size = 2;
};

template <>
struct PixelTypeTrait<ImageFormat::RGB32>
{
    typedef float type;
    static constexpr int size = 3;
};

template <>
struct PixelTypeTrait<ImageFormat::RGBA32>
{
    typedef float type;
    static constexpr int size = 4;
};

template <ImageFormat pixelFormat>
using PixelTypeTrait_t = typename PixelTypeTrait<pixelFormat>::type;
template <ImageFormat pixelFormat>
static constexpr int PixelTypeTrait_s = PixelTypeTrait<pixelFormat>::size;

template <class DataType, int nbComponent>
constexpr bool is_color_format_supported = (std::is_same<DataType, unsigned short>::value
        || std::is_same<DataType, unsigned char>::value
        || std::is_same<DataType, float>::value) && (nbComponent > 0) && (nbComponent < 5) ;

}
