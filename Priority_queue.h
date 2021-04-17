#pragma once
#include<assert.h>

template<class T>
class Less
{
public:
	bool operator()(const T& x, const T& y)const
	{
		return x < y;
	}
};

template<class T>
class Greater
{
public:
	bool operator()(const T& x, const T& y)const
	{
		return x > y;
	}
};

namespace wzy
{
	//默认的情况下，优先级队列是一个大堆
	//这个使我们自己定义的，但是在标准库里面，大堆传的是Less，小堆传的是Greater
	template<class T, class Container = vector<T>,class Compare = Greater<T>>
	class priority_queue
	{
	public:
		//priority_queue() 
		//{}
		//只要你写了一个构造函数，那么编译器就不在默认生成其余的了，所以必须要自己补上
		//但是这个补上的构造函数并不是什么都没有干，对于我们所自己定义的自定义类型，他会在开始的时候自动调用构造函数初始化
		priority_queue() = default; //C++11中的关键字     强制的让编译器在给你生成一个默认的构造函数

		template<class InputIterator>
		priority_queue(InputIterator first, InputIterator last)
			:_con(first,last)
		{
			//从第一个非叶子结点处开始调整
			//从下往上建堆
			for (int i = (_con.size() - 1 - 1) / 2; i >= 0; --i)
			{
				AdjustDown(i);
			}

			//从上往下建堆
			//for (int i = 1; i < _con.size(); ++i)
			//{
			//	AdjustUp(i);
			//}
		}
		//因为此时在类里面，所以默认就可以访问到它的成员变量，所以只需要传一个参数
		void AdjustUp(int child)
		{
			Compare com;
			int parent = (child - 1) / 2;
			while (child > 0) //由于上面计算公式的原因，当你的孩子为0的时候，parent也为0，已经终止了
				//在粗暴简单点理解：当你child结点为1的时候，parent结点刚好是0，此时还是有父节点的，但是你的child结点一旦小于1的时候
				//直接的，parent就找不到了。
			{
				//if (_con[child] > _con[parent])
				if (com(_con[child] , _con[parent]))
				{
					swap(_con[child], _con[parent]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
				{
					break;
				}
			}
		}
		void push(const T& x)
		{
			_con.push_back(x);
			//此时的堆就不在满足大堆的兴致了，所以需要向上调整，来保持大堆的特性，孩子结点都要比父亲结点小
			AdjustUp(_con.size() - 1);
		}

		void AdjustDown(int parent)
		{
			Compare com;
			size_t child = parent * 2 + 1;
			//有左孩子，右孩子可能不存在
			while (child < _con.size())
			{
				//首先找出左右孩子中较大的哪一个
				//如果你不加child+1<_con.size()这句判断语句，那么你会发现后面的_con[child+1]是一个[]，里面有断言，如果一旦越界，直接崩
				//if (child + 1 < _con.size() && _con[child + 1] > _con[child])
				if (child + 1 < _con.size() && com(_con[child + 1] , _con[child]))

				{
					++child;
				}
				//然后再从较大的孩子和父亲结点的进行比较
				//if (_con[child] > _con[parent])
				if (com(_con[child] , _con[parent]))

				{
					swap(_con[child], _con[parent]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
				{
					break;
				}
			}
		}
		void pop()
		{
			assert(size() > 0);
			swap(_con[0], _con[_con.size() - 1]);
			_con.pop_back();
			AdjustDown(0);
		}

		const T& top()const
		{
			return _con[0];
		}

		size_t size()const
		{
			return _con.size();
		}

		bool empty()const
		{
			return _con.empty();
		}
	private:
		Container _con;
	};



}