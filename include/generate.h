#ifndef GENERATE_H
#define GENERATE_H

#include <fstream>
#include <deque>
using namespace std;

class GeneratePair
{
private:
    deque<int> window;
    ifstream data_file;

public:
    GeneratePair();
    ~GeneratePair();
    void fit(string input_file);
    void generate();
};

#endif

// generate.h
