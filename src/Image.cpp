#include "Image.h"

Image::Image(string fileName):
Drawable()
{
    if (fileName != "") {
        setFileName(fileName);
    }
}

void Image::setFileName(string fileName)
{
    image.ReadFromFile(fileName.c_str());
}


/* ---------- Overriding from Drawable ---------- */

int Image::getWidth() const {
    return image.TellWidth();
}

int Image::getHeight() const {
    return image.TellHeight();
}


/* ---------- Implemented from Drawable ---------- */

void Image::draw()
{
    for(int i = 0; i < getWidth(); i++)
    {
        for(int j = 0; j < getHeight(); j++)
        {
            int red = image.GetPixel(i, j).Red;
            int green = image.GetPixel(i, j).Green;
            int blue = image.GetPixel(i, j).Blue;

            unsigned int rgb = ((red & 0xff) << 16) + ((green & 0xff) << 8) + (blue & 0xff);

            //cout << rgb << endl;

            g->setColor(rgb);

            g->plot(getLocationX()+i, getLocationY()+getHeight()-j);

            //cout << getLocationX()+i << " " << getLocationY()-j << endl;
        }
    }

    isVisible = true;
}

void Image::erase()
{

}

string getName(int n)
{
    string name;
    
    if(n == 1) name = "../img/1.bmp";
    else if(n == 2) name = "../img/2.bmp";
    else if(n == 3) name = "../img/3.bmp";
    else if(n == 4) name = "../img/4.bmp";
    else if(n == 5) name = "../img/5.bmp";
    else if(n == 6) name = "../img/6.bmp";
    else if(n == 7) name = "../img/7.bmp";
    else if(n == 8) name = "../img/8.bmp";
    else if(n == 9) name = "../img/9.bmp";
    else if(n == 0) name = "../img/0.bmp";
    
    return name;
}
