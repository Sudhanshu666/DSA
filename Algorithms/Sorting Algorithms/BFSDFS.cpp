#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>

std::vector<int> visit(8,0);

void printMatrix(std::vector<std::vector<int>>& vec, int n){
    for(int i{1}; i < n; i++){
        std::cout << "\n[ ";
        for(int j{1}; j < n; j++)
            std::cout << vec[i][j] << " ";
        std::cout << "]";
    }
}

void BFS(std::vector<std::vector<int>>& vec, int init, int n){
    std::vector<int> visited(8,0);
    std::queue<int> q;

    std::cout << "\nBFS : " <<  init << " ";
    visited[init]++;
    q.emplace(init);

    while(!q.empty()){
        int curr = q.front();
        q.pop();

        for(int i{1}; i < n; i++)
            if(vec[curr][i] != 0 && visited[i] == 0){
                std::cout << i << " ";
                visited[i]++;
                q.emplace(i);
            }
    }
    std::cout << std::endl;
}

void DFS(std::vector<std::vector<int>>& vec, int init, int n){
    if(visit[init] == 0){
        std::cout << init << " ";
        visit[init]++;

        for(int i{1}; i < n; i++)
            if(vec[init][i] == 1 && visit[i] == 0)
                DFS(vec, i, n);
    }
}

int main(){
//       0 1 2 3 4 5 6 7    
    std::vector<std::vector<int>> nums {
        {0,0,0,0,0,0,0,0},//0
        {0,0,1,1,1,0,0,0},//1
        {0,1,0,1,0,0,0,0},//2
        {0,1,1,0,1,1,0,0},//3
        {0,1,0,1,0,1,0,0},//4
        {0,0,0,1,1,0,1,1},//5
        {0,0,0,0,0,1,0,0},//6
        {0,0,0,0,0,1,0,0}//7
    };

    BFS(nums, 1, nums.size());
    std::cout << "DFS : "; 
    DFS(nums, 1, nums.size());
    
    return 0;
}