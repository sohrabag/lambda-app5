#pragma once

using namespace std;

namespace SortingAlg {
	class SortLib
	{
	public:
		SortLib();
		~SortLib();
	};

	template<class T>
	class selection {
	public:
		//ctor
		selection(std::size_t N=100) : arr(new T[100]), _size(0) {}
		selection(std::size_t N, const T * a) : arr(new T[N]), _size(0) {
		for (int i = 0; i < N; i++) arr[i] = a[i]; _size(0);
		}
		//dtor
		~selection() { delete[] arr; }

		//public methods
		void Add(T elm) { arr[_size++] = elm; }
		void Sort();
		size_t Count() const { return _count; }
		void show() {
			for (int i = 0; i < _size; i++) std::cout <<  arr[i] << " ";
			std::cout << endl;
		}
	private:
		//data members
		T * arr;
		std::size_t _size;

		//methods
		template<class T>
		static bool less(const T& elm1, const T& elm2) {
			return elm1 < elm2;
		}
		template<class T>
		static void exch(T& elm1, T&elm2) {
			T t; t = elm1; elm1 = elm2; elm2 = t;
		}
		template<class T>
		friend bool operator<(const T& elm1, const T& elm2);
	};

	template<class T>
	inline bool operator<(const T& elm1, const T& elm2) {
		return (elm1 < elm2);
	}
	//void Sort() public method to do selection sort
		template<class T>
		void selection<T>::Sort() {
			for (int i = 0; i < (_size - 1); i++)
				for (int j = i+1; j < (_size - 1); j++)
				{
					if (!less(arr[i], arr[j])) { exch(arr[i], arr[j]); }
				}
		}
}


