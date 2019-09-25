/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#ifndef StickerSheet_H
#define StickerSheet_H

#include "Image.h"

class StickerSheet {
  public :
    StickerSheet(const Image & picture, unsigned max);
    ~StickerSheet();
    StickerSheet(const StickerSheet & other);
    const StickerSheet & operator=(const StickerSheet & other);
    void changeMaxStickers(unsigned max);
    int addSticker(Image & sticker, unsigned x, unsigned y);
    bool translate(unsigned index, unsigned x, unsigned y);
    void removeSticker(unsigned index);
    Image * getSticker(unsigned index);
    Image render() const;
    void deleter();
    void copy(const StickerSheet & other);
private:
  Image* base;
  unsigned max_;
  Image ** images;
  unsigned * xCord;
  unsigned * yCord;
  unsigned stickerCounter;


};

#endif
