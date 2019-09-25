#include "StickerSheet.h"

using namespace std;

StickerSheet :: StickerSheet (const Image &picture, unsigned max) {
  base = new Image(picture);
  max_ = max;
  images = new  Image *[max_];
  xCord = new unsigned[max_];
  yCord = new unsigned[max_];
  stickerCounter = 0;
  xCord[0] = 0;
  yCord[0] = 0;
  for (unsigned i =0; i < max_; i++) {
    images[i] = NULL;
  }

}

void StickerSheet:: deleter() {
  for (unsigned i = 0; i < stickerCounter; i++) {
    delete images[i];
    images[i] = nullptr;
  }
  delete base;
  delete[] xCord;
  delete[] yCord;
  delete[] images;
  images = nullptr;
}

StickerSheet:: ~StickerSheet() {
  deleter();

}

StickerSheet:: StickerSheet(const StickerSheet & other) {
  copy(other);
}

void StickerSheet:: copy(const StickerSheet & other) {
  max_ = other.max_;
  base = new Image(*(other.base));
  images = new Image *[max_];
  xCord = new unsigned[max_];
  yCord = new unsigned[max_];
  stickerCounter = other.stickerCounter;
  for (unsigned i = 0; i < stickerCounter; i++) {
    images[i] = new Image();
    *(images[i]) = *(other.images[i]);
    xCord[i] = other.yCord[i];
    yCord[i] = other.yCord[i];
  }
}

int StickerSheet:: addSticker(Image & sticker, unsigned x, unsigned y) {
  for(unsigned i = 0; i < max_; i++) {
    if(stickerCounter == i) {
      images[i] = new Image(sticker);
      xCord[i] = x;
      yCord[i] = y;
      stickerCounter ++;
      return i;
    }
  }
  return -1;
}

void StickerSheet :: changeMaxStickers(unsigned max) {
  if (max == max_) {
    return;
  }
  //cout << "debug 68" << endl;
  Image **newImages = new Image * [max];
  unsigned *newX = new unsigned[max];
  unsigned *newY = new unsigned[max];
  unsigned newStickerCounter = stickerCounter;
  for (unsigned j = 0; j < stickerCounter; j++) {
    newImages[j] = images[j];
    newX[j] = xCord[j];
    newY[j] = yCord[j];
  }

//set new with new max

yCord = new unsigned[max];
xCord = new unsigned[max];
images = new Image *[max];

//more stickers than max wants so delete some
  if (max < stickerCounter) {
    for (unsigned i = max; i < stickerCounter; i++) {
      delete newImages[i];
      newImages[i] = nullptr;
      newStickerCounter--;
    }
    stickerCounter = newStickerCounter;
    for (unsigned i = 0; i < stickerCounter; i++) {
      images[i] = newImages[i];
      xCord[i] = newX[i];
      yCord[i] = newY[i];
    }
  } else {
    for (unsigned i = 0; i < stickerCounter; i++) {
      images[i] = newImages[i];
      xCord[i] = newX[i];
      yCord[i] = newY[i];
      }
  }
  max_ = max;

    delete[] newImages;
    delete[] newX;
    delete[] newY;
    newImages = nullptr;
    newX = nullptr;
    newY = nullptr;

}

const StickerSheet & StickerSheet:: operator=(const StickerSheet& other) {
  if(&other != this) {
    deleter();
    copy(other);
  }
  return *this;
}

Image * StickerSheet:: getSticker(unsigned index) {
  Image *returnImage;
  if (index >= stickerCounter || index < 0) {
    return nullptr;
  }
  returnImage = images[index];
  return returnImage;
}

bool StickerSheet:: translate(unsigned index, unsigned x, unsigned y) {
  if (index < stickerCounter) {
    xCord[index] = x;
    yCord[index] = y;
    return true;
  }
  return false;
}

void StickerSheet:: removeSticker(unsigned index) {
  if(index < stickerCounter) {
    delete images[index];
    for (unsigned i = 1; i < max_ - 1; i++) {
      images[i - 1] = images[i];
      xCord[i - 1] = xCord[i];
      yCord[i - 1] = yCord[i];
    }

    stickerCounter--;
    xCord[max_ - 1] =0;
    yCord[max_ -1] = 0;
    images[max_ -1 ] = nullptr;
  }
}

Image StickerSheet:: render() const{
  Image returnImage(*base);

  unsigned baseWidth = base->width();
  unsigned baseHeight = base->height();

  //pictures possibly over edge
  for (unsigned i = 0; i < stickerCounter; i++) {
    if (images[i] != NULL) {
      unsigned int xEdge = xCord[i] + images[i]->width();
       unsigned int yEdge = yCord[i] + images[i]->height();
    //unsigned int imXWidth = images[i]->width();
      //unsigned int imYHeight = images[i]->height();
      if (xEdge >baseWidth) {
        baseWidth =xCord[i] + images[i]->width();
      }
      if ( yEdge> baseHeight) {
        baseHeight = yCord[i] + images[i]->height();
      }
  }
  }
  returnImage.resize(baseWidth, baseHeight);

  //fill in reuturnImage
  for (unsigned i =0; i < stickerCounter; i++) {
    if (images[i] != nullptr) {
      Image addImage = *images[i];
      for (unsigned j= xCord[i]; j < (xCord[i] + images[i]->width()); j++) {
        for (unsigned k = yCord[i]; k < (yCord[i]+images[i]->height()); k++) {
          unsigned xIn = j - xCord[i]; //start at 0
          unsigned yIn = k - yCord[i];
          cs225::HSLAPixel pixel =addImage.getPixel(xIn, yIn);
          if (pixel.a != 0) {
            returnImage.getPixel(j,k) = pixel;
          }
        }
      }
   }
  }

  return returnImage;

}
