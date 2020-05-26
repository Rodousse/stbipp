#include <stbipp/Image.hpp>
#include <stbipp/ImageImporter.hpp>

int main()
{
    auto image = stbipp::loadImage<stbipp::ImageFormat::RGB8>("D:/Bureau/easy.png");

    return 0;
}
