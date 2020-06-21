#include <stbipp/Image.hpp>
#include <stbipp/ImageImporter.hpp>
#include <stbipp/ImageExporter.hpp>

int main()
{
    bool loadSuccessful{};
    auto image = stbipp::loadImage("D:/Bureau/easy.png", stbipp::ImageFormat::RGB8, loadSuccessful);
    if(!loadSuccessful)
    {
        return 1;
    }

    image(0, 0) = stbipp::Color3uc{255, 127, 0};

    stbipp::Image save(1000, 1000);

    for(auto i = 0; i < save.height(); ++i)
    {
        for(auto j = 0; j < save.width(); ++j)
        {
            // https://www.shadertoy.com/view/XtVyRz
            stbipp::Color2f uv = {static_cast<float>(j) / save.width() * 3.5f - 1.8f, static_cast<float>(i) / save.height() * 2.0f - 1.0f};
            //uv = (uv * vec2(3.5, 2.0)) - vec2(1.8, 1.0);
            stbipp::Color2f z;
            stbipp::Color2f c;
            float xtemp;

            z.r() = uv.r();
            z.g() =  uv.g();

            c.r() = -0.835;
            c.g() = -0.2321;


            //c =  stbipp::Color2f(0.7885 * std::cos(time * speed), 0.7885 * std::sin(time * speed));
            int iteration = 0;

            while((z.r() * z.r() + z.g() * z.g() < 2.0f)  &&  iteration < 1000)
            {
                xtemp = z.r() * z.r() - z.g() * z.g();
                z.g() = 2.0f * z.r() * z.g()  + c.g() ;
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
                save(j, i) = {color, color, color};
            }
        }
    }
    if(!stbipp::saveImage("D:/Bureau/test.png", save, stbipp::ImageSaveFormat::LUM))
    {
        return 1;
    }


    return 0;
}
