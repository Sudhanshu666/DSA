#include <iostream>
#include <algorithm>
#include <vector>
#define SIZE 10

void display(std::vector<int>& nums){
    std::cout << "\n[ ";
    for(int &i : nums)
        std::cout << i << " ";
    std::cout << "]" << std::endl;
}

int hash(int key) {return key % SIZE; }

int quadProb(std::vector<int>& HT, int key){
    int idx = hash(key), i = 0;
    
    while(HT[(idx + i * i) % SIZE] != 0) i++;
    
    return (idx + i * i) % SIZE;
}

void insert(std::vector<int>& HT, int key){
    int idx = hash(key);
    
    if(HT[idx] != 0) idx = quadProb(HT, key);

    HT[idx] = key;
}

int search(std::vector<int>& HT, int key){
    int idx = hash(key), i = 0;
    
    while(HT[(idx + i * i) % SIZE] != key){
        i++;
        if(HT[(idx + i * i) % SIZE] == 0) return -1;
    }
    
    return (idx + i * i) % SIZE;
    
}

int main(){
    std::vector<int> vec{23,43,13,27};
    std::vector<int> HT(10, 0);   

    display(vec);
    display(HT);

    for(int i : vec)
        insert(HT, i);
    
    display(HT);
    
    int key;
    
    std::cin >> key;
    
    std::cout << "\nElement Found : " << HT[search(HT, key)] << std::endl;
    
    return 0;
}
