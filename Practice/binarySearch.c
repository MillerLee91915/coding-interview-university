#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int binarySearch(int target, int *arr, int size)
{
    int front = 0;
    int back = size - 1;

    while (front <= back)
    {
        int mid = front + (back - front) / 2;

        if (arr[mid] == target)
        {
            return mid;
        }
        else if (arr[mid] < target)
        {
            front = mid + 1;
        }
        else
        {
            back = mid - 1;
        }
    }

    return INT_MIN;
}

int bsearch_recursive(int target, int *arr, int front, int back)
{
    if (front > back)
    {
        return INT_MIN;
    }

    int mid = front + (back - front) / 2;

    if (arr[mid] == target)
    {
        return mid;
    }
    else if (arr[mid] < target)
    {
        return bsearch_recursive(target, arr, mid + 1, back);
    }
    else
    {
        return bsearch_recursive(target, arr, front, mid - 1);
    }
}

int main()
{
    int arr[] = {1, 3, 5, 7, 9, 11, 13};
    int size = sizeof(arr) / sizeof(arr[0]);

    int targets[] = {1, 7, 13, 8};   // 測試資料
    int tsize = sizeof(targets) / sizeof(targets[0]);

    for (int i = 0; i < tsize; i++)
    {
        int result = bsearch_recursive(targets[i], arr, 0, size - 1);

        if (result == INT_MIN)
        {
            printf("target %d : not found\n", targets[i]);
        }
        else
        {
            printf("target %d : found at index %d\n", targets[i], result);
        }
    }

    return 0;
}