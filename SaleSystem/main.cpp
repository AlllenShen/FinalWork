#include "SaleSystem.h"
#include <iostream>
#include <string>	
using namespace std;

int main()
{
	STORE store = STORE();
	ENGINE engine = ENGINE(&store);
	string cmd;
	cout << "Welcome! Type \"help\" to get help.";
	while (1)
	{
		cout << "Choose mode:\n1-saler\t2-customer\n>";
		cin >> cmd;
		if (cmd == "1")
			engine.saler();

	}
}