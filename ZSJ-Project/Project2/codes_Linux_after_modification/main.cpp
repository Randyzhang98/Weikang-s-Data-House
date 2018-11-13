#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

inline void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int partition(int * array, const int & size, const int & p)
{
    swap(array[0], array[p]);
    int index;
    int left = 1, right = size - 1;
    while (left <= right)
    {
        while (array[left] < array[0] && left < size - 1)
        {
            left++;
        }
        while (array[right] >= array[0] && right > 0)
        {
            right--;
        }
        if (left>= right) break;
        swap(array[left], array[right]);
    }
    swap(array[0], array[right]);
    index = right;
    return index;
}
int sort_median(int * array, const int & size)
{
    for (int i = 1; i < size; i++)
    {   
        int j = i;
        int temp = array[j];
        while (1)
        {
            if (j == 0) break;
            if (array[j - 1] > temp) 
            {
                array[j] = array[j-1];
            }
            else break;
            j--;
        }
        array[j] = temp;
    }
    return array[size / 2];
}

int find_index(int * array, const int & p, const int & size) 
{
    for (int i = 0; i < size; i++)
    {
        if (array[i] == p) return i;
    }
    //cout << "THIS error on PPPPPPPPPP :: " << p << endl;
    return -1;
}

int deterministic_selection(int * array, const int & size, const int & order)
{
    if (size == 1) return array[order];
    int group_number = size / 5;
    int p;
    int final_array_add = size % 5;
    if (final_array_add != 0)
    {
        group_number++;
    }
    int * median_array = new int[group_number];
    for(int i = 0; i < group_number; i++)
    {
        if (final_array_add != 0 && i == group_number - 1)
        {
            median_array[i] = sort_median((array + 5 * i), final_array_add);
        }
        else 
        {
            median_array[i] = sort_median((array + 5 * i), 5);
        }
    }
    p = deterministic_selection(median_array, group_number, group_number / 2);
    delete [] median_array;
    int index = find_index(array, p, size);
    index = partition(array, size, index);
    if (index == order) return array[index];
    else if (index > order) return deterministic_selection(array, index, order);
    else return deterministic_selection((array + index + 1), (size - index - 1), (order - index - 1));
}

int random_selection(int * array, const int & size, const int & order)
{
    if (size == 1) return array[order];
    int index;
    index = rand() % size;
    index = partition(array, size, index);
    if (index == order) return array[index];
    else if (index > order) return random_selection(array, index, order);
    else return random_selection((array + index + 1), (size - index - 1), (order - index - 1));
}

int main()
{
    ios::sync_with_stdio(false);
    srand(time(NULL));
    clock_t start, end;
    start = clock();
    int type, size, order, output;
    cin >> type;
    cin >> size;
    cin >> order;
    int *array = new int[size]; 
    for (int i = 0; i < size; i++)
    {
        cin >> array[i];
    }
    if (type == 0)
    {
        output = random_selection(array, size, order);
    }
    else
    {
        output = deterministic_selection(array, size, order);
    }
    delete [] array;
    end = clock();
    //cout << "The during time is " << double(end - start)*1.0/CLOCKS_PER_SEC  << endl;
    cout << "The order-" << order << " item is " << output << endl;
    return 0;
}

