#include <iostream>
#include <algorithm>
#include <vector>
#define SIZE 10
#define PRIME 7

void display(std::vector<int>& nums){
    std::cout << "\n[ ";
    for(int &i : nums)
        std::cout << i << " ";
    std::cout << "]" << std::endl;
}

int hash(int key) {return key % SIZE; }
int primeHash(int key) {return PRIME - (key % PRIME); }

int doubleHash(std::vector<int>& HT, int key){
    int idx = hash(key), i = 0;
    
    while(HT[(idx + i * primeHash(key)) % SIZE] != 0) i++;
    
    return (idx + i * primeHash(key)) % SIZE;
}

void insert(std::vector<int>& HT, int key){
    int idx = hash(key);
    
    if(HT[idx] != 0) idx = doubleHash(HT, key);

    HT[idx] = key;
}

int search(std::vector<int>& HT, int key){
    int idx = hash(key), i = 0;
    
    while(HT[(idx + i * primeHash(key)) % SIZE] != key){
        i++;
        if(HT[(idx + i * primeHash(key)) % SIZE] == 0) return -1;
    }
    
    return (idx + i * primeHash(key)) % SIZE;
    
}

int main(){
    std::vector<int> vec{5,25,15,35,95};
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
