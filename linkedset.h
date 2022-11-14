#ifndef LINKEDSET_HPP_INCLUDED
#define LINKEDSET_HPP_INCLUDED

#include <iostream>
#include "set.hpp"

using namespace std;

template< class value_type >
class linkedset;

template< class value_type >
class node {
	friend class linkedset<value_type>;

private:
	value_type e;
	node<value_type>* next;
	node<value_type>* prev;
};

template< class value_type >
class linkedset : public set<value_type> {
public:
	//constructor
	linkedset();
	//copy constructor
	linkedset(const linkedset<value_type>&);
	//destructor
	~linkedset();

	//operator
	bool empty() const;
	bool belong(const value_type&) const;
	void insert(const value_type&);
	void erase(const value_type&);
	void merge(const linkedset<value_type>&);
	void intersection(const linkedset<value_type>&);
	void difference(const linkedset<value_type>&);
	int cardinality() const;
	void print_set() const;

private:
	node<value_type>* find(const value_type&) const;
	node<value_type>* head;
	int lenght;
};

template< class value_type >
linkedset<value_type>::linkedset() {
	node<value_type>* temp = new node<value_type>;
	this->head = temp;
	this->head->next = head;
	this->head->prev = head;
	lenght = 0;
}

template< class value_type >
linkedset<value_type>::linkedset(const linkedset<value_type>& s) {
	node<value_type>* temp = new node<value_type>;
	this->head = temp;
	this->head->next = head;
	this->head->prev = head;
	lenght = 0;
	node<value_type>* iter;
	iter = s.head->next;
	while (iter != s.head) {
		this->insert(iter->e);
		iter = iter->next;
	}
}

template< class value_type >
linkedset<value_type>::~linkedset() {
	node<value_type>* iter;
	iter = this->head->next;
	while (iter != this->head) {
		iter = iter->next;
		this->erase(iter->prev->e);
	}
	delete this->head;
}

template< class value_type >
bool linkedset<value_type>::empty() const {
	return (this->lenght == 0);
}

template< class value_type >
bool linkedset<value_type>::belong(const value_type& x) const {
	if (this->empty()) {
		return false;
	}
	node<value_type>* pos;
	pos = this->find(x);
	return (pos->e == x && pos != this->head);
}

template< class value_type >
void linkedset<value_type>::insert(const value_type& x) {
	if (this->empty()) {
		node<value_type>* temp = new node<value_type>;
		temp->e = x;
		temp->next = this->head;
		temp->prev = this->head;
		this->head->next = temp;
		this->head->prev = temp;
		lenght += 1;
	}
	else {
		node<value_type>* pos;
		pos = find(x);
		if (pos->e != x) {
			node<value_type>* temp = new node<value_type>;
			temp->e = x;
			temp->next = pos;
			temp->prev = pos->prev;
			pos->prev->next = temp;
			pos->prev = temp;
			lenght += 1;
		}
	}
}

template< class value_type >
void linkedset<value_type>::erase(const value_type& x) {
	if (!this->empty()) {
		node<value_type>* pos;
		pos = find(x);
		if (pos->e == x && pos != this->head) {
			pos->prev->next = pos->next;
			pos->next->prev = pos->prev;
			delete pos;
			lenght -= 1;
		}
	}
}

template< class value_type >
void linkedset<value_type>::merge(const linkedset<value_type>& s) {
	if (!s.empty()) {
		node<value_type>* iter;
		iter = s.head->next;
		while (iter != s.head) {
			this->insert(iter->e);
			iter = iter->next;
		}
	}
}

template< class value_type >
void linkedset<value_type>::intersection(const linkedset<value_type>& s) {
	if (s.empty()) {
		node<value_type>* iter;
		iter = this->head->next;
		while (iter != this->head) {
			this->erase(iter->e);
			iter = this->head->next;
		}
	}
	else {
		node<value_type>* iter;
		iter = this->head->next;
		while (iter != this->head) {
			if (!s.belong(iter->e)) {
				iter = iter->next;
				this->erase(iter->prev->e);
			}
			else {
				iter = iter->next;
			}
		}
	}
}

template< class value_type >
void linkedset<value_type>::difference(const linkedset<value_type>& s) {
	if (!s.empty()) {
		node<value_type>* iter;
		iter = this->head->next;
		while (iter != this->head) {
			if (s.belong(iter->e)) {
				iter = iter->next;
				this->erase(iter->prev->e);
			}
			else {
				iter = iter->next;
			}
		}
	}
}

template< class value_type >
int linkedset<value_type>::cardinality() const {
	return lenght;
}

template< class value_type >
node<value_type>* linkedset<value_type>::find(const value_type& x) const {
	if (this->empty()) {
		return this->head;
	}else{
		node<value_type>* iter;
		iter = this->head->next;
		while (iter != this->head && iter->e < x) {
			iter = iter->next;
		}
		return iter;
	}
}

template< class value_type >
void linkedset<value_type>::print_set() const {
	cout << "Set: [";
	node<value_type>* iter;
	iter = this->head->next;
	while (iter != this->head) {
		if (iter->next == this->head) {
			cout << iter->e;
		}
		else {
			cout << iter->e << ", ";
		}
		iter = iter->next;
	}
	cout << "]." << endl;
} 



#endif // !LINKEDSET_HPP_INCLUDED
