#ifndef SET_HPP_INCLUDED
#define SET_HPP_INCLUDED

#include <iostream>

using namespace std;

template< class value_type >
class set {
public:
	virtual bool empty() const = 0;
	virtual bool belong(const value_type&) const = 0;
	virtual void insert(const value_type&) = 0;
	virtual void erase(const value_type&) = 0;
	//virtual void merge(const set<value_type>&) = 0;
	//virtual void intersection(const set<value_type>&) = 0;
	//virtual void difference(const set<value_type>&) = 0;
	virtual int cardinality() const = 0;
};

class invalidsetoperator {
public:
	invalidsetoperator() {
		this->error = "Invalid operator.";

	}

	invalidsetoperator invalidmerge() {
		this->error = "Invalid merge. The not-included elements in A, contained in B, could be much more than the ones you can put in it";
		return *this;
	}

private:
	string error;
};


#endif // !SET_HPP_INCLUDED