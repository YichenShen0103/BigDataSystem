#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <fstream>
#include <random>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

void generate_data(long long start, long long end, const string &filename)
{
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<long long> dis(0, 1e6);

    ofstream data_file(filename); // 以追加模式打开文件

    if (!data_file.is_open())
    {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }

    for (long long i = start; i < end; i++)
    {
        data_file << dis(gen) << endl;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <max_size>" << endl;
        return 1;
    }

    long long max_size = stoll(argv[1]);
    string filename = "./data/data.txt";

    // 创建目标文件夹（如果不存在）
    filesystem::create_directory("./data");
    generate_data(0, max_size, filename);

    cout << "Data generation completed!" << endl;
    return 0;
}
