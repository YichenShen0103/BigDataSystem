#ifndef COUNT_H
#define COUNT_H

#include <string>
#include <map>
using namespace std;

class Count
{
private:
    string cache_path;                                        // 临时文件夹路径
    size_t chunk_size;                                        // 每个块的大小
    void count_frequencies_in_chunk(const string &file_path); // 计算块中的频率
    void cleanup_temp_files();                                // 清理临时文件
    map<int, int> merge_temp_files();                         // 合并临时文件
    void write_results_to_file(const map<int, int> &final_frequency,
                               const string &output_file_path); // 将结果写入文件

public:
    Count(string cache_path, size_t chunk_size);         // 构造函数
    void fit(string file_path, string output_file_path); // 计算频率
};

#endif // COUNT_H