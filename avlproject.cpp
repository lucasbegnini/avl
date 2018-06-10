#include "stdafx.h"
#include <sstream>


int main(int argc, char* argv[])
{
	AvlTree t;
	string line,operation;
	int value;
	while (getline(cin, line))
	{
		std::istringstream iss(line);
		iss >> operation >> value;

		if (operation == "i") {
			t.insert(value);
		}
		else if (operation == "r") {
			t.remove(value);
		}
	}
	t.displayInorder();
	cout << endl;
	t.display();
	return 0;
}

