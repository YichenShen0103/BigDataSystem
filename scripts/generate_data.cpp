#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <fstream>
#include <random>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

// 全局变量用于文件写入锁
mutex file_mutex;

// 每个线程执行的任务：生成数据并写入文件
void generate_data(long long start, long long end, long long max_size, const string &filename)
{
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<long long> dis(0, max_size);

    ofstream data_file(filename, ios::app); // 以追加模式打开文件

    if (!data_file.is_open())
    {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }

    for (long long i = start; i < end; i++)
    {
        // 每次写入时加锁，保证线程安全
        lock_guard<mutex> lock(file_mutex);
        data_file << dis(gen) << endl;
    }

    // 自动关闭文件，当函数退出时
}

// 主函数：将任务分配到多个线程
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <max_size>" << endl;
        return 1;
    }

    long long max_size = stoll(argv[1]);
    string filename = "../data/data.txt";

    // 创建目标文件夹（如果不存在）
    filesystem::create_directory("../data");

    // 计算分割的任务数量和每个线程的工作量
    int num_threads = 4; // 线程数
    vector<thread> threads;
    long long chunk_size = max_size / num_threads; // 每个线程处理的元素数量

    // 创建线程，每个线程负责生成一部分数据
    for (int i = 0; i < num_threads; i++)
    {
        long long start = i * chunk_size;
        long long end = (i == num_threads - 1) ? max_size : start + chunk_size;

        threads.push_back(thread(generate_data, start, end, max_size, filename));
    }

    // 等待所有线程完成
    for (auto &t : threads)
    {
        t.join();
    }

    cout << "Data generation completed!" << endl;
    return 0;
}
