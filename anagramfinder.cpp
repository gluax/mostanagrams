#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>

using namespace std;

void find_anagrams_no_sorting(unordered_map<int, vector<string>>& anagrams, ifstream& file) {
  unsigned char primes[26] = {5,71,79,19,2,83,31,43,11,53,37,23,41,3,13,73,101,17,29,7,59,47,61,97,89,67};
  string word = "";
  unsigned int word_value = 1;

  //while not end of file
  while (true) {
    file >> word;
    if (file.eof()) {
      return;
    }
    
    for(auto c : word) {
      word_value *= primes[tolower(c) - 'a']; 
    }

    if(word_value != 1) anagrams[word_value].push_back(word);
    word_value = 1;
  }
}

int main(int argc, char *argv[]) {
  
  if (argc != 2) {
    cerr << "Usage: ./anagramfinder <dictionary file>" << endl;
    return 1;
  }
  
  //create map of sorted characters in word to vector of the words
  unordered_map<int, vector<string>> anagrams;

  string fname(argv[1]);
  //open the file
  ifstream file(fname);
  if (!file) {
    cerr << "Error: File \'" << fname << "\' not found." << endl;
    return 1;
  }
  
  //grab all the anagrams
  find_anagrams_no_sorting(anagrams, file);


  if(anagrams.empty()) {
    cout << "No anagrams found." << endl;
    return 1;
  }
    
  //find the largest size
  //unsigned int largest_size = max_element(anagrams.begin(), anagrams.end(), [](const auto& a, const auto& b){return a.second.size() < b.second.size();})->second.size();
  unsigned int largest_size = 0, cur;
  
  vector<vector<string>> final;
  
  //for every key in map whose size is equal to the largest size in map
  for (auto key : anagrams) {
    cur = key.second.size();
    if (cur > largest_size) {
      largest_size = key.second.size();
      final.clear();
      final.push_back(key.second);
      continue;
    } else if(cur == largest_size) {
      final.push_back(key.second);
    }
  }

  if(largest_size < 2) {
    cout << "No anagrams found." << endl;
    return 1;
  }
  
  cout << "Max anagrams: " << largest_size << endl;
  final.size() > 1 ?
    sort(
         final.begin(),
         final.end(),
         [](auto &a, auto &b) {
           sort(a.begin(), a.end());
           sort(b.begin(), b.end());
           return a[0] < b[0];
         })
    : sort(final.front().begin(), final.front().end());
  for(auto vec : final) {
    for (auto word : vec) {
      cout << word << endl;
    }
    cout << endl;
  }
  
}
