#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <mutex>
using namespace std;

//getline(cin,s)
void add_multithread(int& num, std::mutex& m){
    std::lock_guard<std::mutex> lock(m);
    num += 1;
}

int main(){
    
    return 0;
}
