#include<iostream>
#include<vector>
#include<list>
#include<deque>
#include<queue>
using namespace std;

#include "Stack.h" 
#include "Queue.h"
#include"Priority_queue.h"


void test_priority_queue()
{
	priority_queue<int, vector<int>, Less<int>> pq1;
	priority_queue<int, vector<int>, Greater<int>> pq2;

	pq1.push(1);
	pq1.push(5);
	pq1.push(4);
	pq1.push(8);
	pq1.push(3);
	pq1.push(9);


	while (!pq1.empty())
	{
		std::cout << pq1.top() << " ";
		pq1.pop();
	}
	std::cout << std::endl;


	pq2.push(1);
	pq2.push(5);
	pq2.push(4);
	pq2.push(8);
	pq2.push(3);
	pq2.push(9);


	while (!pq2.empty())
	{
		std::cout << pq2.top() << " ";
		pq2.pop();
	}
	std::cout << std::endl;
}


int main()
{

	test_priority_queue();

	return 0;
}


//template<class T>
//class Less
//{
//public:
//	bool operator()(const T& x, const T& y)const
//	{
//		return x < y;
//	}
//};
//
//
//int main()
//{
//	Less<int> less;
//	less(1, 2);
//}