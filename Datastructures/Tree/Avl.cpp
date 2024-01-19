#include <iostream>
#include <memory>

template<typename T>
struct Node{
    std::shared_ptr<Node<T>> lchild;
    T data;
    std::shared_ptr<Node<T>> rchild;
    int height;
};

template<typename T>
class Avl{
    std::shared_ptr<Node<T>> root;
    std::shared_ptr<Node<T>> helper;
public:
    Avl(T data) : root(std::make_shared<Node<T>>()){
        root->data = data;
        root->height = 1;
    }
    std::shared_ptr<Node<T>> createNode(T data){
        auto curr = std::make_shared<Node<T>>();
        curr->data = data;
        curr->height = 1;
        return curr;
    }
    std::shared_ptr<Node<T>> getRoot() const { return root; }
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
    bool insert(std::shared_ptr<Node<T>> root, std::shared_ptr<Node<T>> curr){
        if(search(root, curr->data))
            return false;
        (helper->data < curr->data) ? helper->rchild = curr : helper->lchild = curr;

        root->height = height(root);
        helper->height = height(helper);

        isValid(root);
        return true;        
    }
    int inline balanceFactor(std::shared_ptr<Node<T>> curr){
        return (curr) ? height(curr->lchild) - height(curr->rchild) : 0;
    }
    void llRotation(std::shared_ptr<Node<T>> curr);
    void lrRotation(std::shared_ptr<Node<T>> curr);
    void rrRotation(std::shared_ptr<Node<T>> curr);
    void rlRotation(std::shared_ptr<Node<T>> curr);
    void isValid(std::shared_ptr<Node<T>> curr);

    void insert(T data){
        if(insert(root, createNode(data)))
            std::cout << "\nNode " << data << " is added." << std::endl;
        else
            std::cout << "\nNode " << data << " addition failed." << std::endl;
    }

    void preorderDisplay(std::shared_ptr<Node<T>> curr);
    void inorderDisplay(std::shared_ptr<Node<T>> curr);
    void postorderDisplay(std::shared_ptr<Node<T>> curr);
};

template<typename T>
void Avl<T>::isValid(std::shared_ptr<Node<T>> curr){
    if(balanceFactor(curr) == 2 && balanceFactor(curr->lchild) == 1)
        llRotation(curr);
    else if(balanceFactor(curr) == 2 && balanceFactor(curr->lchild) == -1)
        lrRotation(curr);
    else if(balanceFactor(curr) == -2 && balanceFactor(curr->rchild) == -1)
        rrRotation(curr);
    else if(balanceFactor(curr) == -2 && balanceFactor(curr->rchild) == 1)
        rlRotation(curr);
}

template<typename T>
void Avl<T>::llRotation(std::shared_ptr<Node<T>> curr){
    if(curr){
        auto pl = curr->lchild;
        auto plr = pl->rchild;

        pl->rchild = curr;
        curr->lchild = plr;

        curr->height = height(curr);
        pl->height = height(pl);

        (curr == root) ? root = pl : helper->lchild = pl;
    }
}
template<typename T>
void Avl<T>::lrRotation(std::shared_ptr<Node<T>> curr){
    if(curr){
        auto pl = curr->lchild;
        auto plr = pl->rchild;

        pl->rchild = plr->lchild;
        curr->lchild = plr->rchild;

        plr->lchild = pl;
        plr->rchild = curr;

        pl->height = height(pl);
        curr->height = height(curr);
        plr->height = height(plr);

        (curr == root) ? root = plr : helper->lchild = plr;
    }
}
template<typename T>
void Avl<T>::rrRotation(std::shared_ptr<Node<T>> curr){
    if(curr){
        auto pr = curr->rchild;
        auto prl = pr->lchild;

        pr->lchild = curr;
        curr->rchild = prl;

        curr->height = height(curr);
        pr->height = height(pr);

        (curr == root) ? root = pr : helper->rchild = pr;
    }
}
template<typename T>
void Avl<T>::rlRotation(std::shared_ptr<Node<T>> curr){
    if(curr){
        auto pr = curr->rchild;
        auto prl = pr->lchild;

        pr->lchild = prl->rchild;
        curr->rchild = prl->lchild;

        prl->rchild = pr;
        prl->lchild = curr;

        pr->height = height(pr);
        curr->height = height(curr);
        prl->height = height(prl);

        (curr == root) ? root = prl : helper->rchild = prl;
    }
}

template <typename T>
void Avl<T>::preorderDisplay(std::shared_ptr<Node<T>> curr){
    if(curr){
        std::cout << curr->data << ", ";
        preorderDisplay(curr->lchild);
        preorderDisplay(curr->rchild);
    }
}

template <typename T>
void Avl<T>::postorderDisplay(std::shared_ptr<Node<T>> curr){
    if(curr){        
        postorderDisplay(curr->lchild);
        postorderDisplay(curr->rchild);    
        std::cout << curr->data << ", ";
    }
}

template <typename T>
void Avl<T>::inorderDisplay(std::shared_ptr<Node<T>> curr){
    if(curr){        
        inorderDisplay(curr->lchild);
        std::cout << curr->data << ", ";
        inorderDisplay(curr->rchild);        
    }
}

void basic(){
    Avl<int> t(10);

    t.insert(10);
    t.insert(30);
    t.insert(20);

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