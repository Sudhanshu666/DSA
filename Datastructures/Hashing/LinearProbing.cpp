#include <iostream>
#include <vector>
#include <algorithm>
#define SIZE 10

void disp(std::vector<int>& vec){
    std::cout << "\n[ ";
    for(int &i : vec)
        std::cout << i << " ";
    std::cout << "]" << std::endl;   
}

int hash(int data) {return data % SIZE; }

int linearProb(std::vector<int>& Ht, int idx){
    int i = 0;
    while(Ht[(idx + i) % SIZE] != 0) i++;
    return ((idx + i) % SIZE);
}

void insert(std::vector<int>& Ht, int data){
    int hIndx = hash(data);

    if(Ht[hIndx] != 0) hIndx = linearProb(Ht, hIndx);

    Ht[hIndx] = data;
}

int search(std::vector<int>& Ht, int data){
    int idx = hash(data), i = 0, res = -1;

    while(Ht[(idx + i) % SIZE] != data){
        i++;
        if(Ht[(idx + i) % SIZE] == 0) return -1;
    }
    
    res = (idx + i) % SIZE;
    return res;
}

int main(){
    std::vector<int> vec{26, 30, 45, 23, 25, 43, 74, 19, 29};
    std::vector<int> Ht(SIZE, 0);

    disp(vec);
    disp(Ht);

    for(int i : vec)
        insert(Ht, i);
    
    disp(Ht);
    
    int key;
    
    std::cin >> key;
    
    std::cout << "\nElement Found : " << Ht[search(Ht, key)] << std::endl;

    return 0;
}