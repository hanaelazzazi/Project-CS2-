#include "plagirism.h"







plagirism::~plagirism() {
    percent = -1;
    fileName = "";
    filePath = "";

    numOfLines = -1;
    lines.clear();
    sentences.clear();
}




plagirism::plagirism() {}





void plagirism::basic(string name, string path) {
    fileName = name;
    filePath = path;
    Filelength(path, numOfchar, numOfWords, numOfLines);
    sentences = getsentences(path);
    int ln = Db.getNumFields();

    for (int i = 0; i < ln; i++) {
        string n;
        string p;

        Db.select(i + 1, n, p);

        detect(p, n);
    }
    percent = percentage();

    Db.insertfile(name, path);

    sortLines();

}



void plagirism::AIdetection(string path) {
    
    Filelength(path, numOfchar, numOfWords, numOfLines);

    paragraphs = getparagraphs(path);

    numOfParagraphs = paragraphs.size();

    for (int i = 0; i < numOfParagraphs; i++) {
        bool x = false;

        //delete alll file

        //put in the file the input

        //command to run the python notebook

        //read from the file

        //put paragraphs[i] in the function save returned value in x
        
        if (x == true) {
            linePlg test;
            test.index = i + 1;
            lines.push_back(test);
        }
    }


    percent = lines.size() / numOfParagraphs;


}



void plagirism::prefered(string name, string path) {
    fileName = name;
    filePath = path;
    Filelength(path, numOfchar, numOfWords, numOfLines);
    int ln = Db.getNumFields();

    for (int i = 0; i < ln; i++) {
        string n;
        string p;

        Db.select(i + 1, n, p);

        detectML(p, n);
    }
    percent = percentage();

    Db.insertfile(name, path);

}



void plagirism::code(string file1, string file2) {
    ifstream f1(file1), f2(file2);
    string str1((std::istreambuf_iterator<char>(f1)),
        istreambuf_iterator<char>());
    string str2((std::istreambuf_iterator<char>(f2)),
        istreambuf_iterator<char>());

    // Convert both strings to lowercase for case-insensitive comparison
    transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
    transform(str2.begin(), str2.end(), str2.begin(), ::tolower);

    const size_t len1 = str1.length(), len2 = str2.length();
    const size_t maxLen = std::max(len1, len2);
     

    // Compute the Levenshtein distance between the two strings
    std::vector<std::vector<size_t>> dist(len1 + 1, std::vector<size_t>(len2 + 1, 0));
    for (size_t i = 1; i <= len1; ++i) dist[i][0] = i;
    for (size_t j = 1; j <= len2; ++j) dist[0][j] = j;
    for (size_t j = 1; j <= len2; ++j) {
        for (size_t i = 1; i <= len1; ++i) {
            const size_t cost = (str1[i - 1] == str2[j - 1]) ? 0 : 1;
            dist[i][j] = std::min(std::min(dist[i - 1][j] + 1, dist[i][j - 1] + 1),
                dist[i - 1][j - 1] + cost);
        }
    }

    // Compute the similarity percentage
    const double similarity = 100.0 * (1 - static_cast<double>(dist[len1][len2]) / maxLen);
    percent = similarity;
}



float plagirism::getpercent() {
    return percent;
}
