#include <stdio.h>
#include <stdlib.h>

int cnt = 0;

void swap(int *a, int *b);
void SelectSort(int *k, int n);
int SelectMinKey(int *k, int n, int i);
void BubbleSort(int *k, int n);
void HeapSort(int *k, int n);
void adjust(int *k, int n, int i);
void MergeSort(int *sr, int *tr, int leftend, int rightend);
void merge(int *x, int *tmp, int left, int leftend, int rightend);
void QuickSort(int *k, int left, int right);

int main() {
    int numsSize, order;
    scanf("%d %d", &numsSize, &order);
    int *nums = (int *)malloc(sizeof(int) * numsSize);
    for (int i = 0; i < numsSize; ++i) {
        scanf("%d", &nums[i]);
    }
    switch (order) {
    case 1: SelectSort(nums, numsSize);             break;
    case 2: BubbleSort(nums, numsSize);             break;
    case 3: HeapSort(nums, numsSize);               break;
    case 4: MergeSort(nums, nums, 0, numsSize - 1); break;
    case 5: QuickSort(nums, 0, numsSize - 1);       break;
    default: break;
    }
    for (int i = 0; i < numsSize; ++i) {
        printf("%d ", nums[i]);
    }
    printf("\n%d", cnt);
    return 0;
}

void swap(int *a, int *b) {
    int tmp = *b;
    *b = *a;
    *a = tmp;
}

void SelectSort(int *k, int n) {
    for (int i = 0; i < n; ++i) {
        int j = SelectMinKey(k, n, i);
        if (i != j) {
            swap(&k[i], &k[j]);
        }
    }
    cnt = n * (n - 1) / 2;
}

int SelectMinKey(int *k, int n, int i) {
    int min = i;
    for (++i; i < n; ++i) {
        min = k[min] < k [i] ? min : i;
    }
    return min;
}

void BubbleSort(int *k, int n) {
    for (int i = 0; i < n; ++i) {
        int sgn = 1;
        for (int j = 1; j < n - i; ++j) {
            cnt++;
            if (k[j - 1] > k[j]) {
                swap(&k[j - 1], &k[j]);
                sgn = 0;
            }
        }
        if (sgn) {
            break;
        }
    }
}

void HeapSort(int *k, int n) {
    for (int i = n / 2; i >= 0; --i) {
        adjust(k, n, i);
    }
    for (int i = n - 1; i > 0; --i) {
        swap(&k[0], &k[i]);
        adjust(k, i, 0);
    }
}

void adjust(int *k, int n, int i) {
    int j, temp;
    temp = k[i];
    j = 2 * i + 1;
    while (j < n) {
        if (j < n-1 && k[j] < k[j + 1]) {
            j++;
        }
        cnt++;
        if(temp >= k[j]) { 
            break;
        }
        k[(j - 1) / 2] = k[j];
        j = 2 * j + 1;
    }
    k[(j - 1) / 2] = temp;
}

void MergeSort(int *sr, int *tr1, int leftend, int rightend) {
    int tr2[100];
    if (leftend == rightend) {
        tr1[leftend] = sr[leftend];
    } else {
        int m = (leftend + rightend) / 2;
        MergeSort(sr, tr2, leftend, m);
        MergeSort(sr, tr2, m + 1, rightend);
        merge(tr2, tr1, leftend, m, rightend);
    }
}

void merge(int *sr, int *tr, int left, int leftend, int rightend) {     
    int i = left, j = leftend+1, q = left;
    while (i <= leftend && j <= rightend) {
        cnt++;
        if (sr[i] <= sr[j]) {
            tr[q++] = sr[i++];
        } else {
            tr[q++] = sr[j++];
        }
    }
    while (i <= leftend) {
        tr[q++] = sr[i++];
    }
    while (j <= rightend) {
        tr[q++] = sr[j++];
    }
    for(i = left; i <= rightend; i++) {
        sr[i] = tr[i];
    }
}

void QuickSort(int *k, int left, int right) {
    int i, last;
    if (left < right) {
        last = left; 
        for (i = left + 1; i <= right; i++) {
            cnt++;
            if (k[i] < k[left]) {
                swap(&k[++last], &k[i]); 
            }
        }
        swap(&k[left], &k[last]);
        QuickSort(k, left, last-1); 
        QuickSort(k, last+1, right);   
    }
}
