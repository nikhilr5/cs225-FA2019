#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace cs225;

void Image:: lighten(double amount) {
  for (unsigned int i = 0; i < this->width(); i++) {
    for (unsigned int j = 0; j< this->height(); j++) {
      HSLAPixel & pixel = this->getPixel(i,j);

      pixel.l += amount;
      if (pixel.l > 1) {
        pixel.l = 1;
      }
    }
  }
}

void Image :: lighten() {
  lighten(0.1);
}

void Image:: darken(double amount) {
  for (unsigned int i = 0; i < this->width(); i++) {
    for (unsigned int j = 0; j< this->height(); j++) {
      HSLAPixel & pixel = this->getPixel(i,j);

      pixel.l -= amount;
      if (pixel.l < 0) {
        pixel.l = 0;
      }
    }
  }
}

void Image :: darken() {
  darken(0.1);
}

void Image ::  saturate(double amount) {
  for (unsigned int i = 0; i < this->width(); i++) {
    for (unsigned int j = 0; j< this->height(); j++) {
      HSLAPixel & pixel = this->getPixel(i,j);

      pixel.s += amount;
      if (pixel.s > 1) {
        pixel.s = 1;
      } else if (pixel.s < 0) {
        pixel.s = 0;
      }
    }
  }
}

void Image :: saturate() {
  saturate(0.1);
}

void Image :: desaturate() {
  saturate(-0.1);
}

void Image :: desaturate(double amount) {
  double negativeAmount = 0 - amount;
  saturate(negativeAmount);
}

void Image :: grayscale() {
  saturate(-2);
}

void Image:: rotateColor(double degrees) {
  for (unsigned int i = 0; i < this->width(); i++) {
    for (unsigned int j = 0; j < this->height(); j++) {
      HSLAPixel & pixel = this->getPixel(i,j);

      pixel.h += degrees;
      while (pixel.h > 360) {
        pixel.h -= 360;
      }
      while (pixel.h < 0) {
        pixel.h += 360;
      }
    }
  }
}

void Image:: illinify() {
  for (unsigned int x = 0; x< this->width(); x++){
    for (unsigned int y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      if(pixel.h < 114 || pixel.h > 293) {
        pixel.h = 11;
      } else {
        pixel.h = 216;
      }
    }
  }
}

void Image:: scale(double factor) {
  int newWidth = (this->width() * factor);
  int newHeight = (this->height() * factor);
  Image * newImage = new Image();

  *newImage = *this;


  this->resize(newWidth, newHeight); //png function

  for (unsigned int x = 0; x< this->width(); x++){
    for (unsigned int y = 0; y < this->height(); y++) {
        int newX = x / factor;
        int newY = y / factor;

        HSLAPixel & newPixel = newImage->getPixel(newX,newY);
        HSLAPixel & pixel = this->getPixel(x,y);
        pixel = newPixel;
    }
  }
  delete newImage;
}

void Image:: scale (unsigned w, unsigned h) {
Image * newImage = new Image();
*newImage = *this;

  this->resize(w, h); //png function
  double wFactor = w / width();
  double hFactor = h / height();

  for (unsigned int x = 0; x< this->width(); x++){
    for (unsigned int y = 0; y < this->height(); y++) {

        HSLAPixel & newPixel = newImage->getPixel(x/ wFactor ,y / hFactor);
        HSLAPixel & pixel = this->getPixel(x,y);
        pixel = newPixel;
    }
  }
  delete newImage;
}
