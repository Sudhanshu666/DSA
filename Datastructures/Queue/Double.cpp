#include <iostream>
#include <memory>
#include <vector>

template<typename T>
class Queue{
    std::shared_ptr<Queue<T>> prev;
    T data;
    std::shared_ptr<Queue<T>> next;
public:
    std::shared_ptr<Queue<T>> front;
    std::shared_ptr<Queue<T>> rear;
    
    void dequeue();
    void enqueue(T data);
    
    void display();  
};

template<typename T>
void Queue<T>::enqueue(T data){
    auto curr = std::make_shared<Queue<T>>();
    curr->data = data;
        
    if(!front)
        front = rear = curr;
    else{
        rear->next = curr;
        curr->prev = rear;
        rear = rear->next;
    }
    curr = nullptr;
}

template<typename T>
void Queue<T>::dequeue(){
    if(front){
        auto curr = front;
        
        front = front->next;
        front->prev = nullptr;
        curr->next = nullptr;
        
        curr = nullptr;
    }
    else
        std::cout << "\n[ERROR]: Queue is empty." << std::endl;
}

template<typename T>
void Queue<T>::display(){
    if(front){
        auto curr = front;
        
        std::cout << "\n";
        while(curr){
            std::cout << "[ " << curr->data << " ]<->";
            curr = curr->next;
        }
        std::cout << "x" << std::endl;
    }
    else
        std::cout << "\n[ERROR]: Queue is empty." << std::endl;
}

void basic(){
    Queue<int> q;
    
    q.enqueue(5);
    q.enqueue(3);
    q.enqueue(7);
    q.enqueue(9);
    q.enqueue(2);
    q.enqueue(6);
    q.display();
    
    
    q.dequeue();
    q.dequeue();
    q.dequeue();
    q.dequeue();
    
    q.display();
}

template<typename T>
Queue<T> enqueue(const std::vector<T> &vec){
    Queue<T> obj;
    for(const auto &i : vec)
        obj.enqueue(i);
        
    return obj;
}

template<typename T>
void dequeue(Queue<T> &obj, int count){
    for(int i = 0; i < count; ++i)
        obj.dequeue();   
}

void ad(){
    std::vector<int> v1{4,6,8,7,3};   
    auto i = enqueue(v1);    
    i.display();
    
    dequeue(i, 3);
    i.display();
    
    std::vector<std::string> names{"Alex", "Sofia", "Martin", "Karl", "Jess", "Marie"};
    auto it = enqueue(names);
    it.display();    
    
    dequeue(it,2);
    it.display();
}

int main(){
    ad();
    //basic();
    
    return 0;
}