#ifndef COUNT_H
#define COUNT_H

#include <string>
#include <map>

class Count
{
private:
    std::string cache_path;
    size_t chunk_size;
    void count_frequencies_in_chunk(const std::string &file_path);
    void cleanup_temp_files();
    std::map<int, int> merge_temp_files();
    void write_results_to_file(const std::map<int, int> &final_frequency, const std::string &output_file_path);

public:
    Count(std::string cache_path, size_t chunk_size);
    void fit(std::string file_path, std::string output_file_path);
};

#endif // COUNT_H