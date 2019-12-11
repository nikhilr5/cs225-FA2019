#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>
using namespace std;

/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::numVertices() const {
  // TODO: Part 2
  return vertexMap.size();
}


/**
* The degree of the vertex. For directed: Sum of in-degree and out-degree
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
  return adjList.at(v.key()).size();

}


/**
* Inserts a Vertex into the Graph.
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
  // TODO: Part 2
  V & v = *(new V(key));
  pair<string, V_byRef> *add = new pair<string,V_byRef>(key,v);
  vertexMap.insert(*add);
  adjList[key] = std:: list<edgeListIter>();
  return v;
}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
  // TODO: Part 2

  for(auto it = edgeList.begin(); it != edgeList.end(); ++it) {
    Edge e = (*it);
    if ((e.source() == key || e.dest() == key)) {
      removeEdge(e.source(), e.dest());
    }
  }
  vertexMap.erase(key);


}


/**
* Inserts an Edge into the Graph.
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
  // TODO: Part 2
  E & e = *(new E(v1, v2));
  edgeListIter add = edgeList.insert(edgeList.begin(),e);
  list<edgeListIter> &listUno = adjList[v1.key()];
  list<edgeListIter> &listDos = adjList[v2.key()];
  listUno.push_back(add);
  listDos.push_back(add);

  return e;
}


/**
* Removes an Edge from the Graph. Consider both the undirected and directed cases.
* min(degree(key1), degree(key2))
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2) {
  edgeListIter i = edgeList.begin();
  while (i != edgeList.end()) {
    Edge e = *i;
    Vertex source = e.source();
    Vertex dest = e.dest();
    if (source.key() == key1 && dest.key() == key2) {
      removeEdge(i);
      return;
    }

    if (dest.key() == key1 && source.key() == key2) {
      if (e.directed()) {
        removeEdge(i);
        return;
      }
    }
    i++;
  }
}


/**
* Removes an Edge from the Graph given by the location of the given iterator into the edge list.
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
  Edge edge = *it;

  adjList.at(edge.source().key()).remove(it);
  adjList.at(edge.dest().key()).remove(it);

  edgeList.erase(it);
}


/**
* Return the list of incident edges from a given vertex.
* For the directed case, consider all edges that has the vertex as either a source or destination.
* @param key The key of the given vertex
* @return The list edges (by reference) that are adjacent to the given vertex
*/
template <class V, class E>
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {
  // TODO: Part 2
  std::list<std::reference_wrapper<E>> edges;
  for(edgeListIter i : adjList.at(key)) {
    edges.push_back(*i);
  }
  return edges;
}


/**
* Return whether the two vertices are adjacent to one another. Consider both the undirected and directed cases.
* When the graph is directed, v1 and v2 are only adjacent if there is an edge from v1 to v2.
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const {
  bool booler = false;
  unsigned long minListSize = std:: min(adjList.at(key1).size(), adjList.at(key2).size());
  if (minListSize == adjList.at(key1).size()) {
    for (edgeListIter e: adjList.at(key1)) {
      Vertex dest = (*e).get().dest();
      if (dest.key() == key2) {
        booler = true;
        break;
      }
    }
  } else{
    for (edgeListIter e : adjList.at(key2)) {
      //for undirected purposes
      Vertex source = (*e).get().source();
      if (source.key() == key1){
         booler = true;
         break;
       }
    }
  }
  return booler;
}
