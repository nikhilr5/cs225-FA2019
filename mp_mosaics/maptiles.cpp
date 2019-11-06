/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
#include <vector>
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    int rows = theSource.getRows();
    int columns = theSource.getColumns();
    if (rows == 0 || columns == 0 || theTiles.empty())
    return NULL;


    vector<Point<3>> kdPoints;
    map<Point<3>, size_t> map_;

    size_t size3 = 0;

    //gets average color of tileimage converts to Point
    for (auto a : theTiles) {
      LUVAPixel pix = a.getAverageColor();
      //luva used bc color can be turned into point to compare distance
      Point<3> point = convertToXYZ(pix);
      kdPoints.push_back(point);
      map_[point] = size3;
      size3++;
    }

    //make sorted kd tree
    KDTree<3> *tree = new KDTree<3>(kdPoints);

    MosaicCanvas * returnMosaic = new MosaicCanvas(rows, columns);

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        LUVAPixel currentRegion = theSource.getRegionColor(i,j);
        //regions average color
        Point<3> averageColor = convertToXYZ(currentRegion);
        //closed tile to regioncolor
        Point<3> picture = tree->findNearestNeighbor(averageColor);

        //gets the index of the particular tile
        size_t index = map_[picture];

        //sets the region in the return mosaic to the picture
        returnMosaic->setTile(i,j, &theTiles[index]);

      }
    }
    //segfault
    delete tree;
    return returnMosaic;
}
