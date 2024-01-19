#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

struct Node{
    int data;
    std::shared_ptr<Node> next;
};

class HashTable{
    std::shared_ptr<std::shared_ptr<Node>[]> Ht;
public:
    HashTable();
    HashTable(int size);
    int hash(int data) const{ return data % 10; }
    std::shared_ptr<Node> createNode(int data){
        auto curr = std::make_shared<Node>();
        curr->data = data;
        return curr;
    }
    void insert(int data);
    int search(int data);
    void disp();
    void del(int data);
};

HashTable::HashTable() : Ht(std::shared_ptr<std::shared_ptr<Node>[]>(new std::shared_ptr<Node>[10])){
    for(int i{0}; i < 10; i++)
        Ht[i] = std::make_shared<Node>();
}

HashTable::HashTable(int size) : Ht(std::shared_ptr<std::shared_ptr<Node>[]>(new std::shared_ptr<Node>[size])){
    for(int i{0}; i < size; i++)
        Ht[i] = std::make_shared<Node>();
}

void HashTable::insert(int data){
    int hIndx = hash(data);
    auto curr = createNode(data);

    if(Ht[hIndx] == nullptr) Ht[hIndx] = curr;
    else{
        auto temp = Ht[hIndx];
        auto helper = Ht[hIndx];

        while(temp && temp->data < data){
            helper = temp;
            temp = temp->next;
        }

        if(helper == Ht[hIndx] && helper->data > curr->data){
            curr->next = helper;
            Ht[hIndx] = curr;
        }
        else{
            curr->next = helper->next;
            helper->next = curr;
        }
    }
}

int HashTable::search(int data){
    int hIndx = hash(data);
    auto curr = Ht[hIndx];

    while(curr)
        if(curr->data == data)
            return curr->data;
        else
            curr = curr->next;
    return -1;
}

void HashTable::disp(){
    for(int i = 0; i < 10; i++){
        auto curr = Ht[i]->next;
        
        std::cout << "\n[ " << i << " ]->";
        while(curr){
            std::cout << "[ " << curr->data << " ]->";
            curr = curr->next;
        }
        std::cout << "x" << std::endl;
    }
}

void HashTable::del(int data){
    int hIndx = hash(data);
    auto helper = Ht[hIndx];
    auto curr = helper->next;

    while(curr->data != data){
        helper = curr;
        curr = curr->next;
    }

    if(curr->data == data){
        helper->next = curr->next;
        curr->next = nullptr;
        curr = nullptr;
    }
}

int main(){
    std::vector<int> vec{5,13,9,4,7,8,1,11,3,43,14,68,69,39};
    HashTable H;

    for(int i : vec)
        H.insert(i);

    H.disp();
    H.del(3);
    H.del(39);
    H.del(14);
    H.disp();
}