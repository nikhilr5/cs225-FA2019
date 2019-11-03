/**
 * @file schashtable.cpp
 * Implementation of the SCHashTable class.
 */

using namespace hashes;

using std::pair;

using std:: list;

#include "schashtable.h"

template <class K, class V>
SCHashTable<K, V>::SCHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new std::list<std::pair<K, V>>[size];
    elems = 0;
}

template <class K, class V>
SCHashTable<K, V>::~SCHashTable()
{
    delete[] table;
}

template <class K, class V>
SCHashTable<K, V> const& SCHashTable<K, V>::
operator=(SCHashTable<K, V> const& rhs)
{
    if (this != &rhs) {
        delete[] table;
        table = new std::list<std::pair<K, V>>[rhs.size];
        for (size_t i = 0; i < rhs.size; i++)
            table[i] = rhs.table[i];
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
SCHashTable<K, V>::SCHashTable(SCHashTable<K, V> const& other)
{
    table = new std::list<std::pair<K, V>>[other.size];
    for (size_t i = 0; i < other.size; i++)
        table[i] = other.table[i];
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void SCHashTable<K, V>::insert(K const& key, V const& value)
{
  unsigned int hash1 = hash(key,size);
  pair <K,V> addPair(key,value);

  table[hash1].push_front(addPair);

  elems++;

  if(shouldResize()) {
    resizeTable();
  }
}

template <class K, class V>
void SCHashTable<K, V>::remove(K const& key)
{
    unsigned int hash1 = hash(key,size);

    for (typename std::list< pair<K,V> >::iterator it = table[hash1].begin();
          it != table[hash1].end(); ++it) {
            if (it->first == key) {
              table[hash1].erase(it);
              break;
            }
          }

}

template <class K, class V>
V SCHashTable<K, V>::find(K const& key) const
{
  unsigned hash1 = hash(key, size);
  for (typename list< pair<K,V> >::iterator it = table[hash1].begin();
        it != table[hash1].end(); ++it) {
          // it->first gets you first thing of pair (key)
          if(it->first == key) {
            return it->second;
          }
        }
    return V();
}


template <class K, class V>
V& SCHashTable<K, V>::operator[](K const& key)
{
    size_t idx = hashes::hash(key, size);

    typename std::list<std::pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return it->second;
    }

    // was not found, insert a default-constructed version and return it
    ++elems;
    if (shouldResize())
        resizeTable();

    idx = hashes::hash(key, size);
    std::pair<K, V> p(key, V());
    table[idx].push_front(p);
    return table[idx].front().second;
}

template <class K, class V>
bool SCHashTable<K, V>::keyExists(K const& key) const
{
    size_t idx = hashes::hash(key, size);
    typename std::list<std::pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return true;
    }
    return false;
}

template <class K, class V>
void SCHashTable<K, V>::clear()
{
    delete[] table;
    table = new std::list<std::pair<K, V>>[17];
    size = 17;
    elems = 0;
}

template <class K, class V>
void SCHashTable<K, V>::resizeTable()
{

    /**
     * @todo Implement this function.
     *
     * Please read the note in the spec about list iterators!
     * The size of the table should be the closest prime to size * 2.
     *
     * @hint Use findPrime()!
     */
     size_t newSize = findPrime(2 * size);
     std::list<std::pair<K, V>>* table2 = new list<pair<K,V>>[newSize];
     for (size_t i = 0; i < size; i++) {
       for (typename list< pair<K,V> >::iterator it = table[i].begin();
            it != table[i].end(); ++it) {
              //shift everything to newTable
              size_t hash1 = hash(it->first, newSize);
              std::pair<K,V> pair2(it->first, it->second);
              table2[hash1].push_front(pair2);
         }
       }
       size = newSize;
       delete[] table;
       table = table2;
}
