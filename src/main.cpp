#include "external_sort.h"
#include "generate.h"
#include <iostream>
#include <fstream>
#include <filesystem>
using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <chunk_size>" << endl;
        return 1;
    }
    long long chunk_size = stoll(argv[1]);
    ExternalSort("../data/data.txt", chunk_size);
    ifstream data_file("../data/sorted_data.txt");
    if (!data_file.is_open())
    {
        cerr << "Failed to open sorted data file: ../data/sorted_data.txt" << endl;
        return 1;
    }
    GeneratePair GP = GeneratePair();
    GP.fit("../data/sorted_data.txt");
    GP.generate();

    filesystem::remove_all("../cache");
    filesystem::create_directory("../cache");
    return 0;
}