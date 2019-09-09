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
  // TODO: Part 3

  return png;
}
