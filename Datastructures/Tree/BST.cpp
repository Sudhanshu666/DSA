#include <iostream>
#include <memory>

template<typename T>
struct Node{
    std::shared_ptr<Node<T>> lchild;
    T data;
    std::shared_ptr<Node<T>> rchild;
};

template<typename T>
class Tree{
    std::shared_ptr<Node<T>> root;
    std::shared_ptr<Node<T>> helper;
public:
    Tree(T data) : root(std::make_shared<Node<T>>()){
        root->data = data;
    }
    std::shared_ptr<Node<T>> getRoot() const {return root;}
    std::shared_ptr<Node<T>> createNode(T data);
    int inline height(std::shared_ptr<Node<T>> curr){
        return (curr) ? height(curr->lchild) > height(curr->rchild) ? height(curr->lchild) + 1 : height(curr->rchild) + 1 : 0;
    }
    std::shared_ptr<Node<T>> search(std::shared_ptr<Node<T>> curr, T data){
        if(curr){
            helper = curr;
            return (curr->data == data) ? curr : (curr->data < data) ? search(curr->rchild, data) : search(curr->lchild, data);
        }
        return nullptr;
    }
    bool inline insert(std::shared_ptr<Node<T>> root, std::shared_ptr<Node<T>> curr){
        return ((search(root, curr->data))) ? false : ((helper->data < curr->data) ? (helper->rchild = curr) : (helper->lchild = curr), true);
    }
    void insert(T data){
        if(insert(getRoot(), createNode(data)))
            std::cout << "\nNode " << data << " is added." << std::endl;
        else
            std::cout << "\nNode " << data << " addition failed." << std::endl;
    }
    std::shared_ptr<Node<T>> inPre(std::shared_ptr<Node<T>> curr){
        while(curr && curr->rchild)
            curr = curr->rchild;
        return curr;
    }
    std::shared_ptr<Node<T>> inSuc(std::shared_ptr<Node<T>> curr){
        while(curr && curr->lchild)
            curr = curr->lchild;
        return curr;
    }
    bool deleteNode(std::shared_ptr<Node<T>>& root, T data);
    void deleteNode(T data){
        if(deleteNode(root, data))
            std::cout << "\nNode " << data << " is deleted." << std::endl;
        else
            std::cout << "\nNode " << data << " deletion failed." << std::endl;
    }
    
    void preorderDisplay(std::shared_ptr<Node<T>> curr);
    void inorderDisplay(std::shared_ptr<Node<T>> curr);
    void postorderDisplay(std::shared_ptr<Node<T>> curr);
};

template<typename T>
std::shared_ptr<Node<T>> Tree<T>::createNode(T data){
    auto curr = std::make_shared<Node<T>>();
    curr->data = data;
    return curr;
}

template<typename T>
bool Tree<T>::deleteNode(std::shared_ptr<Node<T>>& root, T data){
    if(!root) return false;

    if(root->data == data){
        if(!root->lchild) root = root->rchild;
        else if(!root->rchild) root = root->lchild;
        else{
            if(height(root->lchild) > height(root->rchild)){
                auto pre = inPre(root->lchild);
                root->data = pre->data;
                deleteNode(root->lchild, pre->data);
            }
            else{
                auto suc = inSuc(root->rchild);
                root->data = suc->data;
                deleteNode(root->rchild, suc->data);
            }    
        }
        return true;
    }

    return (root->data < data) ? deleteNode(root->rchild, data) : deleteNode(root->lchild, data);
}


template<typename T>
void Tree<T>::preorderDisplay(std::shared_ptr<Node<T>> curr){
    if(curr){
        std::cout << curr->data << ", ";
        preorderDisplay(curr->lchild);
        preorderDisplay(curr->rchild);
    }
}

template<typename T>
void Tree<T>::inorderDisplay(std::shared_ptr<Node<T>> curr){
    if(curr){
        inorderDisplay(curr->lchild);
        std::cout << curr->data << ", ";
        inorderDisplay(curr->rchild);
    }
}

template<typename T>
void Tree<T>::postorderDisplay(std::shared_ptr<Node<T>> curr){
    if(curr){
        postorderDisplay(curr->lchild);
        postorderDisplay(curr->rchild);
        std::cout << curr->data << ", ";
    }
}

void basic(){
    Tree<int> t(30);

    t.insert(30);   
    t.insert(20);   
    t.insert(40);   
    t.insert(10);   
    t.insert(25);   
    t.insert(35);   
    t.insert(50); 
    t.insert(5);

    std::cout << "\nPreorder: " ;
    t.preorderDisplay(t.getRoot());
    std::cout << std::endl;
    
    std::cout << "\nInorder: " ;
    t.inorderDisplay(t.getRoot());
    std::cout << std::endl;
    
    std::cout << "\nPostorder: " ;
    t.postorderDisplay(t.getRoot());  
    std::cout << std::endl;

    t.deleteNode(30);   

    std::cout << "\nPreorder: " ;
    t.preorderDisplay(t.getRoot());
    std::cout << std::endl;
    
    std::cout << "\nInorder: " ;
    t.inorderDisplay(t.getRoot());
    std::cout << std::endl;
    
    std::cout << "\nPostorder: " ;
    t.postorderDisplay(t.getRoot());  
    std::cout << std::endl;
}

int main(){
    basic();
    return 0;
}