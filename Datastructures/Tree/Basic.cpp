#include <iostream>
#include <memory>
#include <queue>
#include <stack>

template<typename T>
struct Node{
    std::shared_ptr<Node<T>> lchild;
    T data;
    std::shared_ptr<Node<T>> rchild;   
};

template<typename T>
class Tree{
    std::shared_ptr<Node<T>> root;
public:
    void create();
    std::shared_ptr<Node<T>> getRoot() const{
        return root;
    }
    std::shared_ptr<Node<T>> createNode(T data);
    void preorderDisplay(std::shared_ptr<Node<T>> curr);
    void inorderDisplay(std::shared_ptr<Node<T>> curr);
    void postorderDisplay(std::shared_ptr<Node<T>> curr);
    void preorderDisplayIter(std::shared_ptr<Node<T>> curr);
    void inorderDisplayIter(std::shared_ptr<Node<T>> curr);
    void postorderDisplayIter(std::shared_ptr<Node<T>> curr);

    int inline height(std::shared_ptr<Node<T>> curr){
        return (curr) ? height(curr->lchild) > height(curr->rchild) ? height(curr->lchild) + 1 : height(curr->rchild) + 1 : 0;
    }    
    int inline count(std::shared_ptr<Node<T>> curr){
        return (curr) ? count(curr->lchild) + count(curr->rchild) + 1 : 0;
    }
    int inline sum(std::shared_ptr<Node<T>> curr){
        return (curr) ? sum(curr->lchild) + curr->data + sum(curr->rchild) : 0;
    }
    int inline countBi(std::shared_ptr<Node<T>> curr){
        return (curr) ? (curr->lchild && curr->rchild) ? countBi(curr->lchild) + countBi(curr->rchild) + 1 : countBi(curr->lchild) + countBi(curr->rchild) : 0;
    }
    int inline countUniBi(std::shared_ptr<Node<T>> curr){
        return (curr) ? (curr->lchild || curr->rchild) ? countUniBi(curr->lchild) + countUniBi(curr->rchild) + 1 : countUniBi(curr->lchild) + countUniBi(curr->rchild) : 0;
    }
    int inline countUni(std::shared_ptr<Node<T>> curr){
        return (curr) ? ((curr->lchild && !curr->rchild) || (curr->rchild && !curr->lchild)) ? countUni(curr->lchild) + countUni(curr->rchild) + 1 : countUni(curr->lchild) + countUni(curr->rchild) : 0;
    }
    int inline countleaf(std::shared_ptr<Node<T>> curr){
        return (curr) ? (!curr->lchild && !curr->rchild) ? countleaf(curr->lchild) + countleaf(curr->rchild) + 1 : countleaf(curr->lchild) + countleaf(curr->rchild) : 0;
    }
};

template<typename T>
std::shared_ptr<Node<T>> Tree<T>::createNode(T data){
    std::shared_ptr<Node<T>> curr = std::make_shared<Node<T>>();
    //curr->data = data;
    return curr;
}

template<typename T>
void Tree<T>::create(){
    std::shared_ptr<Node<T>> curr;
    std::shared_ptr<Node<T>> temp;
    std::queue<std::shared_ptr<Node<T>>> q;
    T x;
    
    std::cout << "\nEnter the Root : "<< std::flush;
    std::cin >> x;
    
    root = createNode(x);    
    q.push(root);
    
    while(!q.empty()){
        curr = q.front();
        q.pop();
        
        std::cout << "\nEnter Left child of " << curr->data << " : "<< std::flush;
        std::cin >> x;
        if(x != -1){
            temp = createNode(x);
            curr->lchild = temp;
            q.push(temp);            
        }
        std::cout << "\nEnter Right child of " << curr->data << " : "<< std::flush;
        std::cin >> x;
        if(x != -1){
            temp = createNode(x);   
            curr->rchild = temp;
            q.push(temp);  
        }        
    }    
}

template<typename T>
void Tree<T>::preorderDisplay(std::shared_ptr<Node<T>> curr){
    if (curr){
        std::cout << curr->data << ", " << std::flush;
        preorderDisplay(curr->lchild);
        preorderDisplay(curr->rchild);
    }
}

