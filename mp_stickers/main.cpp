#include "Image.h"
#include "StickerSheet.h"

int main() {

Image shrek;
shrek.readFromFile("shrek.png");
Image water_gun;
water_gun.readFromFile("water_gun.png");
Image sunglasses;
sunglasses.readFromFile("sunglasses.png");
Image hat;
hat.readFromFile("hat.png");

StickerSheet sheet(shrek, 3);
sheet.addSticker(water_gun, 50,50);
sheet.addSticker(sunglasses, 100,100);
sheet.addSticker(hat, 200,200);

Image render = sheet.render();
render.writeToFile("myImage.png");
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  return 0;
}
