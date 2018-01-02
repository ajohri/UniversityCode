/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/** 
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */ 
AnagramDict::AnagramDict(const string& filename)
{
    string word;
    ifstream words(filename);

    // Checking if there is an open spot to put the sorted word in.
    if(words.is_open())
    {
    	for( int i = 0; getline(words, word); i++)
    	{
    		string sorted_word = word;
    		sort(sorted_word.begin(), sorted_word.end());
    		// auto takes on the type of what the right side of the = is.
    		auto lookup = dict.find(sorted_word);
    		if(lookup != dict.end())
    		{
    			(lookup -> second).push_back(word);
    		}
    		else
    		{
    			std::vector<string> all_words;
    			all_words.push_back(word);
    			// The hash function to put the two together
    			dict.insert(make_pair(sorted_word, all_words));
    		}
    	}
    }
}

/** 
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */ 
AnagramDict::AnagramDict(const vector< string >& words)
{
    // Going through each element in the words vector till we have visited each of the elements in words
    for (auto & word : words)
    {
    	// Temporary variable for each element that we are visiting
    	string sorted_word = word;
    	sort(sorted_word.begin(), sorted_word.end());
    	auto lookup = dict.find(sorted_word);
    	// Checking to make sure the final one isn't the same meaning that it has to be placed at the end of the of the vector.
    	// Same logic as above.
    	if(lookup != dict.end())
    	{
    		(lookup -> second).push_back(word);
    	}
    	else
    	{
    		std::vector<string> all_words;
    		all_words.push_back(word);
    		dict.insert(make_pair(sorted_word, all_words));
    	}
    }
}

/**
 * @param word The word to find anagrams of. 
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the 
 * word list.
 */
vector< string > AnagramDict::get_anagrams(const string& word) const
{
    string sorted_word = word;
    sort(sorted_word.begin(), sorted_word.end());
    auto lookup = dict.find(sorted_word);
    if(lookup != dict.end())
    {
    	return lookup -> second;
    }
    else
    {
    	return vector< string >();
    }
}       

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector< vector< string > > AnagramDict::get_all_anagrams() const
{
	auto lookup = dict.begin();
	std::vector<std::vector<string> > all_anagrams;
	while(lookup != dict.end())
	{
		if(!((lookup->second).size() < 2))
		{
			all_anagrams.push_back(lookup->second);
		}
		lookup++;
	}
    return all_anagrams;
}