template<typename T>
void Tree<T>::inorderDisplay(std::shared_ptr<Node<T>> curr){
    if (curr){
        inorderDisplay(curr->lchild);
        std::cout << curr->data << ", ";        
        inorderDisplay(curr->rchild);
    }
}

template<typename T>
void Tree<T>::postorderDisplay(std::shared_ptr<Node<T>> curr){
    if (curr){
        postorderDisplay(curr->lchild);               
        postorderDisplay(curr->rchild);
        std::cout << curr->data << ", "; 
    }
}

template<typename T>
void Tree<T>::preorderDisplayIter(std::shared_ptr<Node<T>> curr){
    std::stack<std::shared_ptr<Node<T>>> st;
    
    while(curr || !st.empty()){
        if(curr){
            std::cout << curr->data << ", ";
            st.push(curr);
            curr = curr->lchild;
        }
        else{
            curr = st.top();
            curr = curr->rchild;
            st.pop();
        }
    }
}

template<typename T>
void Tree<T>::inorderDisplayIter(std::shared_ptr<Node<T>> curr){
    std::stack<std::shared_ptr<Node<T>>> st;
    
    while(curr || !st.empty()){
        if(curr){
            st.push(curr);
            curr = curr->lchild;
        }
        else{
            curr = st.top();
            std::cout << curr->data << ", ";
            curr = curr->rchild;
            st.pop();
        }
    }
}

template<typename T>
void Tree<T>::postorderDisplayIter(std::shared_ptr<Node<T>> curr){
    std::stack<std::shared_ptr<Node<T>>> st;
    
    while(curr || !st.empty()){
        if(curr){
            st.push(curr->rchild);
            st.push(curr);
            curr = curr->lchild;
        }
        else{
            curr = st.top();
            st.pop();

            if(!st.empty() && st.top() == curr->rchild){
                auto right = st.top();
                st.pop();
                st.push(curr);
                curr = right;
            }
            else{
                std::cout << curr->data << ", ";
                curr = nullptr;
            }
        }
    }
}

void basic(){
    Tree<int> t;
    t.create();
    
    std::cout << "\nPreorder: " << std::endl;
    t.preorderDisplay(t.getRoot());
    std::cout << std::endl;
    
    std::cout << "\nInorder: " << std::endl;
    t.inorderDisplay(t.getRoot());
    std::cout << std::endl;
    
    std::cout << "\nPostorder: " << std::endl;
    t.postorderDisplay(t.getRoot());
    std::cout << std::endl;

    std::cout << "\nPreorder Iterative: " << std::endl;
    t.preorderDisplayIter(t.getRoot());
    std::cout << std::endl;

    std::cout << "\nInorder Iterative: " << std::endl;
    t.inorderDisplayIter(t.getRoot());
    std::cout << std::endl;
    
    std::cout << "\nPostorder Iterative: " << std::endl;
    t.postorderDisplayIter(t.getRoot());
    std::cout << std::endl;

    std::cout <<"\nHeight : " << t.height(t.getRoot()) << std::endl;
    std::cout <<"Count : " << t.count(t.getRoot()) << std::endl;
    std::cout <<"Sum : " << t.sum(t.getRoot()) << std::endl;
    std::cout <<"CountBi : " << t.countBi(t.getRoot()) << std::endl;
    std::cout <<"CountUniBi : " << t.countUniBi(t.getRoot()) << std::endl;
    std::cout <<"CountUni : " << t.countUni(t.getRoot()) << std::endl;
    std::cout <<"CountLeaf : " << t.countleaf(t.getRoot()) << std::endl;
    
}

void op(){
    Tree<double> t;
    t.create();

    std::cout << "\nPreorder: " << std::endl;
    t.preorderDisplay(t.getRoot());
    std::cout << std::endl;
    
    std::cout << "\nInorder: " << std::endl;
    t.inorderDisplay(t.getRoot());
    std::cout << std::endl;
    
    std::cout << "\nPostorder: " << std::endl;
    t.postorderDisplay(t.getRoot());
    std::cout << std::endl;    
}

int main(){
    //basic();
    op();
    return 0;
}