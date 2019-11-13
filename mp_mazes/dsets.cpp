#include "dsets.h"

using namespace std;

void DisjointSets:: addelements(int num) {
  for (int i = 0; i < num; i++) {
    vectorData.push_back(-1);
  }
}

int DisjointSets:: find(int elem) {
  if( vectorData[elem] < 0) { return elem;}
  else {
    //sets the elem to point at root (compression)
    vectorData[elem] = find(vectorData[elem]);
    return vectorData[elem];
  }
}

void DisjointSets:: setunion(int a, int b) {
  int root1 = find(a);
  int root2 = find(b);
  int newSize = vectorData[root1] + vectorData[root2];

  if (root1 < root2) {
    vectorData[root2] = root1;
    vectorData[root1] = newSize;
  } else {
    vectorData[root1] = root2;
    vectorData[root2] = newSize;
  }
}

int DisjointSets:: size(int elem) {
  int answer = find(elem);
  return -vectorData[answer];
}
