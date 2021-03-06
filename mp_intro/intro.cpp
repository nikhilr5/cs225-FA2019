#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <iostream>

#include <string>


void rotate(std::string inputFile, std::string outputFile) {
  cs225::PNG * image = new cs225:: PNG();
  image->readFromFile(inputFile);
  int width = image->width();
  int height = image->height();
  cs225::PNG * returnImage = new cs225::PNG(width,height);
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      cs225::HSLAPixel &pixel1 = image->getPixel(i,j);
      cs225::HSLAPixel &pixel2 = returnImage->getPixel(width - i -1, height - j -1);
      pixel2 = pixel1;
    }
  }
  returnImage->writeToFile(outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  for (unsigned i = 0; i < width; i++) {
    for (unsigned j = 0; j < height; j++) {
      cs225::HSLAPixel& pixel = png.getPixel(i,j);
      pixel.h = 60;
      pixel.l = 0.57;
      pixel.s = .99;
      pixel.a = .2;
    }
  }
  for (unsigned i = width*.25; i < width*.3; i++) {
    for (unsigned j = 0; j < height; j++) {
      cs225::HSLAPixel& pixel = png.getPixel(i,j);
      pixel.h = 244;
      pixel.l = 0.48;
      pixel.s = .88;
      pixel.a = .6;
    }
  }
  for (unsigned i = 0; i < width; i++) {
    for (unsigned j = height*.8; j < height*.85; j++) {
      cs225::HSLAPixel& pixel = png.getPixel(i,j);
      pixel.h = 297;
      pixel.l = 0.48;
      pixel.s = .98;
      pixel.a = .9;
    }
  }

  // TODO: Part 3

  return png;
}
