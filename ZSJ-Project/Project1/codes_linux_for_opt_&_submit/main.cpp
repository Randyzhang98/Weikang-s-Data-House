#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <climits>
#include <ctime>

using namespace std;


void print(int *arr, int array_length)
{
    for (int i = 0; i < array_length; i++)
    {
         cout << arr[i] << endl;
    }
}

void bubble_sort(int *arr, int array_length)
{
    for (int i = array_length - 2; i >= 0; i--)
    {
        for (int j = 0; j <= i; j++)
        {
            if (arr[j] > arr[j + 1]) swap(arr[j], arr[j+1]);
        }
    }
}

void insertion_sort(int *arr, int array_length)
{
    for (int i = 1; i < array_length; i++)
    {   
        int j = i;
        int temp = arr[j];
        while (1)
        {
            if (j == 0) break;
            if (arr[j - 1] > temp) 
            {
                arr[j] = arr[j-1];
            }
            else break;
            j--;
        }
        arr[j] = temp;
    }
}

void selection_sort(int *arr, int array_length)
{
    for (int i = 0; i < array_length - 1; i++)
    {
        int ipointer = i;
        for (int j = i + 1; j < array_length; j++)
        {
            if (arr[j] < arr[ipointer]) ipointer = j;
        }
        swap(arr[ipointer],arr[i]);
    }
}


void merge(int *arr, int left, int mid, int right)
{
    int * temp = new int[right - left + 1];int j = 0;
    int left_start = left, right_start = mid + 1, i = 0;
    while (left_start <= mid && right_start <= right)
    {
        if (arr[left_start] <= arr[right_start]) 
        {
            temp[i++] = arr[left_start++];
        }
        else 
        {
            temp[i++] = arr[right_start++];
        }
    }
    while (left_start <= mid) temp[i++] = arr[left_start++];
    while (right_start <= right) temp[i++] = arr[right_start++];
    for (j = left; j <= right; j++)
    {
        arr[j] = temp[j - left];
    }

    delete [] temp;
}

void merge_sort(int *arr, int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int partition_extra(int *arr, const int & left, const int & right)
{
    int pivotat, i;
    int array_length = right - left + 1;
    int *temp = new int[array_length];
    int left_temp = 0, right_temp = right - left;
    //srand(time(0));
    pivotat = rand() % array_length;
    pivotat += left;
    swap(arr[left], arr[pivotat]);
    for (i = left + 1; i <= right; i++)
    {
        if (arr[i] < arr[left]) 
        {
            temp[left_temp++] = arr[i];
        }
        else 
        {
            temp[right_temp--] = arr[i];
        }
    }
    temp[left_temp] = arr[left];
    pivotat = left_temp + left;
    for (i = left; i <= right; i++)
    {
        arr[i] = temp[i - left];
    }
    delete [] temp;
    return pivotat;
}

int partition_in(int *arr, const int & left, const int & right)
{
    int pivotat;
    int array_length = right - left + 1;
    int left_temp = left + 1, right_temp = right;
    //srand(time (0));
    pivotat = rand() % array_length + left;
    swap(arr[left], arr[pivotat]);
    while (left_temp <= right_temp)
    {
        while (arr[left_temp] < arr[left] && left_temp < right) 
        {
            left_temp++;
        }
        while (arr[right_temp] >= arr[left] && right_temp > left) 
        {
            right_temp--;
        }
        if (left_temp >= right_temp) break;
        swap(arr[left_temp], arr[right_temp]);
    }
    swap(arr[left], arr[right_temp]);
    pivotat = right_temp;
    return pivotat;

}

void quick_extra_sort(int *arr, const int & left, const int & right)
{
    if (left < right)
    {
       // cout << "here";
        int pivotat;
        pivotat = partition_extra(arr, left, right);
        quick_extra_sort(arr, left, pivotat-1); 
        quick_extra_sort(arr, pivotat+1, right);
    }
}

void quick_in_sort(int *arr, const int & left, const int & right)
{
    if (left < right)
    {
        int pivotat;
        pivotat = partition_in(arr, left, right);
        quick_in_sort(arr, left,pivotat - 1);
        quick_in_sort(arr,pivotat + 1, right);
    }
}

int main()
{
    int sort_type, array_length;
    srand(time (0));
    cin >> sort_type;
    cin >> array_length;
    int *arr = new int[array_length];
    for(int i = 0; i < array_length; i++)
    {
        cin >> arr[i];
    }
    if (sort_type == 0)
    {
        bubble_sort(arr, array_length);
    }
    else if (sort_type == 1)
    {
        insertion_sort(arr, array_length);
    }
    else if (sort_type == 2)
    {
        selection_sort(arr, array_length);
    }
    else if (sort_type == 3)
    {
        int left = 0, right = array_length - 1;
        merge_sort(arr, left, right);
    }
    else if (sort_type == 4)
    {
        int left = 0, right = array_length - 1;
        quick_extra_sort(arr, left, right);
    }
    else if (sort_type == 5)
    {
        int left = 0, right = array_length - 1;
        quick_in_sort(arr, left, right);
    }
    print(arr, array_length);
    delete [] arr;
    return 0;
}