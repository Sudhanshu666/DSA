//Singly LL
#include <iostream>
#include <vector>
#include <memory>
#include <fstream>

template<typename T>
class Node{
    T data;
    std::shared_ptr<Node<T>> next;
public:
    std::shared_ptr<Node<T>> head;
    std::shared_ptr<Node<T>> last;
    
    void create(const std::vector<T>& vec);
    void insert(T data, int index);
    void remove(int index);
    void display() const;
    
    template<typename U>
    friend Node<U> operator+(const Node<U> &node1, const Node<U> &node2);
};

template<typename T>
Node<T> operator+(const Node<T> &node1, const Node<T> &node2){
    Node<T> res;
    std::vector<T> sum;
    
    auto curr1 = node1.head;
    auto curr2 = node2.head;
    
    while(curr1 && curr2){
        sum.push_back(curr1->data + curr2->data);
        curr1 = curr1->next;
        curr2 = curr2->next;
    }
    while(curr1){
        sum.push_back(curr1->data);
        curr1 = curr1->next;
    }
    while(curr2){
        sum.push_back(curr2->data);
        curr2 = curr2->next;
    }
    
    res.create(sum);
    return res;
}

template<typename T>
void Node<T>::create(const std::vector<T>& vec){
    for(const auto &i : vec){        
        auto curr = std::make_shared<Node<T>>();
        
        curr->data = i;        
        
        if(!head)
            head = last = curr;        
        else{
            last->next = curr;
            last = last->next;
        }        
        curr = nullptr;       
    }
}

template<typename T>
void Node<T>::display() const{
    auto curr = head;
    
    std::cout << std::endl;
    while(curr){
        std::cout << "[ " << curr->data << " ]-";
        curr = curr->next;
    }
    std::cout << "x" << std::endl; 
}

template<typename T>
void Node<T>::insert(T data, int index){
    auto curr = head;
    
    for(int i = 0; i < index - 2; i++)
        curr = curr->next;
        
    auto curr2 = std::make_shared<Node<T>>();
    curr2 ->data = data;

    if(index == 1){
        curr2->next = head;
        head = curr2;
    }
    else{
        curr2->next = curr->next;
        curr->next = curr2;
        
        if(curr == last)
            last = curr2;
    }
    
    std::cout << "\nInsertion successful." << std::endl;
    
    curr = nullptr;
    curr2 = nullptr;
    
}

template<typename T>
void Node<T>::remove(int index){
    auto curr = head;
    
    for(int i = 0; i < index - 2; i++)
        curr = curr->next;
        
    if(index == 1){
        head = head->next;
        curr->next = nullptr;
        curr = nullptr;
    }
    else{
        auto temp = curr->next;
        curr->next = temp->next;
        if(!temp->next)
            last = curr;
        else
            temp->next = nullptr;
        temp = nullptr;
    }
    
    std::cout << "\nDeletion Sucessful!." << std::endl;
    
    curr = nullptr;
}

void basic(){
    std::vector<int> nums = {5,9,3,7};
    Node<int> N;
    
    N.create(nums);
    N.display();  

    N.insert(1, 3);
    N.display();
    
    N.insert(6, 1);
    N.display();
    
    N.insert(2, 2);
    N.display();
    
    N.insert(4, 8);
    N.display();
    
    N.insert(0, 8);
    N.display();
    
    N.remove(5);
    N.display();
    
    N.remove(1);
    N.display();
    
    N.remove(2);
    N.display();
    
    N.remove(6);
    N.display();
    
    N.remove(4);
    N.display();
    
    
}

void stringop(){
    std::vector<std::string> str = {"Sam", "Jim", "Rina", "Ali", "Maya"};
    
    Node<std::string> N;
    
    N.create(str);
    N.display();
    
    N.insert("Sudhanshu", 3);
    N.insert("Aditi", 3);
    N.display();
}

void arith(){
    std::vector<int> vec1 = {8,3,9,7,2,4};
    std::vector<int> vec2 = {2,4,3,1,8,7,1,6};
    Node<int> N1;
    Node<int> N2;
    Node<int> N3;
    
    N1.create(vec1);
    N2.create(vec2);
    
    N3 = N1 + N2;
    
    N1.display();
    N2.display();
    N3.display();
}

int main(){
    //basic();
    //stringop();
    arith();
    
    return 0;
}
