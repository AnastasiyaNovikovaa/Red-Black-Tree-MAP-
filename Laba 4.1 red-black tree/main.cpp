#include "Red-Black-Tree.cpp"
#include <conio.h>
#include <iostream>
#include <string>

int main()
{
	cout << "Laboratory work number 2\n";
	cout << "by Novikova Anastasiya";
	cout << endl;
	cout << "Keys of Red-Black Tree:";
	cout << endl;

	Map<int, int> RBTree_int;
	RBTree_int.insert(3, 3); 
	RBTree_int.insert(6, 8);  
	RBTree_int.insert(1, 5);  
	RBTree_int.insert(0, 4);
	RBTree_int.insert(7, 0);
	RBTree_int.insert(4, 7);
	RBTree_int.insert(2, 2);
	RBTree_int.get_keys();
	cout << endl;
	cout << "Value of Red-Black Tree:";
	cout << endl;
	RBTree_int.get_value();
	cout << endl;
	cout << "Size of Red-Black Tree:";
	cout << RBTree_int.get_size();
	cout << endl;
	cout << "Keys of Red-Black Tree after removing 7:";
	cout << endl;
	RBTree_int.remove(7);
	RBTree_int.get_keys();
	cout << endl;
	cout << "Find Key=4 of Red-Black Tree:";
	RBTree_int.find(4);
	cout << endl;
	RBTree_int.clear();
	cout << endl;
	cout << "<3<3<3<3<3<3<3<3<3<3<3<3<3<3<3<3<3<3<3<3<3<3<3<3<3<3\n";
	cout << endl;
	Map<int, char> RBTree_char;
	RBTree_char.insert(13, 'a');
	RBTree_char.insert(9, 'b');
	RBTree_char.insert(12, 'c');
	RBTree_char.insert(14, 'd');
	RBTree_char.insert(7, 'f');
	cout << "Keys of Red-Black Tree:";
	cout << endl;
	RBTree_char.get_keys();
	cout << endl;
	cout << "Value of Red-Black Tree:";
	cout << endl;
	RBTree_char.get_value();
	cout << endl;
	cout << "Size of Red-Black Tree:";
	cout << RBTree_char.get_size();
	cout << endl;
	RBTree_char.clear();

	cout << endl;
	cout << "GoodBuy! Have a nice day :)";
	_getch();
	
}