
/* Your code here! */

#pragma once

#include <vector>
#include "cs225/PNG.h"
#include "dsets.h"

using namespace cs225;

class SquareMaze {
  public:
    SquareMaze();

    void makeMaze(int width1, int height1);

    bool canTravel(int x, int y, int dir) const;

    void setWall(int x, int y, int dir, bool exists);

    vector<int> solveMaze();

    PNG* drawMaze() const;

    PNG* drawMazeWithSolution();

    PNG* drawCreativeMaze();

    int width;
    int height;
    int vectorSize;
    vector<bool> rWall;
    vector<bool> dWall;

  private:

    void changePixel(HSLAPixel& pixel);

    void blackenP(HSLAPixel& pixel) const;

};
