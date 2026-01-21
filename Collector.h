#ifndef COLLECTOR_H
#define COLLECTOR_H
#include <iostream>
#include <random>
#include <fstream>
#include <unordered_map>
#include "BlockingQueue.h"
#include "matrix.h"
#include <mutex>
#include <string>
using namespace std;

void generate_matrix(int size, double min_val, double max_val);

class Collector{
private:
    BlockingQueue<pair<int, Matrix>>& queue_result;
    unordered_map<int, Matrix> table_matrix;
    mutex res_mtx;
    
    void move_data_from_queue();
public:
    explicit Collector(BlockingQueue<pair<int, Matrix>>& queue);
    Matrix collect_all();
    void save_result(const Matrix& m);
    void collector_function();
};
#endif