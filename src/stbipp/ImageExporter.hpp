#pragma once

#include "stbipp/Image.hpp"

#include <string>

namespace stbipp {
namespace stbiw {

STBIPP_API bool write_png(char const* filename, int w, int h, int comp, const void*  data,
                          int stride_in_bytes);
STBIPP_API bool write_bmp(char const* filename, int w, int h, int comp, const void*  data);
STBIPP_API bool write_tga(char const* filename, int w, int h, int comp, const void*  data);
STBIPP_API bool write_hdr(char const* filename, int w, int h, int comp, const float* data);
// Dumb write hdr for non floating data
STBIPP_API bool write_hdr(char const* filename, int w, int h, int comp, const void* data);
STBIPP_API bool write_jpg(char const* filename, int w, int h, int comp, const void*  data,
                          int quality);

}

STBIPP_API bool isOneByteFileSavedFormat(const std::string& extension);
STBIPP_API bool isFileSavedFormatSupported(const std::string& extension);
}



namespace stbipp {

template<ImageFormat format>
bool saveImage(const std::string& path, const Image<format>& image)
{
    std::string pathExtension = path.substr(path.find_last_of(".") + 1);

    if(pathExtension.empty())
    {
        return false;
    }

    std::transform(pathExtension.begin(), pathExtension.end(), pathExtension.begin(),
                   [](unsigned char c)
    {
        return std::tolower(c);
    }
                  );

    if(!isFileSavedFormatSupported(pathExtension))
    {
        return false;
    }

    const int channels = PixelTypeTrait_s<format>;

    if(isOneByteFileSavedFormat(pathExtension))
    {
        const void* unsignedCharData = static_cast<const void*>(image.data());

        Image<PixelTypeTraits_8Bits<format>> ucImage;
        if(!isFormat8Bits(image.format()))
        {
            ucImage = image;
            unsignedCharData = static_cast<const void*>(ucImage.data());
        }

        if(pathExtension == "png")
        {
            return stbiw::write_png(path.data(), image.width(), image.height(), channels, unsignedCharData,
                                    image.width() * channels);
        }
        else if(pathExtension == "bmp")
        {
            return stbiw::write_bmp(path.data(), image.width(), image.height(), channels, unsignedCharData);
        }
        else if(pathExtension == "tga")
        {
            return stbiw::write_tga(path.data(), image.width(), image.height(), channels, unsignedCharData);
        }
        else if(pathExtension == "jpg" || pathExtension == "jpeg")
        {
            return stbiw::write_jpg(path.data(), image.width(), image.height(), channels, unsignedCharData,
                                    100);
        }
    }
    else if(pathExtension == "hdr")
    {
        if(!isFormat32Bits(image.format()))
        {
            return false;
        }
        return stbiw::write_hdr(path.data(), image.width(), image.height(), channels, image.data());
    }


    return false;


}

}


