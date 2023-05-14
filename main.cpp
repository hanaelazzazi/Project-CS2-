#include <cstring>
#include <cmath>
#include <stdio.h>
#include <sqlite3.h>
#include <string>
#include <cctype>
#include <sstream>
#include <vector>
#include "plg.h"
#include <iostream>
#include "plagirism.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

    int main() {
     
        string y;
        plagirism x;

        x.basic("Test2", "/Users/hanaelazzazi/Desktop/Spring 2023/CS 2/Project and Paper/Sample Documents /TXT/Test2.txt");
        cout <<"The plagiarism percent is: "<<x.getpercent() << "%."<<endl;
        cout<<endl;
        x.printLines(y);
        cout << y << endl;



    }


