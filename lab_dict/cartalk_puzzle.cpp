/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>
#include <iostream>
#include <vector>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    ifstream wordsFile(word_list_fname);
    string word;
    if (wordsFile.is_open()) {
    /* Reads a line from `wordsFile` into `word` until the file ends. */
    while (getline(wordsFile, word)) {
        string firstLetterRemoved = word.substr(1);
        string secondLetterRemoved = word.substr(0,1) + word.substr(2);
        bool a = d.homophones(firstLetterRemoved, secondLetterRemoved);
        bool b = d.homophones(word, firstLetterRemoved);

        if (a || b) {
          ret.push_back(make_tuple(word, firstLetterRemoved, secondLetterRemoved));
        }
    }
}


    /* Your code goes here! */
    return ret;
}
