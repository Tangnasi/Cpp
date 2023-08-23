// Vector.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <algorithm>

class MyVector {
private:
	int* data;
	size_t size;
	size_t capacity;

public:
	MyVector() : data(nullptr),size(0),capacity(0){}
	//MyVector()是构造函数的名称,data(nullptr)表示data变量初始化为空指针，size(0)表示初始化size变量为0，capacity(0)同理

	~MyVector()
	{
		delete[] data;
	}//析构函数，销毁该对象时会自动执行内部代码，释放new运算符分配的内存块，用防止内存泄露

	size_t Size() const {
		return size;
	}
	//获取MyVector的大小

	bool Empty() const {
		return size == 0; //判断size是否为0
	}
	//检测MyVector是否为空，若为空则返回true
    
	int& operator[](size_t index) {
		if (index >= size) {
			throw std::out_of_range("索引超出合法范围！"); //抛出异常
        }
		return data[index];
	}
	//函数重载，重载了“[]"，实质就是实现了用[]来获取对应下标的数值
    
	void Reserve(size_t newCapacity) {  //重设容量
		if (newCapacity <= capacity) {   //新容量是否小于旧容量
			return;
		}
		int* newData = new int[newCapacity];//动态分配内存给 指针newData
		for (size_t i = 0; i < size; ++i) {//把原来data数组存储的数据倒入newData数组内
			newData[i] = data[i];
		}

		delete[] data;//释放分给原来data的内存块
		data = newData;//指针更新
		capacity = newCapacity; //变量更新

	}

	void Resize(size_t newSize) {  //更新大小
		if (newSize > capacity) {
			Reserve(newSize);    //若新大小大于当前容量，则先扩大容量分配足够内存
		}
		if (newSize > size) {
			for (size_t i = size; i < newSize; ++i) {
				data[i] = int();  //新元素用int初始化
			}
		}
		size = newSize; //大小更新
	}

	void PushBack(int value) {
		if (size == capacity) {
			Reserve(capacity == 0 ? 1 : capacity * 2);//容量是否为0，为0则置为1，否则在原有容量基础上乘2

		}
		data[size++] = value;//value的值赋给数组下标加一的
	}
	void PopBack() {
		if (size > 0) {
			--size;
		}
	 }//移除数组末尾的元素

	void Sort() {
		std::sort(data, data + size);
	}//排序

	bool Contains(int value) const { //查找动态数组内元素
		for (size_t i = 0; i < size; ++i) {
			if (data[i] == value) {
				return true;//找到返回true
			}
		}
		return false; //否则返回false
	}

	void Insert(size_t index, int value) { //在指定位置插入一个新的元素，其他元素向后移动
		if (index > size){ //判断输入的索引是否大于当前数组的索引
			throw std::out_of_range("索引越界"); //若是则抛出异常
		}
		if (size == capacity) { //扩大索引前先判断当前索引和容量的关系 若等于则
			Reserve(capacity == 0 ? 1 : capacity * 2); //容量是否为0，为0则置为1，否则在原有容量基础上乘2
		}

		for (size_t i = size; i > index; --i) { //index后数组数据灌入
			data[i] = data[i - 1];   //循环会将指定位置 index 之后的元素依次向后移动一个位置，为新元素 value 腾出插入位置。
		}
		data[index] = value;//然后，新元素被插入到 index 位置。
		++size;//size增加1
	}

	int& At(size_t index) {  //访问指定位置的元素，会进行范围检查，超出范围时抛出异常
		if (index >= size) {  //& 引用的作用就是可以允许你通过引用直接访问和修改容器中的元素，而不是在函数内部操作副本。
			throw std::out_of_range("索引越界");//例子：int& element = vec.At(1);  element = 5; 此时data[1]=5
		  }
		return data[index];
	}

	void Erase(size_t index) { //删除指定位置的元素，其他元素向前移动
		if (index >= size) {
			throw std::out_of_range("索引越界");
		}

		for (size_t i = index; i < size - 1; ++i) {
			data[i] = data[i + 1];
		}
		--size;
	}


};
int main()
{
	MyVector vec;
	vec.PushBack(3);
	vec.PushBack(1);
	vec.PushBack(2);

	std::cout << "动态数组内元素数量为：" << vec.Size() << std::endl;
	std::cout << "动态数组内元素为：";
	for (size_t i = 0; i < vec.Size(); ++i) {
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
	
	vec.Insert(1, 4);  // 在索引1位置插入4
    
	std::cout << "动态数组内元素数量为：" << vec.Size() << std::endl;
	std::cout << "动态数组内元素为：";
	for (size_t i = 0; i < vec.Size(); ++i) {
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;

	vec.Sort();

	std::cout << "排序后动态数组元素为";
	for (size_t i = 0; i < vec.Size(); ++i) {
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "数组索引2处的值为： " << vec.At(2) << std::endl;

	vec.Erase(1);  // 删除索引1的值

	int searchValue = 2;
	if (vec.Contains(searchValue)) {
		std::cout << "此动态数组包含元素:" << searchValue << std::endl;
	}
	else {
		std::cout << "此动态数组不包含元素：" << searchValue << std::endl;
	}

	searchValue = 9;
	if (vec.Contains(searchValue)) {
		std::cout << "此动态数组包含元素:" << searchValue << std::endl;
	}
	else {
		std::cout << "此动态数组不包含元素：" << searchValue << std::endl;
	}

	vec.PopBack();

	std::cout << "移除后动态数组元素数量：" << vec.Size() << std::endl;
	
	vec.Resize(5);

	std::cout << "调整后动态数组元素数量：" << vec.Size() << std::endl;

	return 0;

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
