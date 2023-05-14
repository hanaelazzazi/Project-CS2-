#include "plg.h"

using namespace std;

plg::plg(){}


plg::~plg() {
    numOfLines = -1;
    //fileName = "";
    //filePath = "";
    lines.clear();
    sentences.clear();
    //percent = -1;
}






void plg::detect(string p,string name) {
    vector<string> file2 = getsentences(p);


    //int counter = 0;
    for (int i = 0; i < sentences.size(); i++) {
        double max = 0;
        bool flag = false;
        double n=0;

        for (int j = 0; j < file2.size(); j++) {
            
            bool z = compare(sentences[i], file2[j], n);
            if (n > max)max = n;
            if (z == true)flag = true;
        }

        if (flag == true) {
            linePlg y;
            y.index = i+1;
            y.file = name;
            y.percentage = max;

            insert(y);
        }
    }


}


void plg::detectML(string p, string name) {
    


    //pass the the two file paths to the ML string matching function
    //return percentage and save it in percent
    
    
        /*cout << " Sending arguments to python notebook \n";
    string path("C:/Users/youss/OneDrive/Desktop/python proj/string matching.ipynb");
    string CMD("jupyter nbconvert --execute" + path + sntc1 + sntc2);
    system(CMD.c_str());
    cout << " Done Sending arguments to python notebook \n";


    ifstream myfile; myfile.open("C:/Users/youss/OneDrive/Desktop/python proj/output-AI.txt");
    string z;
    myfile >> z;

    cout << " Done reading from output of python \n";
    cout << z << "\n";*/
}


void plg::insert(linePlg s) {
    bool flag = false;
    for (int i = 0; i < lines.size()&&flag==false; i++) {
        if (lines[i].index == s.index) {
            flag = true;
            if (s.percentage > lines[i].percentage) {
                lines[i] = s;
            }
        }
    }

    if (flag == false) {
        lines.push_back(s);
    }
}

vector<string> plg::getsentences(string path) {
    ifstream x;
    x.open(path);

    string test = "?.!";

    int words, chars, lines;

    Filelength(path, chars, words, lines);

    vector<string> res;
    int counter = 0;

    string line = "";
    char c;

    for (int i = 0; i < chars; i++) {
        x.get(c);
        if (charOcc(test, c)) {
            line = line + " ";
            res.push_back(line);
            line = "";
            counter++;
        }
        else line = line + c;
        
    }
    return res;
}


vector<string> plg::getparagraphs(string path) {
    
    ifstream infile(path);
    string line;
    vector<string> paragraphs;
    string currentParagraph;

    while (std::getline(infile, line)) {
        if (line.empty()) {  // Empty line indicates end of paragraph
            if (!currentParagraph.empty()) {  // End of current paragraph
                paragraphs.push_back(currentParagraph);
                currentParagraph.clear();
            }
        }
        else {
            if (!currentParagraph.empty()) {
                currentParagraph += "\n";
            }
            currentParagraph += line;
        }
    }

    // If the file does not end with an empty line, the last paragraph may not have been added
    if (!currentParagraph.empty()) {
        paragraphs.push_back(currentParagraph);
    }

    return paragraphs;


}



bool  plg::compare(string sntc1, string sntc2,double &x) {
    double count = 0;
    vector<string> box = split_sentence(sntc1);

    for (int i = 0; i < box.size(); i++) {
         double x = rabinKarp(box[i], sntc2);
        double y = bruteForce(box[i], sntc2);

        double avg = (x + y) / 2;
        count += avg;
    }

    double prcnt = (count / box.size())*100;

    if (prcnt >= 65) {
        x = prcnt;
        return true; }
    else return false;
}




