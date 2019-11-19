#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    SquareMaze maze;
    maze.makeMaze(100,100);
    PNG* mazePNG = maze.drawCreativeMaze();
    mazePNG->writeToFile("creative.png");
    return 0;
}
