#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <fstream>
#include <cctype>
#include <memory>
#include "Mat_Lib.h"

template<class T>
class AdjMatrix : public Mat_Lib_2D<T> {
public:
	AdjMatrix(){}
	void adjconst() {
		FinalConst();
}

	void Init_adjMatrix(int rows, int cols) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				SetMatrix(i, j, 0);
			}
		}
	}

	void SetMatrix(int row, int col, int val) {
		_vec_Mat_Buffer[row][col] = val;
	}

	std::vector<std::vector<int>> ret_adjMatrix() {
		return _vec_Mat_Buffer;
	}

	void Show_adjMatrix(int r, int c) {
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				std::cout << _vec_Mat_Buffer[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}
protected:
	int _rs; //rows of the matrix
	int _cs; // columns of the matrix
};

class Graph
{
	//private members
private:
	//graph processing objects
	std::vector<int> _vec; // list of vertices of the graph
	std::vector<int>::iterator _ver_it;//iterator for list of vertices
	std::set<std::pair<int, std::vector<int>>> _adj_list; //list of adjaency vertex
	std::set<std::pair<int, std::vector<int>>>::iterator _adj_it; //iterator to adjacent list of a vertix
	std::set<std::pair<int, int>> _edge_list;//edge-list and each edge is a std::pair
	std::set<std::pair<int, int>>::iterator _edge_it;
	std::pair<std::set<std::pair<int, int>>::iterator, bool> ret;//return value for inserting an edge pair to the vector of edges
//	int** ppadj;
	AdjMatrix<int> adjmat;
	int n_of_V;
	int n_of_E;
	int count;
	int idx;

	//file related objects
	std::ifstream _file;

public:

	//ctor create a graph with only V-vertex and without no edges
	Graph(int V) : n_of_E(0), n_of_V(0), count(0), idx(0)
	{
		srand(time(NULL));
		for (int i = 0; i < V; i++) { _vec.push_back(rand()%100); }
		_ver_it = _vec.begin();
		n_of_E = V - 1;
		n_of_V = V;
/*
//		std::shared_ptr<int*[]> foo(new int*[5]);
ppadj = new (int*[V]);
for (int i = 0; i < V; i++) { ppadj[i] = new int[V]; }
*/
		adjmat.SetMatSize(V, V);
		adjmat.adjconst();
	}

	//cotr reads a graph from data stream ifstream called in
	Graph(std::string fname) : n_of_E(0), n_of_V(0), count(0), idx(0)
	{
		char c;
		char a[4];
		a[3] = '\0';
		_file.open(fname, std::ios_base::binary);
		_file.seekg(0, _file.beg);

		_file.get(a, 3);
		n_of_V = _atoi64(a);
		std::cout << n_of_V << std::endl;
		do { c = _file.get(); } while (!std::isdigit(c));
		_file.putback(c);
		_file.get(a, 3);
		n_of_E = _atoi64(a);
		std::cout << n_of_E << std::endl;
/*
//allocate adjancy matrix
ppadj = new (int*[n_of_V]);
for (int i = 0; i < n_of_V; i++) { ppadj[i] = new int[n_of_V]; }
//initialize the matrix
*/
		adjmat.SetMatSize(n_of_V, n_of_V);
		adjmat.adjconst();

		do{
			c = _file.get();
			if (std::isdigit(c)) {
				_file.putback(c);
				_file.get(a, 3);
				_vec.push_back(_atoi64(a));
				std::cout << a << std::endl;
			}
		} while (c != EOF);

		//set the iterator _ver_it to the beginning of the vertices list
		_ver_it = _vec.begin();
	}

	//dtor to clean any memory cleaning
	virtual ~Graph()
	{
		_vec.clear();
		_edge_list.clear();
	}

	//public methods

	/*show adjacency matrxi*/
	void show_adjMatrix(int r, int c) {
		adjmat.Show_adjMatrix(r, c);
	}

	/*returns number of vertices for this graph*/
	inline int V() const {
		
		return n_of_V;
	}

	/*returns number of edges for this graph*/
	inline int E() const {
				
		return n_of_E;
	}

	/*creae a list of vertices adjacent to V*/
	std::set<std::pair<int, std::vector<int>>>::iterator adj(int V) {

		int size = _edge_list.size(); //point to the first edge in the list
		int second(0);
		std::vector<int> v;
		std::set<std::pair<int, int>>::iterator it;
		_edge_it = _edge_list.begin();

			do {
				second = _edge_it->second;
				if (_edge_it->first == V) { 
					v.push_back(second); 
				}
			} while (++_edge_it != _edge_list.end());
			_adj_list.insert(std::make_pair(V, v));
			
			return _adj_it;
	}

	std::vector<vector<int>> Fill_adjMatrix() {

		std::set<std::pair<int, std::vector<int>>>::iterator a_it = A_begin();
		//init adjancy matrix to zeros
		adjmat.Init_adjMatrix(n_of_V, n_of_V);
		//two vertices make an edge, should have their intersection in adjacency matrix set to 1
		for (int i = 0; i < a_it->second.size(); i++)
				adjmat.SetMatrix(a_it->first, a_it->second[i], 1);

		//return ppadj;
		return adjmat.ret_adjMatrix();
	}

	/*Adds an edge between vertices v-w and returns a iterable list of edges*/
	inline void AddEdge(int v, int w) {
		ret = _edge_list.insert(std::make_pair(v, w));
		if (ret.second == false) { throw; }
	}

	/*methods to scan vertices vector*/
	inline int First()const { return *_vec.begin(); }
	inline int End() const { return *_vec.end(); }
	inline int get_next() { return _vec[count++]; }
	inline int get_prev() { return _vec[--count]; }

	/*methods to iterate over list of edges*/
	inline std::set<std::pair<int, int>>::iterator E_begin() const { return _edge_list.begin(); }
	inline std::set<std::pair<int, int>>::iterator E_end() const { return _edge_list.end(); }
//operator++ cannot be used----	inline std::set<std::pair<int, int>>::iterator E_next() { return ++_edge_it; }

	/*methods to iterate over list of adjancy of a vertex*/
	inline std::set<std::pair<int, std::vector<int>>>::iterator A_begin() const { return _adj_list.begin(); }
	inline std::set<std::pair<int, std::vector<int>>>::iterator A_end() const { return _adj_list.end(); }
	inline std::set<std::pair<int, std::vector<int>>>::iterator A_next() { return _adj_it++; }
	inline int A_size() const { return _adj_list.size(); }
};

/*
_file.seekg(0, _file.end);
int length = _file.tellg();
char * buffer = new char[length];
_file.seekg(0, _file.beg);
_file.read(buffer, length);
std::cout << buffer << std::endl;
*/