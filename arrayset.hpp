#ifndef ARRAYSET_HPP_INCLUDED
#define ARRAYSET_HPP_INCLUDED

#include <iostream>
#include "set.hpp"

using namespace std;

template< class value_type >
class arrayset : public set<value_type> {
public:
	//constructor
	arrayset();
	arrayset(int);
	//copy constructor
	arrayset(const arrayset<value_type>&);
	//deconstructor
	~arrayset();

	//operator
	bool empty() const;
	bool belong(const value_type&) const;
	void insert(const value_type&);
	void erase(const value_type&);
	void merge(const arrayset<value_type>&);
	void intersection(const arrayset<value_type>&);
	void difference(const arrayset<value_type>&);
	int cardinality() const;
	void print_set() const;

private:
	int find(const value_type&) const;
	value_type* set;
	int maxdim;
	int lenght;
};

template< class value_type >
arrayset<value_type>::arrayset() {
	this->maxdim = 10;
	this->set = new value_type[maxdim];
	this->lenght = 0;
}

template< class value_type >
arrayset<value_type>::arrayset(int maxdim) {
	this->maxdim = maxdim;
	this->set = new value_type[maxdim];
	this->lenght = 0;
}

template< class value_type >
arrayset<value_type>::arrayset(const arrayset<value_type>& s) {
	this->maxdim = s.maxdim;
	this->set = new value_type[this->maxdim];
	this->lenght = s.lenght;
	for (int i = 0; i < this->lenght; ++i) {
		this->set[i] = s.set[i];
	}
}

template< class value_type >
arrayset<value_type>::~arrayset() {
	delete[] set;
}

template< class value_type >
bool arrayset<value_type>::empty() const {
	return (this->lenght == 0);
}

template< class value_type >
bool arrayset<value_type>::belong(const value_type& x) const {
	int pos;
	pos = find(x);
	return (this->set[pos] == x && pos != this->lenght);
}

template< class value_type >
void arrayset<value_type>::insert(const value_type& x) {
	if (this->empty()) {
		this->set[0] = x;
		this->lenght += 1;
	}
	else {
		int pos;
		pos = find(x);
		if (pos == this->lenght) {
			this->set[lenght] = x;
			this->lenght += 1;
		}
		else if (this->set[pos] != x && this->lenght < this->maxdim) {
			for (int i = this->lenght - 1; i > pos - 1; --i) {
				this->set[i + 1] = this->set[i];
			}
			this->set[pos] = x;
			this->lenght += 1;
		}
	}
}

template< class value_type >
void arrayset<value_type>::erase(const value_type& x) {
	if (!this->empty()) {
		int pos;
		pos = find(x);
		if (this->set[pos] == x && pos != this->lenght) {
			for (int i = pos; i < this->lenght - 1; ++i) {
				this->set[i] = this->set[i + 1];
			}
			this->lenght -= 1;
		}
	}
}

template< class value_type >
void arrayset<value_type>::merge(const arrayset<value_type>& B) {
	invalidsetoperator error;
	if (!B.empty()) {
		if ((this->maxdim - this->lenght) < B.lenght) {
			throw error.invalidmerge();
		}
		for (int i = 0; i < B.lenght; i++) {
			this->insert(B.set[i]);
		}
	}
}

template< class value_type >
void arrayset<value_type>::intersection(const arrayset<value_type>& B) {
	if (!B.empty()) {
		for (int i = 0; i < this->lenght; ++i) {
			if (!B.belong(this->set[i])) {
				this->erase(this->set[i]);
				i -= 1;
			}
		}
	}
	else {
		this->lenght = 0;
	}
}

template< class value_type >
void arrayset<value_type>::difference(const arrayset<value_type>& B) {
	if (!B.empty()) {
		for (int i = 0; i < this->lenght; ++i) {
			if (B.belong(this->set[i])) {
				this->erase(this->set[i]);
				i -= 1;
			}
		}
	}
}

template< class value_type >
int arrayset<value_type>::cardinality() const {
	return this->lenght;
}

template< class value_type >
int arrayset<value_type>::find(const value_type& x) const {
	if (this->empty()) {
		return 0;
	}
	else {
		int iter = 0;
		while (this->set[iter] < x && iter < this->lenght) {
			iter += 1;
		}
		return iter;
	}
}

template< class value_type >
void arrayset<value_type>::print_set() const {
	cout << "Set: [";
	for (int i = 0; i < this->lenght; ++i) {
		if (i == this->lenght - 1) {
			cout << this->set[i];
		}
		else {
			cout << this->set[i] << ", ";
		}
	}
	cout << "]." << endl;
}


#endif // !ARRAYSET_HPP_INCLUDED