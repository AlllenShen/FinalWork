#include "SaleSystem.h"
#include <iostream>
#include <string>	
using namespace std;

void test(STORE & store, ENGINE & engine);
int main()
{	
	cout.setf(std::ios::left);
	STORE store = STORE();
	ENGINE engine = ENGINE(&store);
	string name[10]
	{ "a", "b", "c", "d", "e", 
		"f", "g", "h", "i", "j" };
	int price[10]
	{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int index[10]
	{ 1, 1, 3, 4, 5, 6, 7, 8, 9, 10 };
	for (int i = 0; i < 10; i++)
			store.add(name[i], price[i], index[i]);
	test(store, engine);
	/*string cmd;
	cout << "Welcome! Type \"help\" to get help.";
	while (1)
	{
		cout << "Choose mode:\n1-saler\t2-customer\n>";
		cin >> cmd;
		if (cmd == "1")
			engine.saler();
		if (cmd == "2")
			engine.customer();
		if (cmd == "\\q")
			return 0;
	}*/
	system("pause");
}

void test(STORE & store, ENGINE & engine)
{
	//store.delet();
	vector<GOODS>::const_iterator * f = store.find(1);
	int in = (**f).GetIndex();
	const GOODS & g = **f;
}
