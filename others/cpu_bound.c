#include <stdlib.h>


void sort(int *arr, size_t len){
    for (size_t i = 0; i < len; i++){
        for (size_t j = 0; j < len - 1; j++){
            if (arr[j] > arr[j + 1]){
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(){
    int n = 100;
    int *arr = (int *) malloc(n * sizeof(int));

    while(1){
        for (int i = 0; i < n; i++){
            arr[i] = rand();
        }
        sort(arr, n);
    }

    return 0;
}
