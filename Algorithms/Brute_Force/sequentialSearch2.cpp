#include <vector>
int SequentialSearch2(std::vector<int> arr, int key)
{
	//顺序查找的算法实现，它用例查找键作为限位器
	//输入：一个n个元素的数组arr和一个查找键key
	//输出：第一个值等于key的元素的位置，如果找不到这个元素，返回-1
	arr.push_back(key);
	int i = 0;
	while (arr[i] != key)
		i++;
	if (i < arr.size() - 1)
		return i;
	else
		return -1;
}