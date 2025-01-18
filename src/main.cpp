#include "count.h"
#include "external_sort.h"
#include "generate.h"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <chunk_size>" << endl;
        return 1;
    }
    size_t chunk_size = stoll(argv[1]);

    string cache_path = "../cache";
    filesystem::create_directory("./data");
    Count Cnt = Count(cache_path, chunk_size);
    Cnt.fit("../data/data.txt", "../data/output_pairs.txt");
    cout << "Counting completed." << endl;
    // ExternalSort("../data/data.txt", chunk_size);
    // cout << "External sort completed." << endl;

    // ifstream data_file("../data/sorted_data.txt");
    // if (!data_file.is_open())
    // {
    // cerr << "Failed to open sorted data file: ../data/sorted_data.txt" << endl;
    // return 1;
    // }

    // GeneratePair GP = GeneratePair();
    // GP.fit("../data/sorted_data.txt");
    // GP.fit("../data/frequencies.txt");
    // GP.generate();

    filesystem::remove_all("../cache");
    filesystem::create_directory("../cache");
    return 0;
}