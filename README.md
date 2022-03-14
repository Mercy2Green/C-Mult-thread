# C-Mult-thread
2022年3月11日我的C++多线程学习记录
规划：C++ ->(多线程编程、RNN和LSTM神经网络) -> C# -> (系统编程、游戏mod) -> python库

## 2022年3月12日
### 1.线程共享信息与互斥锁的使用

```C++
#include <mutex>  
mutex mutex1;  
mutex.lock();  
mutex.unlock();
```

## 2022年3月13日
### 1.Windows和Linux多线程不是同一个
Linux使用pthread库，Windows使用thread库。
进程间通信方式：https://blog.csdn.net/weixin_38416696/article/details/90719388

C++ Primer Plus中没有多线程的详细教学，不用费钱了

## 2022年3月14日
### 1.C++ *namespace*
*namespace*类似文件夹，*namespace*中有函数、变量等。比如*namespace A*和*namespace B*都可以有一个*print*函数用来输出，但是可能这两个*print*有不同的功能，所以你要是想要特指其中一个*print*的话，就可以如下：

```C++
using namespace std;//直接使用现有的namespace;

namespace A//或者自己创建
{
	void print()//内部组成可以是函数，也可以是数据结构、变量等。
	{
	cout << "namesapce A" << endl;
	}
}

namespace B
{
	void print()
	{
	cout << "namespace B" << endl;
	}
}

int main ()
{
    A::print();
    B::print();
    
	return 0;
}
```

