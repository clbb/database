#include<iostream>
using namespace std;

template<class T>
class seqlist
{
public:
	seqlist(int sz = DefaultSize)
	{
		_capacity = sz > DefaultSize ? sz:DefaultSize;
		_size = 0;
		_seq = new T[_capacity];
	}
	~seqlist()
	{
		if(_size == 0)
			delete []_seq;
	}


public:
	bool Isempty()
	{
		return _size == 0 ? 1:0;
	}
	bool Isfull()
	{
		return _size >= _capacity ? 1 :0;
	}

	void Show_list()const
	{
		for (size_t i = 0; i < _size; ++i)
			cout << _seq[i] << " ";
		cout << endl;
	}

	void Push_back(int key)
	{
		if(Isfull())
			 
			Inc();
		_seq[_size]= key;
		_size++;
	}
	
	void Push_front(int key)
	{
		if(Isfull())
			return;
		_size++;

		int cur = _size-1;
		while(cur)
		{
			_seq[cur] = _seq[cur-1];
			cur--;
		}
		_seq[0] = key;
	}
	void pop_back()
	{
		if(Isempty())
			return;
		_size--;
	}
	size_t lenth()
	{
		return _size;
	}
	 int begin()
	 {
		 return 0;
	 }
	int end()
	{
		return _size-1;
	}

	int find(T key)//return pos
	{
		int i;
		for( i = 0; i<_size;++i)
		{
			if(_seq[i] == key)
				return i;
		}
		cout<<key<<" no exist"<<endl;
		exit(1);
	}

	void delete_pos(size_t pos)
	{
		if(pos < 0 || pos >= _size)
			return;

		size_t i = pos;
		while(i < _size)
		{
			_seq[i] = _seq[i+1];
			i++;
		}
		_size--;
	}

	void Insert_pos(size_t pos ,T key)
	{

		if(Isfull())
			Inc();

		if( pos >= _size)
			return;

		
		_size++;

		size_t i = _size-1;
		while(i > pos)
		{
			_seq[i] = _seq[i-1];
			i--;
		}
		_seq[pos] = key;
	}


	void Inc()
	{
		T *newseq = new T[_capacity+Incsize];
		memcpy(newseq,_seq,sizeof(T)*_size);
		delete []_seq;
		_seq = newseq;	
		_capacity= _capacity+Incsize;

	}
	size_t Capacity()
	{
		return _capacity;
	}
private:
	enum{DefaultSize=3,Incsize=4};
	size_t _capacity;
	size_t _size;
	T* _seq;

	
};

int main()
{
	seqlist<int> s(3);
	s.Push_back(1);
	s.Push_back(2);
	s.Push_back(3);
	cout<<s.Capacity()<<endl;
	//s.pop_back();
	s.Show_list();
	s.Insert_pos(0,11111);
	cout<<s.Capacity()<<endl;

	//s.delete_pos(2);
	s.Show_list();
	
	return 0;
}
