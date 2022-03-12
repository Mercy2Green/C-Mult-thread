#include <iostream>
#include <thread>
#include <list>
#include <mutex>
using namespace std;
mutex mutex1;

class Seaking
{
public:
	void makeFriend()
	{
		
		for (int i = 0; i < 1000; i++)
		{
			mutex1.lock();
			cout << "Get a girlfriend" << i << endl;
			mm.push_back(i);
			mutex1.unlock();
		}
		
	}
	void breakUp()
	{
		
		for (int i = 0; i < 1000; i++)
		{
			mutex1.lock();
			if (!mm.empty())
			{
				cout << "lose a grilfriend" << mm.front() << endl;
				mm.pop_front();
			}
			else
			{
				cout << "No grilfriend" << endl;
			}
			mutex1.unlock();
		}
		
	}

protected:
	list<int> mm;
};


int main()
{
	Seaking fx;
	thread test1(&Seaking::makeFriend, &fx);
	thread test2(&Seaking::breakUp, &fx);
	test1.join();
	test2.join();


	return 0;
}