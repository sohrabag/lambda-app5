#pragma once
#include<memory>

using namespace std;

//Queue is a FIFO data structure. the first item in is the first item in the line.
template<class T>
class Queue
{
public:

	Queue(int maxsize=20) : _front(0), _end(0), _N(maxsize), bWrapped(false)
	{
		try {
			_N = maxsize;
			//use calloc to allocate for memory allocation in generic templates
			_data = new T[_N];
			::memset(_data, 0, sizeof(T));
		}
		catch (bad_alloc& ba){
			cout << ba.what() << endl;
		}
	}

	virtual ~Queue()
	{
	}

	//members and operators
	void Enqueue(T val);
	T dequeue();
	bool IsEmpty();
	const unsigned& Size() const;
	bool IsFull();
	template<typename T>
	friend ostream& operator<<(ostream& out, Queue<T> q);
protected:
	int _front;
	int _end;
	int _N;	//max size of the queue
	T * _data;
	//printing flag when _end wrapps around the end of queue and insert at the begginig
	bool bWrapped;
};

//Enqueue(T val)
template<class T>
void Queue<T>::Enqueue(T val) {
	
	try {
//		_end %= _N; //should we turn around
		if (IsFull()) { cout << "Queue is full. dequeue some items and then enqueu again!" << endl;
		return;
		}
		if (_end >= _N) {
			_end %= _N;
			bWrapped = true;
		}

		//add a new item into the array.
		_data[_end++] = val;
	}
	catch (std::bad_alloc& ba) {
		cout << ba.what() << endl;
	}
}

//dequeue()
template<class T>
T Queue<T>::dequeue() {
	if (IsEmpty())	return 0;
	return _data[_front++];
}

//IsEmpty()
template<class T>
bool Queue<T>::IsEmpty() {
	return (_end - _front) == 0;
}

//IsFull()
template<class T>
bool Queue<T>::IsFull() {
	
	return (((_end - _front) >= _N) || ((_end == _front) && bWrapped));
}

//Size()
template<class T>
const unsigned& Queue<T>::Size() const {
	return (!bWrapped) ? (_end - _front) : _N;
}

//operator<<(ostream& out, Queue<T> q)
template<class T>
ostream& operator<<(ostream& out, Queue<T> q) {
	if( q._end >= q._front)
		for (int i = q._front; i < q._end ; i++) out << q._data[i] << " ";

	//This code takes care of scenario where wrapp around happens in the queue.
	if (q._end <= q._front) {
		for (int i = 0; i != q._end; i++) cout << q._data[i] << " ";
		for (int i = q._front; i < q._N; i++) out << q._data[i] << " ";
	}

	out << endl;

	return out;
}