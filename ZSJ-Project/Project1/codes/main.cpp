#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <climits>
#include <ctime>

using namespace std;

// void swap (int & a, int & b)
// {
//     int t = a;
//     a = b;
//     b = t;
// }

//safghdiashoaisjdoaisdj

void print(int *arr, int array_length)
{
    cout << "is:" << endl;
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
        bool flag = true;
        int j = i;
        while (flag)
        {
            if (j == 0) break;
            if (arr[j - 1] > arr[j]) swap(arr[j], arr[j - 1]);
            j--;
        }
    }
}
void selection_sort(int *arr, int array_length)
{
    for (int i = 0; i < array_length - 1; i++)
    {
        for (int j = i; j < array_length; j++)
        {
            if (arr[j] < arr[i]) swap(arr[j], arr[i]);
        }
    }
}

// void non_merge(int *arr, int i, int sorted_length, int array_length) // non-regression method
// {
//     int left_start = i, left_length = sorted_length, right_start = i + left_length, right_length = sorted_length;
//     if (i + 2*sorted_length >= array_length) 
//     {
//         left_start = 0;
//         left_length = sorted_length * 2;
//         right_start = i;
//         right_length = array_length - i;
//     }
//     int li = left_start, ri = right_start;

// }

// void non_merge_sort(int *arr, int array_length)// non-regression method
// {
//     int sorted_length = 1;
//     while (sorted_length < array_length)
//     {
//         int i = 0;
//         while (i < array_length)
//         {
//             merge(arr, i, sorted_length, array_length);//be care of sorted_arr_length greater than the actual length;
//             i += 2*sorted_length;
//         }
//         sorted_length *= 2;
//     }
// }

void merge(int *arr, int left, int mid, int right, int array_length)
{
    int * temp = new int[array_length];
    int left_start = left, right_start = mid + 1, i = left;
    while (left_start <= mid && right_start <= right)
    {
        if (arr[left_start] <= arr[right_start]) 
        {
            temp[i++] = arr[left_start++];
            //cout << "left it is " << left_start -1 << " and the value is " << arr[left_start - 1] << endl;
        }
        else 
        {
            temp[i++] = arr[right_start++];
            //cout << "right it is " << right_start -1 << " and the value is " << arr[right_start - 1] << endl;
        }
    }
    if (left_start > mid)
    {
        for (int j = right_start; j <= right; j++)
        {
            temp[i++] = arr[j];
        }
    }
    else 
    {
        for (int j = left_start; j <= mid; j++)
        {
            temp[i++] = arr[left_start++];
        }
    }
    for (int j = left; j <= right; j++)
    {
        arr[j] = temp[j];
        //cout << "temp [" << j << "] is " << temp[j] << endl;
    }
    delete [] temp;
}

void merge_sort(int *arr, int left, int right, int array_length)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        //cout << "midn is " << mid <<  endl;
        merge_sort(arr, left, mid, array_length);
        merge_sort(arr, mid + 1, right, array_length);
        merge(arr, left, mid, right, array_length);
    }
}

int partition_extra(int *arr, const int & left, const int & right)
{
    int pivotat, i;
    int array_length = right - left + 1;
    int *temp = new int[array_length];
    int left_temp = 0, right_temp = right - left;
    srand(time(0));
    pivotat = rand() % array_length;
    pivotat += left;
    //cout << "length is " << array_length << endl;
    //cout << "pivotat is " << pivotat << endl;
    //cout << "arr[pivotat] is " << arr[pivotat] << endl;
    swap(arr[left], arr[pivotat]);
    //cout << "arr[left] is " << arr[left] << endl;
    //int flag_it = 0;
    for (i = left + 1; i <= right; i++)
    {
        if (arr[i] < arr[left]) 
        {
            temp[left_temp++] = arr[i];
            //flag_it = 1;
        }
        else 
        {
            temp[right_temp--] = arr[i];
            //flag_it = 2;
        }
    }
    //if (right_temp != left_temp) cout << "temp it error" << endl;
    //if (flag_it = 2)
    //{

    //}/
    //else if (flag_it = 1)
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
    srand(time (0));
    pivotat = rand() % array_length + left;
    // cout << "length is " << array_length << endl;
    // cout << "pivotat is " << pivotat << endl;
    // cout << "arr[pivotat] is " << arr[pivotat] << endl;
    //  cout << "from " << left << " to " << right << " the array is ";
    //     for (int i = left; i <= right; i++)
    //     {
    //         cout << arr[i] << " ";
    //     } 
    //     cout << endl;
    //     cout << "after first swap" << endl;
    swap(arr[left], arr[pivotat]);
    // cout << "from " << left << " to " << right << " the array is ";
    //     for (int i = left; i <= right; i++)
    //     {
    //         cout << arr[i] << " ";
    //     } 
    //     cout << endl;
    
    
    // bool left_it = true, right_it = true;
    while (left_temp <= right_temp)
    {
        //cout << "hereh"<< endl;
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
        // cout << "left is " << left_temp << " right is " << right_temp << endl;
    }
    //if (left_temp != right_temp) cout << "temp ir" << endl;
    swap(arr[left], arr[right_temp]);
    // if (array_length == 2 && arr[left] >= arr[right])
    // {
    //     swap(arr[left], arr[right]);
    // }
    pivotat = right_temp;
    // cout << "from " << left << " to " << right << " the array is ";
    //     for (int i = left; i <= right; i++)
    //     {
    //         cout << arr[i] << " ";
    //     } 
    //     cout << endl;
    //     cout << "pivotat is " << pivotat << endl;
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
        //cout << "here";
        int pivotat = 3;
        pivotat = partition_in(arr, left, right);
        quick_in_sort(arr, left,pivotat - 1);
        quick_in_sort(arr,pivotat + 1, right);
    }
}

int main()
{
    int sort_type, array_length;
    double during_time;
    clock_t start, end;
    cin >> sort_type;
    cin >> array_length;
    int *arr = new int[array_length];
    for(int i = 0; i < array_length; i++)
    {
        cin >> arr[i];
    }
    start = clock();
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
        merge_sort(arr, left, right, array_length);
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

    end = clock();
    during_time = (end - start) / CLOCKS_PER_SEC;
    cout << array_length << endl;
    print(arr, array_length);
    //cout << during_time << endl;
    delete [] arr;
    return 0;
}