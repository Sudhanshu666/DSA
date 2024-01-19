//Singly LL Circular
#include <iostream>
#include <vector>
#include <memory>

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
};

template<typename T>
void Node<T>::create(const std::vector<T>& vec){
    for(const auto &i : vec){        
        auto curr = std::make_shared<Node<T>>();        
        curr->data = i;        
        
        if(!head){
            head = curr;
            curr->next = head;
            last = curr;
        }
        else{
            last->next = curr;
            last = last->next;
            last->next = head;
        }        
        curr = nullptr;       
    }
}

template<typename T>
void Node<T>::display() const{
    auto curr = head;
    
    std::cout << std::endl;
    std::cout << ">-";
    do{
        std::cout << "[ " << curr->data << " ]-";
        curr = curr->next;
    }while(curr != head);
    std::cout << "<" << std::endl; 
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
        last->next = head;
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
        last->next = head;
    }
    else{
        auto temp = curr->next;
        curr->next = temp->next;
        if(temp == last)
            last = curr;
        
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

int main(){
    basic();    
    
    return 0;
}
