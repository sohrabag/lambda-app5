#pragma once

#include <vector>
using namespace std;


namespace Mysapce {

	enum Mat_Type
	{
		NONE, HORIZONTAL, VERTICAL, STANDARD = 256, LARGE = 512
	};

	enum Name_list {
		sohrab, arezou, mahlagha, rahi
	};

//this is a enum template which can be used in different templates
	template<class E, class T>
	class enumVector	: public vector<T>{

	public:
		//constructors
		enumVector(E max) : vector<T>(1 + int(max)){}
		enumVector(const enumVector& v);
		T & operator[] (E index);
	protected:

	};

	template<class E, class T>
	inline enumVector<E, T>::enumVector(const enumVector & v)	: vector<T>(v)
	{
	}

	template<class E,class T>
	T & enumVector<E, T>::operator[] (E index) {

		return vector<T>::operator[] (index); //we exactly call the same operator from vector because 
											  //base class for enumVector is vector class.
	}


/*=======================		1D MATRIX TEMPLATE CLASS    =================================================*/

	template<class T>
	class Mat_Lib_1D {
	public:

		Mat_Lib_1D() {}

		Mat_Lib_1D(Mat_Type x, Mat_Type y)
		{
			if (x == HORIZONTAL) { _rows = 1; _cols = y; }
			else if (x == VERTICAL) { _rows = y; _cols = 1; }
			else
			{
				_rows = NONE;
				_cols = NONE;
			}

			//allocate a 2D matrix

		}
		//copy constructor
		Mat_Lib_1D(const Mat_Lib_1D& other) {
			for (int i = 0; i < _rows; i++)
				_pMat_Buffer[i] = other._pMat_Buffer[i];
		}

		virtual ~Mat_Lib_1D()
		{
			//no dynamically allocated memory to deallocate.
		}

		//Methods
		template<class T>
		friend ostream& operator<<(ostream& out, const Mat_Lib_1D<T>& mat);
		template<class T>
		friend istream& operator >> (istream& in, Mat_Lib_1D<T>& mat);
		template<class T>
		friend Mat_Lib_1D<T>& operator+( Mat_Lib_1D<T>& lhsmat1, const Mat_Lib_1D<T>& rhsmat2);
		template<class T>
		friend Mat_Lib_1D<T>& operator*(Mat_Lib_1D<T>& lhsmat1, Mat_Lib_1D<T>& rhsmat2);
		template<class T>
		friend Mat_Lib_1D<T>& operator/(Mat_Lib_1D<T>& lhsmat1, Mat_Lib_1D<T>& rhsmat2);
		template<class T>
		friend Mat_Lib_1D<T>& operator-(Mat_Lib_1D<T>& lhsmat1, Mat_Lib_1D<T>& rhsmat2);

	protected:

		//data members
		int _rows;
		int _cols;
		T _pMat_Buffer[LARGE];

		//Methods
		virtual void FinalConst();
	};


	template<class T>
	void Mat_Lib_1D<T>::FinalConst() {
#if 0
		if (_rows == 1)
			for (int i = 0; i < _cols; i++)
				_pMat_Buffer[i] = new T;

		if (_cols == 1)
			for (int i = 0; i < _rows; i++)
				_pMat_Buffer[i] = new T;
#endif

	}

	template<class T>
	inline ostream& operator<<(ostream& out, const Mat_Lib_1D<T>& mat) {

		for (int i = 0; i < mat._cols; i++) {
			out << mat._pMat_Buffer[i] << " ";
		}
		cout << endl;

		return out;
	}

	template<class T>
	inline istream& operator >> (istream& in, Mat_Lib_1D<T>& mat) {
		int val = 2;
		//import matrix data into input stream cin
		for (int i = 0; i < mat._cols; i++) {
			in >> mat._pMat_Buffer[i];
		}
		return in;
	}

	template<class T>
	inline Mat_Lib_1D<T>& operator+(Mat_Lib_1D<T>& lhsmat1, const Mat_Lib_1D<T>& rhsmat2) {

		for (int i = 0; i < lhsmat1._cols; i++) {
			lhsmat1._pMat_Buffer[i] = lhsmat1._pMat_Buffer[i] + rhsmat2._pMat_Buffer[i];
		}

		return lhsmat1;
	}

	template<class T>
	inline Mat_Lib_1D<T>& operator*(Mat_Lib_1D<T>& lhsmat1, Mat_Lib_1D<T>& rhsmat2) {

		for (int i = 0; i < lhsmat1._cols; i++)
			lhsmat1._pMat_Buffer[i] = lhsmat1._pMat_Buffer[i] * rhsmat2._pMat_Buffer[i];

		return lhsmat1;
	}

	template<class T>
	Mat_Lib_1D<T>& operator/(Mat_Lib_1D<T>& lhsmat1, Mat_Lib_1D<T>& rhsmat2) {

		for (int i = 0; i < lhsmat1._cols; i++)
			lhsmat1._pMat_Buffer[i] = lhsmat1._pMat_Buffer[i] - rhsmat2._pMat_Buffer[i];

		return lhsmat1;
	}

	template<class T>
	Mat_Lib_1D<T>& operator-(Mat_Lib_1D<T>& lhsmat1, Mat_Lib_1D<T>& rhsmat2) {

		lhsmat1._pMat_Buffer[i] = lhsmat1._pMat_Buffer[i] - rhsmat2._pMat_Buffer[i];

		return lhsmat1;
	}



	/*=======================2D MATRIX TEMPLATE CLASS ==============================================*/

	template<class T>
	class Mat_Lib_2D : Mat_Lib_1D<T>
	{
	public:

