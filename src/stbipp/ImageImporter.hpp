#pragma once
#include "StbippSymbols.h"
#include "stbipp/Image.hpp"
#include "stbipp/TypeTraits.hpp"

#include <string>

namespace stbipp
{
/**
 * @brief Load an image at the given path with the given pixel format
 * @param[in] path Path to the image to load
 * @param[out] image The image which will contains the data (all contained data will be erased)
 * @param[in] pixelFormat The pixel format to use
 * @return true if the loading was successful
 */
STBIPP_API bool loadImage(const std::string& path, Image& image, const ImageFormat pixelFormat);
} // namespace stbipp
