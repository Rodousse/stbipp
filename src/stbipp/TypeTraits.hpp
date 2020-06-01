#pragma once

#include "stbipp/ImageFormat.hpp"

namespace stbipp {


template <ImageFormat pixelFormat>
struct PixelTypeTrait
{
    typedef void type;
};

template <>
struct PixelTypeTrait<ImageFormat::LUM8>
{
    typedef unsigned char type;
};

template <>
struct PixelTypeTrait<ImageFormat::LUMA8>
{
    typedef unsigned char type;
};

template <>
struct PixelTypeTrait<ImageFormat::RGB8>
{
    typedef unsigned char type;
};

template <>
struct PixelTypeTrait<ImageFormat::RGBA8>
{
    typedef unsigned char type;
};

template <>
struct PixelTypeTrait<ImageFormat::LUM16>
{
    typedef unsigned short type;
};

template <>
struct PixelTypeTrait<ImageFormat::LUMA16>
{
    typedef unsigned short type;
};

template <>
struct PixelTypeTrait<ImageFormat::RGB16>
{
    typedef unsigned short type;
};

template <>
struct PixelTypeTrait<ImageFormat::RGBA16>
{
    typedef unsigned short type;
};

template <>
struct PixelTypeTrait<ImageFormat::LUM32>
{
    typedef float type;
};

template <>
struct PixelTypeTrait<ImageFormat::LUMA32>
{
    typedef float type;
};

template <>
struct PixelTypeTrait<ImageFormat::RGB32>
{
    typedef float type;
};

template <>
struct PixelTypeTrait<ImageFormat::RGBA32>
{
    typedef float type;
};

template <ImageFormat pixelFormat>
using PixelTypeTrait_t = typename PixelTypeTrait<pixelFormat>::type;

}
