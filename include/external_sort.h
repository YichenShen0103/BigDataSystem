#ifndef EXTERNAL_SORT_H
#define EXTERNAL_SORT_H

#include <string>
#include <vector>
#include <fstream>
using namespace std;

class ExternalSort
{
private:
    ifstream data_file;
    long long chunk_size;
    void sort_and_save_chunk(vector<int> &chunk, int chunk_index);
    void merge_chunks(int num_chunks, const string &output_file);

public:
    ExternalSort(string input_file, long long chunk_size);
    void exSort();
};

#endif

// external_sort.h