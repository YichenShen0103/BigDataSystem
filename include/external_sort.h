#ifndef EXTERNAL_SORT_H
#define EXTERNAL_SORT_H

#include <string>
#include <vector>
#include <fstream>
using namespace std;

class ExternalSort
{
private:
    ifstream data_file;                                            // 输入文件流
    long long chunk_size;                                          // 每个块的大小
    void sort_and_save_chunk(vector<int> &chunk, int chunk_index); // 排序并保存块
    void merge_chunks(int num_chunks, const string &output_file);  // 合并块

public:
    ExternalSort(string input_file, long long chunk_size); // 构造函数
    void exSort();                                         // 外部排序
};

#endif

// external_sort.h