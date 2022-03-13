# C-Mult-thread
2022年3月11日我的C++多线程学习记录

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