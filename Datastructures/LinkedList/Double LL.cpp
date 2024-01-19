//Doubly LL
#include <iostream>
#include <vector>
#include <memory>

template<typename T>
class Node{
    std::shared_ptr<Node<T>> prev;
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
        
        if(!head)
            head = last = curr;        
        else{
            last->next = curr;
            curr->prev = last;
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
        std::cout << "[ " << curr->data << " ]<->";
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
        head->prev = curr2;
        head = curr2;        
    }
    else{
        curr2->next = curr->next;
        curr->next = curr2;
        curr2->prev = curr;
        if(curr2->next){
            curr = curr2->next;
            curr->prev = curr2;            
        }
        
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
        head->prev = nullptr;
        curr->next = nullptr;
        curr = nullptr;        
    }
    else{
        auto temp = curr->next;
        curr->next = temp->next;            
            
        if(!temp->next)
            last = curr;
        else{
            temp->next->prev = curr;
            temp->next = nullptr;            
        }
        
        temp->prev = nullptr;        
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
