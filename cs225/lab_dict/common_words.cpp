/**
 * @file common_words.cpp
 * Implementation of the CommonWords class.
 *
 * @author Zach Widder
 * @date Fall 2014
 */

#include "common_words.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;
using std::feof;

string remove_punct(const string& str) 
{
    string ret;
    std::remove_copy_if(str.begin(), str.end(), 
                        std::back_inserter(ret),
                        std::ptr_fun< int, int >(&std::ispunct));
    return ret;
}

/**
 * Constructs a CommonWords object from a vector of filenames. 
 * file_word_maps is a vector of maps, where each element of the vector represents a different file,
 * and the map hashes a word in the file to the number of time that word has been seen.
 * common is a map of words in all files that hashes to how many files it appeared in.
 * @param filenames The vector of strings where the strings are the filenames to read in.
 */
CommonWords::CommonWords(const vector<string>& filenames)
{
    // initialize all member variables
    init_file_word_maps(filenames);
    init_common();
}

/**
 * Initializes common, mapping a word to the number of documents it shows up in.
 */
void CommonWords::init_common() 
{
    for (size_t i = 0; i < file_word_maps.size(); i++)
    {
        map <string, unsigned int> map_in_use = file_word_maps[i];
        for( auto & key_value : map_in_use)
        {
            if(common.find(key_value.first) != common.end())
            {
                common.find(key_value.first) -> second++;
            }
            else
            {
                common.insert( std::pair<string, unsigned int>(key_value.first, 1));
            }
        }
    }
}

/**
 * Initializes file_word_maps, having each index hold a map going from the word 
 * seen in that file to the number of times the word has been seen
 * @param filenames The vector of names of the files that will be used
 */
void CommonWords::init_file_word_maps(const vector<string>& filenames) 
{
    // vector is equal to number of files given
    file_word_maps.resize(filenames.size());

    // go through all files
    for(size_t i = 0; i < filenames.size(); i++) 
    {
        // get the corresponding vector of words that represents the current file
        vector<string> words = file_to_vector(filenames[i]);
        for(size_t j = 0; j < words.size(); j++)
        {
            // If the word is in the map
            if(file_word_maps[i].find(words[j]) != file_word_maps[i].end())
            {
                file_word_maps[i].find(words[j]) -> second++;
            }
            else
            {
                file_word_maps[i].insert(std::pair<string, unsigned int>(words[j], 1));
            }
        }
        /* Your code goes here! */
    }
}

/**
 * @param n The number of times to word has to appear.
 * @return A vector of strings. Vector contains all words that appear in all
 * files >= n times. I.e. the word must appear in all files more than 
 * n times.
 */
vector< string > CommonWords::get_common_words(unsigned int n) const
{
    /* Your code goes here! */
    vector<string> out;
    unsigned int total = 0;
    for( auto & key_value : common)
    {
        if(key_value.second == file_word_maps.size())
        {
            total = file_word_maps[1].find(key_value.first) -> second;
            for( auto & second_key_value : file_word_maps )
            {
                if(second_key_value.find(key_value.first) -> second < total)
                {
                    total = second_key_value.find(key_value.first) -> second;
                }
            }
        }

        if( total >= n )
        {
            out.push_back(key_value.first);
        }
        total = 0;
    }
    return out;
}

/**
 * Takes a filename and transforms it to a vector of all words in that file.
 * @param filename The name of the file that will fill the vector
 */
vector< string > CommonWords::file_to_vector(const string& filename) const {
    ifstream words(filename);
    vector<string> out;

    if(words.is_open()) {
        std::istream_iterator<std::string> word_iter(words);
        while(!words.eof()) {
            out.push_back(remove_punct(*word_iter));
            ++word_iter;
        }
    }
    return out;
}
