#pragma once
#include "StbippSymbols.h"
#include "stbipp/Image.hpp"
#include "stbipp/TypeTraits.hpp"

#include <string>

namespace stbipp
{
STBIPP_API Image loadImage(const std::string& path, const ImageFormat pixelFormat, bool& success);
}
