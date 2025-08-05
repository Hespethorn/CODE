#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Record {
    char _letter;
    int _frequency;
    bool operator<(const Record& other) const {
        return _letter < other._letter;
    }
};

class Dictionary {
public:
    void read(const std::string &filename);
    void store(const std::string &filename);
    vector<Record> &getDict() {
        return _dict;
    }

private:
    vector<Record> _dict;
    void addLetter(char letter);
};

void Dictionary::read(const std::string &filename) {
    ifstream fileStream(filename);
    if (!fileStream.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }

    // Count total number of characters in the file
    fileStream.seekg(0, ios::end);
    streampos fileSize = fileStream.tellg();
    fileStream.seekg(0, ios::beg);

    char ch;
    size_t totalChars = 0;
    while (fileStream.get(ch)) {
        ++totalChars;
    }
    fileStream.clear(); // Clear the end-of-file flag
    fileStream.seekg(0, ios::beg); // Rewind to the beginning of the file

    size_t currentChar = 0;
    while (fileStream.get(ch)) {
        if (isalpha(ch)) { // Consider only alphabetic characters
            ch = tolower(ch); // Convert to lowercase
            addLetter(ch);
        }
        ++currentChar;
        printf("%02ld \r", 100 * currentChar / totalChars);
    }
    fileStream.close();
}

void Dictionary::store(const std::string &filename) {
    ofstream fileOut(filename);
    if (!fileOut.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }
    for (const auto &record : _dict) {
        fileOut << record._letter << " " << record._frequency << endl;
    }
    fileOut.close();
}

void Dictionary::addLetter(char letter) {
    auto it = find_if(_dict.begin(), _dict.end(), [&letter](const Record& r) { return r._letter == letter; });
    if (it != _dict.end()) {
        ++(it->_frequency);
    } else {
        _dict.push_back({letter, 1});
    }
}
bool compareByFrequency(const Record& a, const Record& b) {
    if (a._frequency == b._frequency) {
        return a._letter < b._letter; // If frequencies are equal, sort by letter
    }
    return a._frequency > b._frequency; // Sort by frequency in descending order
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    Dictionary dict;
    dict.read(argv[1]);
    sort(dict.getDict().begin(), dict.getDict().end(), compareByFrequency);
    dict.store("char_freq.txt");
    cout << "\nCharacter frequency dictionary has been created." << endl;
    return 0;
}
