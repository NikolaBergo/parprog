#ifndef FASTMATRIX_H 
#define FASTMATRIX_H

#include <iostream>
using namespace std;

template<class T> class fmatrix {
public:
	
	fmatrix(size_t lines, size_t columns): lines(lines), columns(columns) { 
		bigbody = new T[lines * columns];
		body = new T*[lines];
		for (size_t i = 0; i < lines; i++) {
		body[i] = bigbody + i*columns;
		}
	}
	   
	~fmatrix() { 
		delete [] body;
		delete [] bigbody;
	}
	   
	T * operator()(size_t line, size_t col) { 
		return body[line]+col;
	}
	   
	T * operator()(size_t line, size_t col) const { 
		return body[line]+col;
	}
	   
	void print() const {
		for (int i = 0; i < lines; i++) {
			for (int j = 0; j < columns; j++) {
				cout << "  " << *(*this)(i,j) << ' ';
			} 
			cout << endl;
		}
	}
	bool mul(fmatrix const &left, fmatrix const &right) {
		if (left.columns != right.lines) return false;
		if (lines != left.lines) return false;
		if (columns != right.columns) return false;
		
		fmatrix<T> transposed(right.columns, right.lines);
		transposed.transpose(right);
		
		for (size_t i = 0; i < lines; i++) {
			for (size_t j = 0; j < columns; j++) {
				T acc = (T)0;
				for (size_t k = 0; k < left.columns; k++) {
					acc += *left(i,k) * *transposed(j,k);
				}
				*(*this)(i,j) = acc;
			}
		}
		
		return true;
	}
	
	bool add(fmatrix const &left, fmatrix const &right); 
private:
	
	T ** body;
	T *bigbody;
	size_t lines, columns;
	
	bool transpose(fmatrix const &source) {
		for (int i = 0; i < lines; i++) {
			for (int j = 0; j < columns; j++)
				*(*this)(i,j) = *source(j, i);
		}
	}
};

#endif
