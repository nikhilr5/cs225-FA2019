
/* Your code here! */
#include <vector>
#include "maze.h"
#include <iostream>
#include <map>
#include <queue>
#include <sys/time.h>

using namespace std;


SquareMaze:: SquareMaze() {}

void SquareMaze:: makeMaze(int width1, int height1) {
  width = width1;
  height = height1;
  vectorSize = width * height;
  DisjointSets groups;
  groups.addelements(vectorSize);
  //no cells are in same set
  for (int i = 0; i < vectorSize; i++) {
    rWall.push_back(true);
    dWall.push_back(true);
  }
  int x,y;

  while (groups.size(0) < vectorSize ) {
    x = rand() % width;
    y = rand() % height;

    if (rand() % 2 == 1 && x != width - 1) {
        if (groups.find(y * width + x) != groups.find(y* width + x +1)) {
          setWall(x,y,0,false);
          groups.setunion(y * width + x, y * width + x + 1);
        }
    } else {
      if (y != height - 1) {
          if (groups.find(y * width + x) != groups.find(y * width + x + width)) {
            setWall(x,y, 1, false);
            groups.setunion(y * width + x, y * width + x + width);

          }
      }

    }

  }
}


bool SquareMaze:: canTravel(int x, int y, int dir) const{
  if (dir == 0) {
    return !rWall[y * width + x];
  } else if (dir == 1) {
    return !dWall[y * width + x];
  } else if (dir == 2) {
    return ((x != 0) && (!rWall[y * width + x - 1]));
  } else if (dir == 3) {
    return ((y != 0) && (!dWall[(y -1)* width + x]));
  }

  return false;
}


void SquareMaze:: setWall(int x, int y, int dir, bool exist) {
  if (dir == 0) {
    rWall[y * width + x] = exist;
  } else if (dir == 1 ) {
    dWall[y * width + x] = exist;
  }
}


vector<int> SquareMaze:: solveMaze() {
  vector<int> row;

  std::map<int, int> map;
  vector<bool> visited;

  //set up vector
  for (int i = 0; i < vectorSize; i++) {
    visited.push_back(false);
}
    queue<int> q;
    //the start
    q.push(0);
    visited[0] = true;
    while (!q.empty()) {
      int num = q.front();
      q.pop();

      // to traverse through vectors
      int x = num % width;
      int y = num / width;

      if (y == height - 1 ) {
        row.push_back(num);
      }

      // can travel different directions if no wall exists and haven't visited before
      if (canTravel(x,y,0) && !visited[num + 1]) {
        visited[num + 1 ] = true;
        map[num + 1] = num;
        q.push(num+ 1);
      }
      if (canTravel(x,y,1) && !visited[num + width]) {
        visited[num + width ] = true;
        map[num + width] = num;
        q.push(num+ width);
      }
      if (canTravel(x,y,2) && !visited[num - 1]) {
        visited[num - 1 ] = true;
        map[num -1] = num;
        q.push(num- 1);
      }
      if (canTravel(x,y,3) && !visited[num - width]) {
        visited[num - width ] = true;
        map[num - width] =num;
        q.push(num- width);
      }
    }

    vector<int> returnVec;
    int begin = row[width - 1];

    //creates a vector that tells you what direction to move
    while(begin != 0) {
      //using map
      int a = map[begin];

      if (begin == a+1) returnVec.push_back(0);
      else if (begin == a + width) returnVec.push_back(1);
      else if (begin == a -1) returnVec.push_back(2);
      else if (begin == a - width) returnVec.push_back(3);
      //next
      begin = a;
    }
    //flip vector to start path from origin
    reverse(returnVec.begin(), returnVec.end());
    return returnVec;
}


PNG* SquareMaze:: drawMaze() const {
  int pngWidth = width * 10 + 1;
  int pngHeight = height * 10 + 1;
  PNG* returnPNG = new PNG(pngWidth, pngHeight);

  for (int i = 0; i < pngHeight; i++) {
    blackenP(returnPNG->getPixel(0,i));

  }
  for (int i = 10; i < pngWidth; i++) {
     blackenP(returnPNG->getPixel(i,0));
  }

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      if (rWall[y * width + x]) {
        for (int k = 0; k < 11; k++) {
          blackenP(returnPNG->getPixel((x+1)*10,y*10+k));
        }
      }

      if (dWall[y * width + x]) {
        for (int k = 0; k < 11; k++) {
          blackenP(returnPNG->getPixel(x*10+k, (y+1)*10));
        }
      }
    }
  }

  return returnPNG;
}



PNG* SquareMaze:: drawMazeWithSolution() {
  PNG* returnPNG = drawMaze();
  vector<int> path = solveMaze();

  //starts at (5,5)
  int x = 5;
  int y = 5;

  for (size_t i = 0; i < path.size(); i++) {
    if (path[i] == 0) {
      for (int k = 0; k < 10; k++) {
        changePixel(returnPNG->getPixel(x,y));
        x+= 1;
      }

    } else if (path[i] == 1) {
      for (int k = 0; k < 10; k++) {
        changePixel(returnPNG->getPixel(x,y));
        y+=1;
      }

    } else if (path[i] == 2) {
      for (int k = 0; k < 10; k++) {
        changePixel(returnPNG->getPixel(x,y));
        x-=1;
      }

    } else if (path[i] == 3) {
      for (int k = 0; k < 10; k++) {
        changePixel(returnPNG->getPixel(x,y));
        y-=1;
      }

    }
  }

  changePixel(returnPNG->getPixel(x,y));
  //undo
  x = x - 4;
  y = y + 5;


  //whitten bottom wall 1-9
  for (int i = 0; i < 9; i++) {
    HSLAPixel& pixel = returnPNG->getPixel(x,y);
    pixel.l = 1;
    pixel.a = 1;
    pixel.h = 0;
    pixel.s =1;
    x+= 1;
  }


  return returnPNG;
}

//helper functions
void SquareMaze::changePixel(HSLAPixel& pixel) {
  pixel.h = 0;
  pixel.s = 1;
  pixel.a = 1;
  pixel.l = 0.5;
}

void SquareMaze:: blackenP(HSLAPixel& pixel) const{
  pixel.l = 0;
}


PNG* SquareMaze:: drawCreativeMaze() {
  int pngWidth = width * 10 + 1;
  int pngHeight = height * 10 + 1;

  PNG* returnPNG = new PNG(pngWidth, pngHeight);

  for(int x = 0; x < width; x++){
   for(int y = 0; y < height / 3; y++){
         if(rWall[y * width+ x]){
           for(int k = 0; k < 11; k++) {
             HSLAPixel& pixel = returnPNG->getPixel((x+1)*10,y*10+k);
             pixel.h = 309;
             pixel.l = 0.5;
             pixel.s = 1;
           }
         }
         if(dWall[y * width + x]){
           for(int k = 0; k < 11; k++){
            blackenP(returnPNG->getPixel(x*10+k, (y+1)*10));
           }
         }
       }
     }

  for(int x = width / 2 ; x < width; x++){
    for(int y = height / 3; y < height; y++){
      if(rWall[y * width+ x]){
        for(int k = 0; k <= 10; k++){
          blackenP(returnPNG->getPixel((x+1)*10,y*10+k));
        }
      }
      if(dWall[y * width + x]){
        for(int k = 0; k <= 10; k++){
          HSLAPixel& pixel = returnPNG->getPixel(x*10+k, (y+1)*10);
          pixel.h = 20;
          pixel.s = 1;
          pixel.l = .5;
        }
      }
    }
  }


return returnPNG;
}
