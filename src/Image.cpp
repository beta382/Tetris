#include "Image.h"

Image::Image()
{

}

void Image::setFileName(string fileName)
{
    image.ReadFromFile(fileName.c_str());
}

void Image::draw()
{
    for(int i = 0; i < image.TellWidth(); i++)
    {
        for(int j = 0; j < image.TellHeight(); j++)
        {
            int red = image.GetPixel(i, j).Red;
            int green = image.GetPixel(i, j).Green;
            int blue = image.GetPixel(i, j).Blue;

            unsigned int rgb = ((red & 0xff) << 16) + ((green & 0xff) << 8) + (blue & 0xff);

            //cout << rgb << endl;

            g->setColor(rgb);

            g->plot(getLocationX()+i, getLocationY()-j);

            //cout << getLocationX()+i << " " << getLocationY()-j << endl;
        }
    }

    isVisible = true;
}

void Image::erase()
{

}
