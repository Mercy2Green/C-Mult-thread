/*
#include <iostream>
#include <thread>
#include <windows.h>


using namespace std;

void print()
{
	Sleep(5000);
	cout << "���߳�����" << endl;
}
void print2()
{
	Sleep(5000);
	cout << "���߳�2����" << endl;
}


void main(int argc, char *argv[])
{

	thread test1(print);//�ഴ��
	thread test2(print2);
	test1.join();//�ȴ����߳�ִ�н������Ż�ص����߳��С�
	//test1.detach();���߳��������̵߳ģ����߳��������̵߳ġ������߳�פ����̨�����߳̾Ͳ������߳��ˡ�
	//���߳�detach�����join�ˡ�
	//joinable()�жϵ�ǰ�߳��ܷ�join����detach��bool���ͷ���ֵ��


	test2.join();

	cout << "���߳�....." << endl;//������Զ�����


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
		cout << "�ӽ�������������" << endl;
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

	cout << "���̡߳�������" << endl;
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

	cout << "���̡߳�������" << endl;
	return 0;
}
*/

/*

#include <thread>
#include <iostream>
using namespace std;

void printInfo(int& num)//& because we need ��Ҫͬ��
{
	num++;
	cout << "���߳�\t" << num << endl;
}

int main()
{
	int num = 0;
	thread test1(printInfo, std::ref(num));//��������Ҫ�����ʽ
	test1.join();
	cout << "���̡߳�����" << num << endl;
}

*/

/*
#include <iostream>
#include <thread>
using namespace std;
void print(unique_ptr<int> ptr)
{
	cout << "���̣߳�" << ptr.get() << endl;
}

int main()
{

	unique_ptr<int> ptr(new int(1000));
	cout << "���̣߳�" << ptr.get() << endl;//move������������
	thread test1(print, move(ptr));
	test1.join();


	cout << "���̡߳�������" << ptr.get() << endl;
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
	//��Ҫ���ߣ�����һ������
	thread test1(&MM::print, mm, ref(num));
	test1.join();
	cout << this_thread::get_id() << endl;


	return 0;
}
*/