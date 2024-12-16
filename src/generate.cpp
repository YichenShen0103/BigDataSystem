#include "generate.h"
#include <fstream>
#include <string>
#include <deque>
#include <iostream>
using namespace std;

GeneratePair::GeneratePair()
{
    window = deque<int>();
}

GeneratePair::~GeneratePair()
{
}

void GeneratePair::fit(string input_file)
{
    data_file = ifstream(input_file);
    if (!data_file.is_open())
    {
        cerr << "Failed to open sorted data file: ../data/sorted_data.txt" << endl;
        return;
    }
}

void GeneratePair::generate()
{
    if (!data_file.is_open())
    {
        cerr << "Data file is not open. Please call fit() first." << endl;
        return;
    }

    ofstream cache("../cache/pairs.txt");
    if (!cache.is_open())
    {
        cerr << "Failed to open output file: ../cache/pairs.txt" << endl;
        return;
    }

    int num;
    while (data_file >> num)
    {
        window.push_back(num);
        while (!window.empty() && window.back() - window.front() > 10)
            window.pop_front();
        for (int i = 0; window.back() - window[i] == 10; ++i)
            cache << window[i] << " " << window.back() << endl;
    }

    data_file.close();
    cache.close();

    ifstream pairs("../cache/pairs.txt");
    ofstream pairs_output("../data/output_pairs.txt");
    if (!pairs.is_open())
    {
        cerr << "Failed to open output file: ../cache/pairs.txt" << endl;
        return;
    }
    if (!pairs_output.is_open())
    {
        cerr << "Failed to open output file: ../data/output_pairs.txt" << endl;
        return;
    }

    int count = 0;
    string line;
    string prev = "";
    while (getline(pairs, line))
    {
        if (line == prev)
            ++count;
        else if (count > 0)
        {
            pairs_output << prev << " " << count << endl;
            count = 0;
        }
        prev = line;
    }
    if (count > 0)
        pairs_output << prev << " " << count << endl;
    pairs.close();
    pairs_output.close();
}
