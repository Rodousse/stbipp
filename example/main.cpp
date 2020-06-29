#include <stbipp/Image.hpp>
#include <stbipp/ImageExporter.hpp>
#include <stbipp/ImageImporter.hpp>

int main()
{
    bool loadSuccessful{};
    auto image =
      stbipp::loadImage(std::string(RESOURCE_PATH) + "/example.jpeg", stbipp::ImageFormat::RGB8, loadSuccessful);
    if(!loadSuccessful)
    {
        return 1;
    }

    stbipp::Image save(image.width(), image.height());

    for(auto i = 0; i < save.height(); ++i)
    {
        for(auto j = 0; j < save.width(); ++j)
        {
            using namespace stbipp;
            // https://www.shadertoy.com/view/XtVyRz

            Color2f uv = Color2f(j, i) / Color2f(save.width(), save.height());
            uv = (uv * Color2f(3.5, 2.0)) - Color2f(1.8, 1.0);
            Color2f z = uv;
            Color2f c(-0.835, -0.2321);

            int iteration = 0;

            while((z.r() * z.r() + z.g() * z.g() < 2.0f) && iteration < 1000)
            {
                float xtemp = z.r() * z.r() - z.g() * z.g();
                z.g() = 2.0f * z.r() * z.g() + c.g();
                z.r() = xtemp + c.r();

                ++iteration;
            }

            if(iteration == 1000)
            {
                save(j, i) = {};
            }
            else
            {
                auto color = 10.0f * float(iteration) / 1000;
                save(j, i) = Color4f{color, color, color} + image(j, i);
            }
        }
    }
    if(!stbipp::saveImage("test.png", save, stbipp::ImageSaveFormat::RGB))
    {
        return 1;
    }

    return 0;
}
