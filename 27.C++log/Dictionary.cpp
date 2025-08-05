#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Record {
    string _word;
    int _frequency;
    bool operator<(const Record& other) const {
        return _word < other._word;
    }
};

class Dictionary {
public:
    void read(const std::string &filename);
    void store(const std::string &filename);
    vector<Record> & getDict (){
        return _dict;
    }
private:
    vector<Record> _dict;
    void addWord(const std::string &word);
};

void Dictionary::read(const std::string &filename) {
    ifstream fileStream(filename);
    if (!fileStream.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }
    // Count total number of lines in the file
    fileStream.seekg(0, ios::end);
    streampos fileSize = fileStream.tellg();
    fileStream.seekg(0, ios::beg);
    string line;
    size_t totalLines = 0;
    while (getline(fileStream, line)) {
        ++totalLines;
    }
    fileStream.clear(); // Clear the end-of-file flag
    fileStream.seekg(0, ios::beg); // Rewind to the beginning of the file
    size_t currentLine = 0;
    
    cout << totalLines << endl;
    while (getline(fileStream, line)) {
        istringstream iss(line);
        string word;
        while (iss >> word) {
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            addWord(word);
        }
        ++ currentLine;
        printf("%03ld%% \r", 100 * currentLine / totalLines);
    }
    fflush(stdout);
    fileStream.close();
}

void Dictionary::store(const std::string &filename) {
    ofstream fileOut(filename);
    if (!fileOut.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }
    for (const auto &record : _dict) {
        fileOut << record._word << " " << record._frequency << endl;
    }

    fileOut.close();
}

void Dictionary::addWord(const std::string &word) {
    if (word.empty()) return;

    if(!_dict.empty()){
        auto it = _dict.begin();
        do{
            if(it != _dict.end() && it->_word == word){
                ++(it->_frequency);
                return ;
            }
            ++ it;
        }while(it != _dict.end());
    }
    _dict.push_back({word, 1});
}
bool compareByFrequency(const Record& a, const Record& b) {
    if (a._frequency == b._frequency) {
        return a._word < b._word; 
    }
    return a._frequency > b._frequency; 
}
int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    Dictionary dict;
    dict.read(argv[1]);
    sort(dict.getDict().begin(), dict.getDict().end(), compareByFrequency);
    dict.store("dict.txt");
    cout << "Word frequency dictionary has been created." << endl;
    return 0;
}
