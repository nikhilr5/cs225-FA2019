#include <queue>
#include <algorithm>
#include <string>
#include <list>

/**
 * Returns an std::list of vertex keys that creates any shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 *
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 *
 * You should use undirected edges. Hint: There are no edge weights in the Graph.
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
  unordered_map<string, string> mappers;
  queue<string> q;

  q.push(start);
  mappers.insert({start, start});

  while(!q.empty()) {
    string s = q.front();
    q.pop();
    list<std::reference_wrapper<E>> neighbors = incidentEdges(s);

    for (Edge & e: neighbors) {
      bool visit = false;
      bool visit2 = false;
      if (mappers.find(e.dest().key()) == mappers.end()) visit = true;
      if (mappers.find(e.source().key())== mappers.end()) visit2 = true;


      if (visit) {
        q.push(e.dest().key());
        mappers.insert({e.dest().key(), e.source().key()});
        if(e.dest().key() == end ) {
          // std::cout<< "reach end DEST" << std::endl;
          break;
        }
      }

      if(visit2) {
        q.push(e.source().key());
        mappers.insert({e.source().key(),e.dest().key()});
        if (e.source().key()== end) {
          // std::cout<< "reach end SOURCE" << std::endl;
          break;
        }
      }

    }
  }
  list<std:: string> path;
  string node = end;
  while(node != start) {
    path.push_front(node);
    string parent = mappers.at(node);
    node = parent;
  }
  path.push_front(start);
  return path;
}


// template <class V, class E>
// std::list<std::string> Graph<V,E>::pathFinder(unordered_map<string, string> map, string end, string start) {
//   list<std:: string> path;
//   string node = end;
//   while(node != start) {
//     path.push_front(node);
//     string parent = map.at(node);
//     node = parent;
//   }
//   path.push_front(start);
//   return path;
//
// }
