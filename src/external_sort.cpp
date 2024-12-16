#include "external_sort.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>
#include <string>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

void ExternalSort::sort_and_save_chunk(vector<int> &chunk, int chunk_index)
{
    sort(chunk.begin(), chunk.end());
    ofstream chunk_file("../cache/chunk_" + to_string(chunk_index) + ".txt");
    if (!chunk_file.is_open())
    {
        cerr << "Failed to open chunk file: ../cache/chunk_" << chunk_index << ".txt" << endl;
        return;
    }
    for (int num : chunk)
        chunk_file << num << " ";
    chunk_file.close();
}

void ExternalSort::merge_chunks(int num_chunks, const string &output_file)
{
    auto compare = [](pair<int, ifstream *> &a, pair<int, ifstream *> &b)
    {
        return a.first > b.first;
    };
    priority_queue<pair<int, ifstream *>, vector<pair<int, ifstream *>>, decltype(compare)> min_heap(compare);

    vector<ifstream *> chunk_files(num_chunks);
    for (int i = 0; i < num_chunks; ++i)
    {
        chunk_files[i] = new ifstream("../cache/chunk_" + to_string(i) + ".txt");
        if (!chunk_files[i]->is_open())
        {
            cerr << "Failed to open chunk file: ../cache/chunk_" << i << ".txt" << endl;
            return;
        }
        int num;
        if (*chunk_files[i] >> num)
            min_heap.push({num, chunk_files[i]});
    }

    ofstream output(output_file);
    if (!output.is_open())
    {
        cerr << "Failed to open output file: " << output_file << endl;
        return;
    }

    while (!min_heap.empty())
    {
        auto [num, file] = min_heap.top();
        min_heap.pop();
        output << num << endl;
        if (*file >> num)
            min_heap.push({num, file});
    }

    for (auto file : chunk_files)
    {
        file->close();
        delete file;
    }
}

void ExternalSort::exSort()
{
    fs::remove_all("../cache");
    fs::create_directory("../cache");

    vector<int> chunk;
    int num, chunk_index = 0;

    while (data_file >> num)
    {
        chunk.push_back(num);
        if (chunk.size() == chunk_size)
        {
            sort_and_save_chunk(chunk, chunk_index++);
            chunk.clear();
        }
    }
    if (!chunk.empty())
        sort_and_save_chunk(chunk, chunk_index);
    data_file.close();

    merge_chunks(chunk_index, "../data/sorted_data.txt");
}

ExternalSort::ExternalSort(string input_file, long long chunk_size) : chunk_size(chunk_size)
{
    data_file = ifstream(input_file);
    if (!data_file.is_open())
    {
        cerr << "Failed to open data file: ../data/data.txt" << endl;
        return;
    }
    exSort();
}
