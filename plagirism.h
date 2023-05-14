
#ifndef plagirism_H
#define plagirism_H



#pragma once



#include "plg.h"
#include <algorithm>
using namespace std;

class plagirism :
    public plg
{
private:
    string filePath;
    string fileName;

    float percent;

public:

    plagirism();
    ~plagirism();


    float getpercent();

    void AIdetection(string);

    void basic(string, string);

    void prefered(string, string);

    void code(string, string);//paths




};

#endif
