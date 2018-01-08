#pragma once
#include <memory>

/**************************************************************************************************/
/*										Heap Tree implementation								  */
template<class T>
class HeapTree
{
public:
	
	HeapTree(int maxsize = 20) {

		try {
			_maxSize = maxsize;
			_data = new T [maxsize];
			::memset(_data, 0, sizeof(T));
			_N = 1;
		}
		catch (bad_alloc& ba) {
			cout << ba.what() << endl;
		}
	}

	HeapTree(const HeapTree * obj);
	virtual ~HeapTree()
	{
		//traverse the tree and destroy all the nodes.
//		RemoveTree();
	}

	//methods and operations
	void Insert(T k);
	void unheap(int k); // k is the index of the node in the array
	void down_heap(int k);
	void RemoveTree();
	bool IsEmpty();
	template<typename T> 
	friend ostream& operator<<(ostream& out, HeapTree<T> ht);
	//data members
protected:
	//Heap Tree is an array of only keys with maximum size of N
	T * _data;
	int _N;	//maxsize of the array.
	int _maxSize;//current position where we are at
};
template<typename T>
ostream& operator<<(ostream& out, HeapTree<T> ht) {
	for (int i = 1; i < ht._N; i++)
		out << ht._data[i] << " ";
	out << "\n";

	return out;
}

template<class T>
HeapTree<T>::HeapTree(const HeapTree *obj){
	_data = obj->_data;
	_N = obj->_N;
	_maxSize = obj->_maxSize;
}

template<class T>
void HeapTree<T>::Insert(T k){
	try {
		if ( 1 > _N && _N < _maxSize ) throw std::out_of_range("zereshk");
			_data[_N++] = k;	//one item added to the heap --> violation of heap condition at this point!?
			//call unheap to remove the violation of heap condition as we mentioned above.
			unheap(_N-1);
	}
	catch (exception ex) {
		cerr << ex.what() << endl;
	}
}

template<class T>
bool HeapTree<T>::IsEmpty() {
	return _N == 1;
}

//unheap swims up the tree to fix violation of priority queue condition
//each parent must be larger that its children
template<class T>
void HeapTree<T>::unheap(int k){
	try{
		//check _data is not empty.
		if (IsEmpty())	return;

		while ( k > 1 && ( _data[k/2] < _data[k] ) )
		{
			//swap carefully
			T t; t = _data[k / 2]; _data[k / 2] = _data[k]; _data[k] = t;
			//swim up the heap from child to the parent.
			k = k / 2;
		}
	}
	catch(bad_alloc& ba){
		cerr << ba.what() << endl;
}

	return;
}

//sink top-down the heap tree. this is when the parent is less than the children 
//so that it is necessary to reHeapify the tree.
template<class T>
void HeapTree<T>::down_heap(int k) {

	try {
		int j = 0;

		while (2*k <= _N) {
			j = 2 * k;
			if ((_data[j] < _data[j + 1])) j++;
			if (_data[k] < _data[j]) { T t; t = _data[k]; _data[k] = _data[j]; _data[j] = t; }
			else break;
			k = j;
		}
	}
	catch(exception ex) {
		cerr << ex.what() << endl;
	}

	return;
}

template<class T>
void HeapTree<T>::RemoveTree() {
	try {
		if(_data) delete [] _data;
		_data = nullptr;
	}
	catch (exception ex) {
		cerr << ex.what() << endl;
	}
}


