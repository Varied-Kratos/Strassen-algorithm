#include "Collector.h"
using namespace std;

void generate_matrix(int size, double min_val, double max_val){
    random_device rd;
    mt19937 gener(rd());
    uniform_real_distribution<double> number(min_val, max_val);

    ofstream a_mat("Matrix_A.txt");
    if (!a_mat.is_open()) {
            throw std::runtime_error("Не могу открыть файл: Matrix_A.txt");
    }
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            double curr_num = number(gener);
            a_mat << curr_num;
            if(j < size - 1){
                a_mat<<" ";
            }
        }
        a_mat<<"\n";
    }
    a_mat.close();

    ofstream b_mat("Matrix_B.txt");
    if (!b_mat.is_open()) {
            throw std::runtime_error("Не могу открыть файл: Matrix_B.txt");
    }
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            double curr_num = number(gener);
            b_mat << curr_num;
            if(j < size - 1){
                b_mat<<" ";
            }
        }
        b_mat<<"\n";
    }
    b_mat.close();
}

void Collector::move_data_from_queue(){
    for(int i = 0; i < 7; i++){
        pair<int, Matrix> result;
        bool success = queue_result.pop(result);

         if(!success){
            throw runtime_error("Неуспешное извлечение из очереди");
        }
            
        unique_lock<mutex> lock(res_mtx);
        table_matrix[result.first] = result.second;
        lock.unlock();
    }
}
Collector::Collector(BlockingQueue<pair<int, Matrix>>& queue): queue_result(queue){}
    
Matrix Collector::collect_all(){

    Collector::move_data_from_queue();
        
    if(table_matrix.size() < 7){
       throw runtime_error("Были получены не все данные");
    }
    Matrix M1 = table_matrix.at(1);
    Matrix M2 = table_matrix.at(2);
    Matrix M3 = table_matrix.at(3);
    Matrix M4 = table_matrix.at(4);
    Matrix M5 = table_matrix.at(5);
    Matrix M6 = table_matrix.at(6);
    Matrix M7 = table_matrix.at(7);
    Matrix C11 = M1 + M4 - M5 + M7;
    Matrix C12 =  M3 + M5;
    Matrix C21 =  M2 + M4;
    Matrix C22 = M1 - M2 + M3 + M6;
    return Matrix::combine(C11, C12, C21, C22);
}

void Collector::save_result(const Matrix& m){
    m.save("Result_matrix.txt");
}

void Collector::collector_function() {
    Matrix result = collect_all();
    save_result(result);
}