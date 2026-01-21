#include <iostream>
#include <thread>
#include <chrono>
#include "BlockingQueue.h"
#include "matrix.h"
#include "Producer.h"
#include "Consumer.h"
#include "Collector.h"

using namespace std;

int main() {
    try {       
        int size; 
        cout << "Введите размер матрицы"<<endl;
        cin >> size;
        const int THREADS = 4;
        generate_matrix(size, 1.0, 5.0);

        Matrix A, B;
        A.load("Matrix_A.txt");
        B.load("Matrix_B.txt");
        
        BlockingQueue<Task> taskQueue(10);
        BlockingQueue<pair<int, Matrix>> resultQueue(10);
        Producer producer(taskQueue);
        Consumer consumer(taskQueue, resultQueue, THREADS);
        Collector collector(resultQueue);

        consumer.start();          
        producer.generateFirstLevelTasks(A, B);        
        taskQueue.close();        
        consumer.join();        
        resultQueue.close();
        collector.collector_function();        
    } 
    catch (const exception& e) {
        cout << "Ошибка" << endl;
    }
    return 0;
}