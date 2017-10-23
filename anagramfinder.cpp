#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>

using namespace std;

void find_anagrams(map<string, vector<string>>& anagrams, ifstream& file) {
  string word, converted;
  string sorted_word;
  
  //while not end of file
  while (true) {
    if (file.eof()) {
      return;
    }
    
    //grab the word
    file >> word;

    //word parsing here?
    //or do I want the original word not stripped of unwanted characters?
    for(auto c : word) {
      if(!isalpha(c)) continue;
      converted += tolower(c);
    }
    
    //copy word to keep copy
    sorted_word = converted;
    
    //idea #2 instead of sorting maybe assign value of primes to each letter
    //its faster to mathmatically calc a value instead of sorting a string I think
    sort(sorted_word.begin(), sorted_word.end());
    
    //map the sorted letters to the vector and  push back the word to the vector
    anagrams[sorted_word].push_back(word);
    converted = "";
  }
}

void find_anagrams_no_sorting(map<int, vector<string>>& anagrams, ifstream& file) {
  unsigned char primes[26] = {5,71,79,19,2,83,31,43,11,53,37,23,41,3,13,73,101,17,29,7,59,47,61,97,89,67};
  string word;
  unsigned int word_value = 1;
  
  //while not end of file
  while (true) {
    if (file.eof()) {
      return;
    }
    
    //grab the word
    file >> word;

    for(auto c : word) {
      word_value *= primes[tolower(c) - 'a']; 
    }
    
    anagrams[word_value].push_back(word);
    word_value = 1;
  }
}

int main(int argc, char *argv[]) {
  //default file name
  string fname = "dictionary.txt";

  //if they specified a different file
  if (argc > 1) {
    fname = argv[1];
  }

  //create map of sorted characters in word to vector of the words
  //maybe map to pair of vector, # of words
  map<int, vector<string>> anagrams;
  
  //open the file
  //maybe mmap? Don't think there's a need to if every line only contains a single word
  ifstream file(fname);
  if (!file) {
    cerr << "Could not open file" << endl;
    return 1;
  }

  //grab all the anagrams
  find_anagrams_no_sorting(anagrams, file);

  //find the largest size but then we traverse it twice...
  //once to find largest size second to see which have the largest size
  //maybe change function to keep vector of highest seen numbers?
  //that's probably bad because then I search highest number every time instead of once at the end
  unsigned int largest_size = max_element(anagrams.begin(), anagrams.end(), [](const auto& a, const auto& b){return a.second.size() < b.second.size();})->second.size();

  cout << "Max anagrams: " << largest_size << endl;
  //for every key in map whose size is equal to the largest size in map
  for (auto key : anagrams) {
    if (key.second.size() == largest_size) {
      
      //print every word in that list
      sort(key.second.begin(), key.second.end());
      for (auto word : key.second) {
	cout << word << endl;
      }
      cout << endl;
    }
  }
}
