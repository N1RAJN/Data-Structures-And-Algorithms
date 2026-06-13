#include <stdio.h>
#include <stdlib.h>

typedef struct {
    uint size;
    uint capacity;
    int *arr;
} Vector;

void initalize_arr(Vector *nums, uint capacity) {
    nums->capacity = capacity;
    nums->arr = (int *)calloc(capacity, sizeof(int));
    nums->size = 0;
}

void push_item(Vector *nums, int val) {
    if (nums->size == nums->capacity) {
        nums->capacity *= 2;
        nums->arr = (int *)realloc(nums->arr, nums->capacity * sizeof(int));
    }
    nums->arr[nums->size] = val;
    printf("Inserted %d at index %d\n", val, nums->size);
    nums->size++;
}

void pop_item(Vector *nums) {
    if (nums->size == 0) {
        printf("Empty array.\n");
        return;
    }
    nums->size--;
    printf("Popped %d at index %d\n", nums->arr[nums->size], nums->size);
}

void insert_item(Vector *nums, int index, int val) {
    if (index < 0 || index > nums->size) {
        printf("Index out of bounds.\n");
        return;
    }
    if (nums->size == nums->capacity) {
        nums->capacity *= 2;
        nums->arr = (int *)realloc(nums->arr, nums->capacity * sizeof(int));
    }
    for (int j = nums->size; j > index; --j) {
        nums->arr[j] = nums->arr[j - 1];
    }
    nums->arr[index] = val;
    nums->size++;
    printf("Inserted %d at index %d\n", val, index);
}
void remove_item(Vector *nums, int index) {
    if (index < 0 || index >= nums->size) {
        printf("Index out of bounds.\n");
        return;
    }
    int num = nums->arr[index];
    for (int j = index; j < nums->size - 1; ++j) {
        nums->arr[j] = nums->arr[j + 1];
    }
    nums->size--;
    printf("Remove %d from index %d\n", num, index);
}
