# Stbipp

Stbipp is a cross-platform small sized image I/O library based on [stb_image and stb_image_write](https://github.com/nothings/stb), developed in C++11.

It brings an abstract layer between the features of stb_image and the developer, and CMake files to easily incorporate the library into your projects.

The initial idea was to create a library to easily load and write images, and convert those into different formats. Edit the images without having the overhead of a big library.

The supported load format are the same as stb_image :


> JPEG baseline & progressive (12 bpc/arithmetic not supported, same as stock IJG lib)
> 
> PNG 1/2/4/8/16-bit-per-channel
> 
> TGA (not sure what subset, if a subset)
> 
> BMP non-1bpp, non-RLE
> 
> PSD (composited view only, no extra channels, 8/16 bit-per-channel)
> 
> GIF (*comp always reports as 4-channel)
> 
> HDR (radiance rgbE format)
> 
> PIC (Softimage PIC)
> 
> PNM (PPM and PGM binary only)

Also the supported export format are the same as stb_image_write :

- JPEG
- PNG
- BMP
- HDR
- TGA

# Requirements

Really few requirements are needed :
- A C++ compiler compatible with the C++11 standard.
- CMake

# Install

Just clone the project and build/ install it where you want 
``` bash
git clone https://github.com/Rodousse/stbipp.git
cd stbipp
mkdir build
cd build
cmake ..
make
```

# Example

``` cpp
#include <stbipp/Image.hpp>
#include <stbipp/ImageExporter.hpp>
#include <stbipp/ImageImporter.hpp>

int main()
{
    // Load Image
    stbipp::Image image{};
    // Load image as an RGB image with 8 bits per channel
    if(!stbipp::loadImage(std::string(RESOURCE_PATH) + "/example.jpeg", image, stbipp::ImageFormat::RGB8))
    {
        return 1;
    }

    // Create an image with the given dimensions
    stbipp::Image save(image.width(), image.height());

    // Fill the image
    for(auto y = 0; y < save.height(); ++y)
    {
        for(auto x = 0; x < save.width(); ++x)
        {
            using namespace stbipp;
            save(x, y) = Color4f{static_cast<float>(x)/save.width(), 
                                 static_cast<float>(y)/save.height(), 
                                 0.0f, 
                                 0.0f};
        }
    }

    // Clone image in a different format (e.g : RGB with 16 bits per channel)
    auto castedImage = save.castData<stbipp::Color3us>();

    // Export the created image as a grayscale with alpha image
    if(!stbipp::saveImage("test.png", save, stbipp::ImageSaveFormat::LUMA))
    {
        return 1;
    }

    return 0;
}
```
