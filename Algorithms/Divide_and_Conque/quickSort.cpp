
int HoarePartition(int* arr, int l, int r);

void Quicksort(int* arr, int l, int r)
{
	//用Quicksort对子数组排序
	//输入：数组arr[0...size-1]中的子数组arr[l...r]，由左右下标l和r定义
	//输出：非降序的子数组arr[l...r]
	if (l < r)
	{
		int s = HoarePartition(arr, l, r);
		Quicksort(arr, l, s-1);
		Quicksort(arr, s+1, r);
	}
}

int HoarePartition(int* arr, int l, int r)
{
	//以第一个元素为中轴，对子数组进行划分
	//输入：数组中的子数组，由上下标和定义
	//输出：的一个划分，分裂点位置作为函数的返回值
	int p = arr[l];
	int i = l + 1;
	int j = r;
	do
	{
		while(arr[i++] < p);
		while(arr[j--] > p);
		i--;
		j++;
		std::swap(arr[i], arr[j]);
	}while (i < j);
	std::swap(arr[i], arr[j]);
	std::swap(arr[l], arr[j]);
	return j;
}