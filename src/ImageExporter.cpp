#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stbipp/ImageExporter.hpp"

#include <stb_image_write.h>

#include <unordered_set>

namespace stbipp {

const std::unordered_set<std::string> getOneByteFileSavedFormat();
const std::unordered_set<std::string> getSupportedSaveFileFormat();

namespace stbiw {

//8
bool write_png(char const* filename, int w, int h, int comp, const void*  data,
               int stride_in_bytes)
{
    return stbi_write_png(filename, w, h, comp, data, stride_in_bytes);
}
//8
bool write_bmp(char const* filename, int w, int h, int comp, const void*  data)
{
    return stbi_write_bmp(filename, w, h, comp, data);
}
//8
bool write_tga(char const* filename, int w, int h, int comp, const void*  data)
{
    return stbi_write_tga(filename, w, h, comp, data);
}
//32
bool write_hdr(char const* filename, int w, int h, int comp, const float* data)
{
    return stbi_write_hdr(filename, w, h, comp, data);
}

bool write_hdr(char const* filename, int w, int h, int comp, const void* data)
{
    return false;
}
bool write_jpg(char const* filename, int w, int h, int comp, const void*  data,
               int quality)
{
    return stbi_write_jpg(filename, w, h, comp, data, quality);
}

}

bool isOneByteFileSavedFormat(const std::string& extension)
{
    return getOneByteFileSavedFormat().count(extension);
}

bool isFileSavedFormatSupported(const std::string& extension)
{
    return getSupportedSaveFileFormat().count(extension);
}

const std::unordered_set<std::string> getOneByteFileSavedFormat()
{
    return {"png", "bmp", "tga", "jpg", "jpeg"};
}

const std::unordered_set<std::string> getSupportedSaveFileFormat()
{
    auto fileFormat = getOneByteFileSavedFormat();
    fileFormat.insert({"hdr"});
    return fileFormat;
}
}
