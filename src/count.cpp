#include "count.h"
#include <iostream>
#include <deque>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

// 分块读取文件并统计频度
void Count::count_frequencies_in_chunk(const std::string &file_path)
{
    std::ifstream input_file(file_path);
    if (!input_file)
    {
        std::cerr << "Error: Unable to open input file." << std::endl;
        return;
    }

    if (!fs::exists(cache_path))
    {
        fs::create_directory(cache_path);
    }

    std::map<int, int> frequency_map;
    std::string line;
    size_t chunk_count = 0;

    while (std::getline(input_file, line))
    {
        int number = std::stoi(line);
        frequency_map[number]++;

        // 如果当前块达到指定大小，写入临时文件
        if (frequency_map.size() >= chunk_size)
        {
            std::ofstream temp_file(cache_path + "/chunk_" + std::to_string(chunk_count) + ".txt");
            for (const auto &pair : frequency_map)
                temp_file << pair.first << " " << pair.second << "\n";
            temp_file.close();
            frequency_map.clear();
            chunk_count++;
        }
    }

    // 写入最后一个块
    if (!frequency_map.empty())
    {
        std::ofstream temp_file(cache_path + "/chunk_" + std::to_string(chunk_count) + ".txt");
        for (const auto &pair : frequency_map)
            temp_file << pair.first << " " << pair.second << "\n";
        temp_file.close();
    }

    input_file.close();
}

// 合并临时文件
std::map<int, int> Count::merge_temp_files()
{
    std::map<int, int> final_frequency;

    for (const auto &entry : fs::directory_iterator(cache_path))
    {
        std::ifstream temp_file(entry.path());
        std::string line;

        while (std::getline(temp_file, line))
        {
            size_t space_pos = line.find(' ');
            int number = std::stoi(line.substr(0, space_pos));
            int count = std::stoi(line.substr(space_pos + 1));
            final_frequency[number] += count;
        }

        temp_file.close();
    }

    return final_frequency;
}

// 清理临时文件
void Count::cleanup_temp_files()
{
    for (const auto &entry : fs::directory_iterator(cache_path))
        fs::remove(entry.path());
}

void Count::fit(std::string file_path, std::string output_file_path)
{
    count_frequencies_in_chunk(file_path);
    auto final_frequency = merge_temp_files();
    cleanup_temp_files();
    // write_results_to_file(final_frequency, output_file_path);

    std::deque<int> window;
    std::ofstream output(output_file_path);
    for (const auto &pair : final_frequency)
    {
        window.push_back(pair.first);
        while (!window.empty() && window.back() - window.front() > 10)
            window.pop_front();
        if (window.back() - window.front() == 10)
            output << "( " << window.front() << ", " << window.back() << " ) "
                   << final_frequency[window.front()] * final_frequency[window.back()] << "\n";
    }
    output.close();
}

void Count::write_results_to_file(const std::map<int, int> &final_frequency, const std::string &output_file_path)
{
    std::ofstream output_file(output_file_path);
    if (!output_file)
    {
        std::cerr << "Error: Unable to open output file." << std::endl;
        return;
    }

    for (const auto &pair : final_frequency)
        output_file << pair.first << " " << pair.second << "\n";

    output_file.close();
}

Count::Count(std::string cache_path, size_t chunk_size) : cache_path(cache_path), chunk_size(chunk_size)
{
    std::filesystem::create_directory(cache_path);
}