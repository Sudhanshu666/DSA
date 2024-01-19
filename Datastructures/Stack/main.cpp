//Stack
#include <iostream>
#include <vector>
#include <memory>

template<typename T>
class Node{
    T data;
    std::shared_ptr<Node<T>> next;
public:
    std::shared_ptr<Node<T>> top;
    
    void pushMul(std::vector<T> &vec);
    void push(T data);
    T pop();
    void display() const;
};

template<typename T>
void Node<T>::push(T data){
    auto curr = std::make_shared<Node<T>>();
    
    curr->data = data;
    curr->next = top;
    top = curr;
    
    curr = nullptr;
}

template<typename T>
void Node<T>::pushMul(std::vector<T> &vec){
    for(auto &i : vec)
        push(i);
}

template<typename T>
T Node<T>::pop(){
    T data;
    
    auto curr = top;
    top = top->next;
    curr->next = nullptr;
    data = curr->data;
    curr = nullptr;
    
    return data;    
}

template<typename T>
void Node<T>::display() const{
    auto curr = top;
    
    std::cout << std::endl;
    while(curr){
        std::cout << "[ " << curr->data << " ]" << std::endl;
        curr = curr->next;
    }    
}

void basic(){
    std::vector<int> vec = {5,9,3,7};
    Node<int> N;
    
    N.pushMul(vec);
    N.display();
    
    N.push(1);
    N.display();
    
    std::cout << "\n " << N.pop() << " Popped out." << std::endl;
    std::cout << "\n " << N.pop() << " Popped out." << std::endl;
    std::cout << "\n " << N.pop() << " Popped out." << std::endl;
    
    N.display();
}

int main(){
    basic();
    
    return 0;
}