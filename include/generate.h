#ifndef GENERATE_H
#define GENERATE_H

#include <fstream>
#include <deque>
using namespace std;

class GeneratePair
{
private:
    deque<int> window;  // 滑动窗口
    ifstream data_file; // 数据文件

public:
    GeneratePair();              // 构造函数
    ~GeneratePair();             // 析构函数
    void fit(string input_file); // 外部接口
    void generate();             // 生成数据
};

#endif

// generate.h
