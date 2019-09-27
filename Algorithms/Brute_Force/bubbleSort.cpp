void BubbleSort(int * arr, int size)
{
	//该算法用冒泡排序对数组arr[0...n-1]进行排序
	//输入：一个可排序数组arr[0...n-1]
	//输出：非降序排列的数组arr[0...n-1]
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (arr[j+1] < arr[j])
			{
				arr[j] = arr[j] ^ arr[j+1];
				arr[j+1] = arr[j] ^ arr[j+1];
				arr[j] = arr[j] ^ arr[j+1];
			}
		}
	}
}