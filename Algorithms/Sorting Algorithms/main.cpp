#include <iostream>
#include <vector>
#include <algorithm>

void read(std::vector<int>& vec){
    int x;
    for(int i{0}; i < 5; i++){
        std::cout << "\nEnter: ";
        std::cin >> x;
        vec.emplace_back(x);
    }
}
void disp(std::vector<int>& vec){
    std::cout << "[ ";
    for(int i : vec)
        std::cout << i << " ";
    std::cout << "]\n";
}

void bub(std::vector<int>& vec){
    int n = vec.size();
    for(int i = 0; i < n - 1; i++)
        for(int j = 0; j < n - i - 1; j++)
            if(vec[j] > vec[j + 1])
                std::swap(vec[j], vec[j + 1]);
}

void insertionSort(std::vector<int>& vec){
    int n = vec.size(), j, temp;
    for(int i = 1; i < n; i++){
        j = i - 1;
        temp = vec[i];

        while(j > -1 && vec[j] > temp){
            vec[j + 1] = vec[j];
            j--;
        }
        vec[j + 1] = temp;
    }
} 

void selectionSort(std::vector<int>& vec){
    int n = vec.size();
    for(int i = 0; i < n; i++){
        auto minIter = std::min_element(vec.begin() + i, vec.end());
        std::swap(vec[i], *minIter);
    }
}

int partition(std::vector<int>& vec, int l, int h){
    int pivot = vec[l], i = l, j = h;

    do{
        do{i++;}while(vec[i] <= pivot);
        do{j--;}while(vec[j] > pivot);

        if(i < j) std::swap(vec[i], vec[j]);
    }while(i < j);

    std::swap(vec[l], vec[j]);
    return j;
}

void quickSort(std::vector<int>& vec, int l, int h){
    int j;
    if(l < h){
        j = partition(vec, l, h);
        quickSort(vec, l, j);
        quickSort(vec, j + 1, h);
    }
}

void mergeSort(std::vector<int>& A, int low, int mid, int high){
    int i = low, j = mid + 1, k = 0;
    std::vector<int> res(high - low + 1);

    while (i <= mid && j <= high){
        if(A[i] < A[j])
            res[k++] = A[i++];
        else
            res[k++] = A[j++];
    }
    while (i <= mid)
        res[k++] = A[i++];

    while (j <= high)
        res[k++] = A[j++];
    
    int n = res.size();
    for(int k{0}; k < n; k++)
        A[low + k] = res[k];    
}

void rMergeSort(std::vector<int>& vec, int l, int h){
    int m;
    if(l < h){
        m = (l + h) / 2;

        rMergeSort(vec, l, m);
        rMergeSort(vec, m + 1, h);

        mergeSort(vec, l, m, h);
    }
}

void iMergeSort(std::vector<int>& vec, int n){
    int p;
    for(p = 2; p <= n; p = p * 2)
        for(int i{0}; i + p - 1 < n; i = i + p){
            int l = i, h = i + p - 1;
            int m = (l + h) / 2;
            mergeSort(vec, l, m, h);             
        }
    if(p / 2 < n)
        mergeSort(vec, 0, p / 2 - 1, n - 1);
}

void countSort(std::vector<int>& vec){
    auto maxpoint = std::max_element(vec.begin(), vec.end());
    std::vector<int> res(*maxpoint, 0);

    for(int &i : vec)
        res[i]++;

    int i = 0;
    vec.clear();

    while(i <= *maxpoint){
        if(res[i] > 0){
            vec.emplace_back(i);
            res[i]--;
        }
        else
            i++;    
    }
}

int main(){
    std::vector<int> nums;

    read(nums);
    std::cout << "\nBefore : ";
    disp(nums);

    countSort(nums);
    std::cout << "\nAfter : ";
    disp(nums);

    return 0;
}