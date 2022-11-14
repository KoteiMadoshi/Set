#include <iostream>
#include "arrayset.hpp"
#include "linkedset.h"

using namespace std;

int main(int argc, char* argv[]) {
	int dim = 20;
	//arrayset<int> A(dim);
	linkedset<int> A;

	cout << "Set A created:" << endl;
	A.print_set();
	cout << "Cardinality: " << A.cardinality() << "." << ((A.empty()) ? " Set empty." : " Set not empty.") << endl << endl;

	for (int i = 0; i < dim / 2; ++i) {
		A.insert(i + 1);
	}

	cout << "Set A filled of elements from 1 to " << dim / 2 << ":" << endl;
	A.print_set();
	cout << "Cardinality: " << A.cardinality() << "." << ((A.empty()) ? " Set empty." : " Set not empty.") << endl << endl;

	for (int i = 0; i < dim; ++i) {
		A.insert(i + 1);
	}

	cout << "Set A filled with elemets from 1 to " << dim << " (excluding the repeated ones):" << endl;
	A.print_set();
	cout << "Cardinality: " << A.cardinality() << "." << endl << endl;

	int erase = 20;
	A.erase(erase);

	cout << "Set A after the erase of element \"" << erase << "\":" << endl;
	A.print_set();
	cout << "Cardinality: " << A.cardinality() << "." << endl << endl;

	int belong = 11;
	cout << "Element " << erase << ": ";
	cout << ((A.belong(erase)) ? "Element contained in the set." : "Element not contained in the set.") << endl;
	cout << "Element " << belong << ": ";
	cout << ((A.belong(belong)) ? "Element contained in the set." : "Element not contained in the set.") << endl << endl;

	//arrayset<int> B(A);
	linkedset<int> B(A);

	cout << "Set B created with copy constructor: " << endl;
	B.print_set();
	cout << "Cardinality: " << B.cardinality() << "." << endl << endl;

	for (int i = 0; i < dim; ++i) {
		B.erase(i + 1);
	}

	for (int i = 0; i < dim; ++i) {
		B.insert(i + dim / 2);
	}

	cout << "Set B cleared and filled with elements from " << dim / 2 << " to " << (dim - 1) + dim / 2 << ":" << endl;
	B.print_set();
	cout << "Cardinality: " << B.cardinality() << "." << endl << endl;

	//arrayset<int> C(dim * 5);
	linkedset<int> C;

	cout << "______________________________________________________________________" << endl << endl;

	cout << "Set A:" << endl;
	A.print_set();
	cout << "Cardinality: " << A.cardinality() << "." << endl << endl;
	cout << "Set B:" << endl;
	B.print_set();
	cout << "Cardinality: " << B.cardinality() << "." << endl << endl;

	C.merge(A);
	C.merge(B);

	cout << "Set C = A UNITED B:" << endl;
	C.print_set();
	cout << "Cardinality: " << C.cardinality() << "." << endl << endl;

	//arrayset<int> D(A);
	linkedset<int> D(A);
	D.intersection(B);

	cout << "Set D = A INTERSECTION B:" << endl;
	D.print_set();
	cout << "Cardinality: " << D.cardinality() << "." << endl << endl;

	//arrayset<int> E(A);
	linkedset<int> E(A);
	E.difference(B);

	cout << "Set E = A DIFFERENCE B:" << endl;
	E.print_set();
	cout << "Cardinality: " << E.cardinality() << "." << endl << endl;
	

	cout << endl;
	system("PAUSE");
	return 0;
}