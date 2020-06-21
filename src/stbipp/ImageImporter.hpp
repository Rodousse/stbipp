#pragma once
#include "stbipp/Image.hpp"
#include "stbipp/TypeTraits.hpp"

#include "StbippSymbols.h"

#include <string>



namespace stbipp {

STBIPP_API Image loadImage(const std::string& path, const ImageFormat pixelFormat, bool& success);

}