		Mat_Lib_2D()
		{
			_rows = NONE;
			_cols = NONE;
			//Finally construct the vectors of vectors to simulate a 2D matrix.
			FinalConst();
		}

		Mat_Lib_2D(int num_of_rows, int num_of_cols) {
			_rows = num_of_rows; _cols = num_of_cols;

			//Final construct of the 2D matrix with size of columns and rows specified
			FinalConst();

		}

		Mat_Lib_2D(	int num_of_rows,
						int num_of_cols,
								T init_val) {
			_rows = num_of_rows; _cols = num_of_cols;
			//construct the 2D with sizes given in the parameters.
			FinalConst();
			//initialize the 2D matrix with the initial value given.
			for (auto i = 0; i < _rows; i++)
				for (auto j = 0; j < _cols; j++) {
					_vec_Mat_Buffer[i][j] = init_val;
				}
		}

		virtual ~Mat_Lib_2D()
		{
		}

		//public methods
		void SetMatSize(int r, int c) {
			try {
				assert(r); assert(c);
				_rows = r; _cols = c;
			}
			catch (exception ex) {
				cout << ex.what();
			}
		}

		T& operator()(int i, int j){
			return _vec_Mat_Buffer[i][j];
		}

		auto row_size() {
			return _rows;
		}

		auto col_size() {
			return _cols;
		}

		//overloading operators
		template<class T>
		friend ostream& operator<<(ostream& out, Mat_Lib_2D<T>& mat);

		template<class T>
		friend istream& operator >> (istream& in, Mat_Lib_2D<T>& mat);

		template<class T>
		friend Mat_Lib_2D<T>& operator+(Mat_Lib_2D<T>& lhsmat, Mat_Lib_2D<T>& rhsmat);

		template<class T>
		friend Mat_Lib_2D<T>& operator-(Mat_Lib_2D<T>& lhsmat, Mat_Lib_2D<T>& rhsmat);

		template<class T>
		friend Mat_Lib_2D<T>& operator*(Mat_Lib_2D<T>& lhsmat, Mat_Lib_2D<T>& rhsmat);

		template<class T>
		friend Mat_Lib_2D<T>& operator/(Mat_Lib_2D<T>& lhsmat, Mat_Lib_2D<T>& rhsmat);

	protected:
		//data members
		vector<vector<T>>	_vec_Mat_Buffer;
		//Methods
		virtual void FinalConst() override;
	};

	template<class T>
	void Mat_Lib_2D<T>::FinalConst() {
		try {
			if (_rows != NONE && _cols != NONE)
			{
				_vec_Mat_Buffer = vector<vector<T>>(); _vec_Mat_Buffer.resize(_rows);
				//allocate the a 2D matrix
				for (auto i = 0; i < _rows; i++) {
					_vec_Mat_Buffer[i] = vector<T>();
					_vec_Mat_Buffer[i].resize(_cols);
				}
			}
			else
				cout << "Please Set Rows and columns to set number of rows and columns" << endl;
		}
		catch (bad_alloc& ba) {
			cout << ba.what() << endl;
		}
	}

	template<class T> 
	inline ostream& operator<<(ostream& out, Mat_Lib_2D<T>& mat) {
		for (auto i = 0; i < mat.row_size(); i++) {
			for (auto j = 0; j < mat.col_size(); j++) {
				out << mat(i, j) << " ";
			}
			out << endl;
		}
		return out;
	}

	template<class T>
	inline istream& operator >> (istream& in, Mat_Lib_2D<T>& mat) {
		for (auto i = 0; i < mat.row_size(); i++) {
			for (auto j = 0; j < mat.col_size(); j++) {
				in >> mat._vec_Mat_Buffer[i][j];
			}
		}

		return in;
	}

	template<class T>
	inline Mat_Lib_2D<T>& operator+(Mat_Lib_2D<T>& lhsmat, Mat_Lib_2D<T>& rhsmat) {
		for (auto i = 0; i < lhsmat.row_size(); i++) {
			for (auto j = 0; j < lhsmat.col_size(); j++) {
				lhsmat._vec_Mat_Buffer[i][j] += rhsmat._vec_Mat_Buffer[i][j];
			}
		}

		return lhsmat;
	}

	template<class T>
	inline Mat_Lib_2D<T>& operator-(Mat_Lib_2D<T>& lhsmat, Mat_Lib_2D<T>& rhsmat) {

		for (auto i = 0; i < lhsmat.row_size(); i++)
			for (auto j = 0; j < lhsmat.col_size(); j++)
				lhsmat._vec_Mat_Buffer[i][j] -= rhsmat._vec_Mat_Buffer[i][j];

		return lhsmat;
	}

	template<class T>
	inline Mat_Lib_2D<T>& operator*(Mat_Lib_2D<T>& lhsmat, Mat_Lib_2D<T>& rhsmat) {
#if 0
		for (auto i = 0; i < lhsmat.row_size(); i++)
			for (auto j = 0; j < lhsmat.col_size(); j++)
				lhsmat._vec_Mat_Buffer[i][j] *= rhsmat._vec_Mat_Buffer[i][j];
#endif
		return lhsmat;
	}

	template<class T>
	inline Mat_Lib_2D<T>& operator/(Mat_Lib_2D<T>& lhsmat, Mat_Lib_2D<T>& rhsmat) {
#if 0
		for (auto i = 0; i < lhsmat.row_size(); i++)
			for (auto j = 0; j < lhsmat.col_size(); j++)
				lhsmat._vec_Mat_Buffer[i][j] /= rhsmat._vec_Mat_Buffer[i][j];
#endif
		return lhsmat;
	}
	/*=================================================================================================*/

}
