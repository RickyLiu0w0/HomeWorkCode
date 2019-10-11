#include <iostream>

int ** strassenMatrix(int A[][2], int aSize, int B[][2], int bSize)
{
	//利用Strassen 矩阵乘法计算矩阵相乘
	//输入：简单起见，输入的大小均为2 X 2 的方阵A、B
	//输入：A X B，大小为2 X 2 的方阵
	if (aSize != 2 || bSize != 2)
	{
		std::cout << "目前仅支持 2 X 2 方阵的输入";
		exit(1);
 	}
 	int M1 = (A[0][0] + A[1][1]) * (B[0][0] + B[1][1]);
 	int M2 = (A[1][0] + A[1][1]) * B[0][0];
 	int M3 = A[0][0] * (B[0][1] - B[1][1]);
 	int M4 = A[1][1] * (B[1][0] - B[0][0]);
	int M5 = (A[0][0] + A[0][1]) * B[1][1];
	int M6 = (A[1][0] - A[0][0]) * (B[0][0] + B[0][1]);
	int M7 = (A[0][1] - A[1][1]) * (B[1][0] + B[1][1]);
	int** C = new int *[aSize];
	for (int i = 0 ; i < aSize; i++)
		C[i] = new int[aSize];
	C[0][0] = M1 + M4 - M5 + M7;
	C[0][1] = M3 + M5;
	C[1][0] = M2 + M4;
	C[1][1] = M1 + M3 - M2 + M6;
	return C;
}