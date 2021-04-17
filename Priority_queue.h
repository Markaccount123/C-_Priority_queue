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
	//Ĭ�ϵ�����£����ȼ�������һ�����
	//���ʹ�����Լ�����ģ������ڱ�׼�����棬��Ѵ�����Less��С�Ѵ�����Greater
	template<class T, class Container = vector<T>,class Compare = Greater<T>>
	class priority_queue
	{
	public:
		//priority_queue() 
		//{}
		//ֻҪ��д��һ�����캯������ô�������Ͳ���Ĭ������������ˣ����Ա���Ҫ�Լ�����
		//����������ϵĹ��캯��������ʲô��û�иɣ������������Լ�������Զ������ͣ������ڿ�ʼ��ʱ���Զ����ù��캯����ʼ��
		priority_queue() = default; //C++11�еĹؼ���     ǿ�Ƶ��ñ������ڸ�������һ��Ĭ�ϵĹ��캯��

		template<class InputIterator>
		priority_queue(InputIterator first, InputIterator last)
			:_con(first,last)
		{
			//�ӵ�һ����Ҷ�ӽ�㴦��ʼ����
			//�������Ͻ���
			for (int i = (_con.size() - 1 - 1) / 2; i >= 0; --i)
			{
				AdjustDown(i);
			}

			//�������½���
			//for (int i = 1; i < _con.size(); ++i)
			//{
			//	AdjustUp(i);
			//}
		}
		//��Ϊ��ʱ�������棬����Ĭ�ϾͿ��Է��ʵ����ĳ�Ա����������ֻ��Ҫ��һ������
		void AdjustUp(int child)
		{
			Compare com;
			int parent = (child - 1) / 2;
			while (child > 0) //����������㹫ʽ��ԭ�򣬵���ĺ���Ϊ0��ʱ��parentҲΪ0���Ѿ���ֹ��
				//�ڴֱ��򵥵���⣺����child���Ϊ1��ʱ��parent���պ���0����ʱ�����и��ڵ�ģ��������child���һ��С��1��ʱ��
				//ֱ�ӵģ�parent���Ҳ����ˡ�
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
			//��ʱ�ĶѾͲ��������ѵ������ˣ�������Ҫ���ϵ����������ִ�ѵ����ԣ����ӽ�㶼Ҫ�ȸ��׽��С
			AdjustUp(_con.size() - 1);
		}

		void AdjustDown(int parent)
		{
			Compare com;
			size_t child = parent * 2 + 1;
			//�����ӣ��Һ��ӿ��ܲ�����
			while (child < _con.size())
			{
				//�����ҳ����Һ����нϴ����һ��
				//����㲻��child+1<_con.size()����ж���䣬��ô��ᷢ�ֺ����_con[child+1]��һ��[]�������ж��ԣ����һ��Խ�磬ֱ�ӱ�
				//if (child + 1 < _con.size() && _con[child + 1] > _con[child])
				if (child + 1 < _con.size() && com(_con[child + 1] , _con[child]))

				{
					++child;
				}
				//Ȼ���ٴӽϴ�ĺ��Ӻ͸��׽��Ľ��бȽ�
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