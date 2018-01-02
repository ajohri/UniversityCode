/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of "StringTriples" (a typedef'd std::tuple, see top of 
 * cartalk_puzzle.h). Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector< StringTriple > cartalk_puzzle(PronounceDict d,
                                      const string& word_list_fname)
{
    StringTriple base_triple;
    std::vector<StringTriple> base_total;
    ifstream words(word_list_fname);
    string first_word;
    string second_word;
    string word;
    if(words.is_open())
    {
    	while(getline(words,word))
    	{
    		if(word.size() > 1)
    		{
    			second_word = word[0] + word.substr(2, word.size());
    			first_word = word.substr(1, word.size());

    			if(d.homophones(first_word, word) && d.homophones(second_word, word))
    			{
    				base_triple = make_tuple(first_word, word, second_word);
    				base_total.push_back(base_triple);
    			}
    		}
    	}
    }
    return base_total;
}