int plg::rabinKarp(string word, string sentence) {
    to_lower(word);
    to_lower(sentence);

    vector<string> words = split_sentence(sentence);
    int n = words.size();
    int m = word.size();
    long long p_pow = 1;
    long long word_hash = 0;

    // compute hash for the word
    for (int i = 0; i < m; i++) {
        word_hash = (word_hash + (word[i] - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }

    // check if there is a match
    for (int i = 0; i < n; i++) {
        long long sentence_hash = 0;
        string current_word = words[i];
        int current_word_size = current_word.size();

        // compute hash for the current word in the sentence
        if (current_word_size >= m) {
            for (int j = 0; j < m; j++) {
                sentence_hash = (sentence_hash + (current_word[j] - 'a' + 1) * p_pow) % m;
                p_pow = (p_pow * p) % m;
            }
        }

        // check if there is a match
        if (word_hash == sentence_hash && current_word == word) {
            return 1;
        }

        // compute hash for the next substring of length m
        for (int j = m; j < current_word_size; j++) {
            sentence_hash = (p * (sentence_hash - (current_word[j - m] - 'a' + 1) * p_pow) + (current_word[j] - 'a' + 1)) % m;
            if (sentence_hash < 0) sentence_hash += m;
            if (word_hash == sentence_hash && current_word.substr(j - m + 1, m) == word) {
                return 1;
            }
        }
    }
    return 0;
}








int plg::bruteForce(string word, string str) {
    to_lower(word);
    to_lower(str);

    string test = ".,>< !@#$%^&*()}{[];'\\/?~+-=";

    int strLen = str.length();
    int wordLen = word.length();
    int result = false;
    for (int i = 0; i <= strLen - wordLen; i++) {
        if (str[i] == word[0] && (charOcc(test, str[i + wordLen]) || i + wordLen == strLen)) {
            bool flag = true;
            int j = 1;
            for (j = 1; j < wordLen; j++) {
                if (str[i + j] != word[j]) {
                    flag = false;

                }
            }
            if (flag == true) {
                result = true;

            }
        }
    }
    if (result == true) {
        return 1;
    }
    else {
        return 0;
    }
}




vector<string> plg::split_sentence(string sentence) {
    vector<string> words;
    stringstream ss(sentence);
    string word;
    while (ss >> word) {
        words.push_back(word);
    }
    return words;
}




void plg::to_lower(string& x) {
    for (int i = 0; i < x.length(); i++) {
        x[i] = tolower(x[i]);
    }
}


bool plg::charOcc(string str, char c) {
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == c) {
            return true;
        }
    }
    return false;
}


int plg::percentage() {
    int sum = 0;
    for (int i = 0; i < lines.size(); i++) {
        sum += lines[i].percentage;
    }

    return sum / numOfLines;
}





void plg::Filelength(string p,int & characters,int & words ,int & sentences ) {
    ifstream x;
    x.open(p);
    if (!x.is_open() || x.fail()) {
        
        cout << "file not opened"<<endl;
    }
    else {
        string test = "!?.";

        characters = 0;
        words = 0;
        sentences = 0;


        char c;
        while (!x.eof()) {
            x.get(c);
            if (charOcc(test, c)) {
                sentences++;
            }
            if (c == ' ') {
                words++;
            }
            characters++;
        }
        x.close();

    }
}





void plg::sortLines() {


    for (int i = 0; i < lines.size();i++) {
        int minIndex = i;
        for (int j = i+1; j < lines.size(); j++) {
            if (lines[j].index < lines[minIndex].index) {
                minIndex = j;
            }
        }

        linePlg box = lines[minIndex];
        lines[minIndex] = lines[i];
        lines[i] = box;

    }
}




void plg::printLines(string& x)
{
    x = "";

    for (int i = 0; i < lines.size(); i++) {
    string y = "Line number " +to_string(lines[i].index) + " is plagiarized from " + lines[i].file + " file by " + to_string(lines[i].percentage) + "%.";

    x = x + y + "\n";
    }
}



void plg::printAIlines(string& x)
{
    x = "";

    for (int i = 0; i < lines.size(); i++) {
        string y = "paragraph number" + to_string(lines[i].index) + " is probably written by AI ";

        x = x + y + "\n";
    }
}



