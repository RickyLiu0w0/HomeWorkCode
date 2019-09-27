#include <iostream>

void  SelectionSort(int* arr, int size)
{
	//该算法用选择排序对给定的数组排序
	//输入：一个可排序的数组 arr[0...n-1]
	//输出：升序排列的数组 arr[0...n-1]
	for (int i = 0; i < size - 1; i++)
	{
		int min = i;
		for (int j = i + 1; j < size; j++)
		{
			if (arr[j] < arr[min])
				min = j;
		}
		if (i != min) 
		{
			arr[i] = arr[i] ^ arr[min];
			arr[min] = arr[i] ^ arr[min];
			arr[i] = arr[i] ^ arr[min];
		}
		
	}
	
}