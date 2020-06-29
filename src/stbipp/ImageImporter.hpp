#pragma once
#include "StbippSymbols.h"
#include "stbipp/Image.hpp"
#include "stbipp/TypeTraits.hpp"

#include <string>

namespace stbipp
{
STBIPP_API bool loadImage(const std::string& path, Image& image, const ImageFormat pixelFormat);
} // namespace stbipp
