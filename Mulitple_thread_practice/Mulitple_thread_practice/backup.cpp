/*
#include <iostream>
#include <thread>
#include <windows.h>


using namespace std;

void print()
{
	Sleep(5000);
	cout << "子线程运行" << endl;
}
void print2()
{
	Sleep(5000);
	cout << "子线程2运行" << endl;
}


void main(int argc, char *argv[])
{

	thread test1(print);//类创建
	thread test2(print2);
	test1.join();//等待子线程执行结束，才会回到主线程中。
	//test1.detach();主线程运行主线程的，子线程运行子线程的。把子线程驻留后台，主线程就不管子线程了。
	//当线程detach后就能join了。
	//joinable()判断当前线程能否join或者detach，bool类型返回值。


	test2.join();

	cout << "主线程....." << endl;//这个会自动换行


	return;
}
*/

/*
#include <iostream>
#include <thread>
using namespace std;

class MM
{
public:
	void operator()()
	{
		cout << "子进程启动。。。" << endl;
	}
};

int main()
{
	//MM();
	MM mm;
	thread test1(mm);
	test1.join();
	thread test2((MM()));
	test2.join();

	cout << "主线程。。。。" << endl;
	return 0;
}
*/

/*
#include <iostream>
#include <thread>
using namespace std;

int Max(int a, int b)
{
	return a > b ? a : b;
}

int main()
{
	int(*pMax)(int, int) = nullptr;
	pMax = [](int a, int b)->int {return a > b ? a : b; };

	cout << pMax(1, 2) << endl;

	cout << "主线程。。。。" << endl;
	return 0;
}
*/

/*

#include <thread>
#include <iostream>
using namespace std;

void printInfo(int& num)//& because we need 需要同步
{
	num++;
	cout << "子线程\t" << num << endl;
}

int main()
{
	int num = 0;
	thread test1(printInfo, std::ref(num));//传引用需要这个格式
	test1.join();
	cout << "主线程。。。" << num << endl;
}

*/

/*
#include <iostream>
#include <thread>
using namespace std;
void print(unique_ptr<int> ptr)
{
	cout << "子线程：" << ptr.get() << endl;
}

int main()
{

	unique_ptr<int> ptr(new int(1000));
	cout << "主线程：" << ptr.get() << endl;//move则这里就清空了
	thread test1(print, move(ptr));
	test1.join();


	cout << "主线程。。。。" << ptr.get() << endl;
	return 0;
}
*/

/*
#include<thread>
#include<iostream>
using namespace std;

class MM
{
public:
	void print(int& num)
	{
		num = 1001;
		cout << this_thread::get_id() << endl;
	}
};

int main()
{
	MM mm;
	int num = 1007;
	//需要告诉，是哪一个对象
	thread test1(&MM::print, mm, ref(num));
	test1.join();
	cout << this_thread::get_id() << endl;


	return 0;
}
*/