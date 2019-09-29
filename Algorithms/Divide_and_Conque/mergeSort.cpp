#include <cmath>

void Merge(int* B, int Bsize, int* C , int Csize, int* A, int Asize);
void Mergesort(int* arr, int size)
{
	//递归调用mergesort来对数组排序
	//输入：一个可排序的数组arr[0...size-1]
	//输出：非降序排列的数组arr[0...size-1]
	if (size > 1)
	{
		int i;
		int* B = new int [size/2];
		int* C = new int [(int)ceil(size/2.0)];
		for (i = 0 ; i < size / 2; i ++)
			B[i] = arr[i];
		for (i = size / 2; i < size; i++)
			C[i - size/2] = arr[i];
		Mergesort(B, size/2);
		Mergesort(C, ceil(size/2.0));
		Merge(B, size/2, C,ceil(size/2.0), arr, size);
	}
	delete [] B;
	delete [] C;
}

void Merge(int* B, int Bsize, int* C , int Csize, int* A, int Asize)
{
	//将两个有序数组合并成一个更大的有序数组
	//输入：两个有序数组B[0...Bsize-1]和C[0...Csize-1]
	//输出：中已经有序存放了B和C中的元素
	if (Bsize + Csize != Asize)
		exit(1);
	int i, j, k;
	i = j = k = 0;
	while (i < Bsize && j < Csize)
		if (B[i] <= C[j])
			A[k++] = B[i++];
		else
			A[k++] = C[j++];
	if (i == Bsize)
		while (j < Csize)
			A[k++] = C[j++];
	else
		while (i < Bsize)
			A[k++] = B[i++];
}