#include "SaleSystem.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::setw;
const int SHOW_LEN = 10;

void FirstLine() //输出标题行
{ 
	cout << setw(8) << "Index"
		<< setw(8) << "Name"
		<< setw(8) << "Price"
		<< setw(8) << "Number"  << endl;
}
int handle(string cmd)
{
	if (cmd == "\\q")
		return 1;
	else if (cmd == "add")
		return 2;
	else if (cmd == "change")
		return 3;
	else if (cmd == "delet")
		return 4;
	else if (cmd == "show_goods")
		return 5;
	else if (cmd == "show_chart")
		return 6;
	else if (cmd == "end")
		return 7;
	else if (cmd == "help")
		return 8;
	else if (cmd == "\n")
		return 9;
	else
		return -1;
}
void SalerHelp()
{
	cout << setw(15) << "\\q" << "Exit the mode.\n"
		<< setw(15) << "show_goods" << "Show items in store.\n"
		<< setw(15) << "add" << "Add item to store.\n"
		<< setw(15) << "change" << "Change item in store.\n"
		<< setw(15) << "delet" << "Delet item in store.\n"
		<< setw(15) << "end" << "Finish and show item solde.\n";
}
void CustomerHele()
{
	cout << setw(15) << "\\q" << "Exit the mode.\n"
		<< setw(15) << "show_goods" << "Show items in store.\n"
		<< setw(15) << "show_chart" << "Show items in chart.\n"
		<< setw(15) << "add" << "Add item to chart.\n"
		<< setw(15) << "delet" << "Delet item in chart.\n"
		<< setw(15) << "end" << "Finish and show items.\n";
}

//GOODS类
GOODS::GOODS(string name_ = string('\0'), int price_ = NULL, int index_ = NULL)
{
	name = name_;
	price = price_;
	index = index_;
	if (&name == NULL)
		cout << "Warnning: Name is NULL!\n";
	if (price == NULL)
		cout << "Warnning: Price is NULL!\n";
	if (index == NULL)
		cout << "Warnning: Index is NULL!\n";
}
void GOODS::show() const
{
	cout << setw(8) << index
		<< setw(8) << name
		<< setw(8) << price  << endl;
}
bool GOODS::operator==(const GOODS good) const
{
	if (this->index == good.GetIndex()
		&& this->name == good.GetName()
		&& this->price == good.GetPrice())
		return true;
	else
		return false;
}

//SaleGood类
SaleGood::SaleGood(const GOODS * good_ = NULL, int num_ = 0)
	:GOODS(*good_)
{
	num = num_;
	good = good_;
}
void SaleGood::show() const
{
	cout << setw(8) << (*good).GetIndex()
		<< setw(8) << (*good).GetName()
		<< setw(8) << (*good).GetPrice()
		<< setw(8) << num  << endl;
}
void SaleGood::cancel(int num_ = 1)
{
	if (num_ > num)
	{
		cout << "There are only " << num
			<< "\nAre you sure to do?We'll clear ALL!(Y/N)\n";
		char c = '\0';
		cin >> c;
		if (c == 'Y' || c == 'y')
		{
			num = 0;
			cout << "Clear\n";
			return;
		}
		else if (c == 'N' || c == 'n')
			return;
		else
		{
			cout << "Wrong Type!";
			return;
		}
	}
	num -= num_;
}

//CUSTOMER类
void CUSTOMER::show() const
{
	FirstLine();
	for (int i = 0; i < BuyList.size(); i++)
		BuyList[i].show();
	cout << "Total:" << total << endl;
}
SaleGood * CUSTOMER::find(int index_)
{
	for (int i = 0; i < BuyList.size(); i++)
		if (BuyList[i].GetIndex() == index_)
			return &BuyList[i];
	return NULL;
}
void CUSTOMER::add(int index_, int num_)
{
	if (store->find(index_) == NULL)
	{
		cout << "The good with index:" << index_
			<< " DOES NOT exist!\nPlease check if index is right.\n";
		return;
	}
	//vector<SaleGood>::iterator * item = find(index_);
	SaleGood * item = find(index_);
	if (item != NULL)
	{
		(*item).add(num_);
		return;
	}
	//GOODS g = *(store->find(index_)); 
	SaleGood good = SaleGood(store->find(index_), num_);
	BuyList.push_back(good);
	total += good.GetPrice() * num_;
}
void CUSTOMER::cancel(int index_, int num_ = 1)
{
	if (find(index_) == NULL)
	{
		cout << "The item IS NOT in your chart!\nPlease check if index is right.\n";
		return;
	}
	for (int i=0; i < BuyList.size(); i++)
		if (BuyList[i].GetIndex() == index_)
		{
			int pnum = BuyList[i].GetNum(); //减少前的个数
			BuyList[i].cancel(num_);
			int rnum = BuyList[i].GetNum();
			total -= BuyList[i].GetPrice() * (pnum - rnum);
			return;
		}
	cout << "Unkonwn Erro.Operation FAILED!\n";
}

//STORE类

//	this implementation will cause fatal exception
//
//vector<GOODS>::const_iterator * STORE::find(int index_) const
//{
//	vector<GOODS>::const_iterator iter = GoodList.begin();
//	for (;iter != GoodList.end(); iter++)
//		if ((*iter).GetIndex() == index_)
//			return &iter;
//	return NULL;
//}

GOODS * STORE::find(int index_)
{
	for (int i = 0; i < GoodList.size(); i++)
		if (GoodList[i].GetIndex() == index_)
			return &GoodList[i];
	return nullptr;
}
void STORE::show(int begin) const
{
	if (begin >= GoodList.size())
	{
		cout << "Beyond!";
		return;
	}
	else if (begin + SHOW_LEN >= GoodList.size())
	{
		for (int i = begin; i < GoodList.size(); i++)
			GoodList[i].show();
		return;
	}
	else
		for (int i = begin; i < 1 + 10; i++)
		{
			GoodList[i].show();
			show(i + 1);
		}

}
void STORE::add()
{
	string name_;
	int price_, index_;
	cout << "Name:";
	cin >> name_;
	cout << "Price:";
	cin >> price_;
	cout << "Index:";
	cin >> index_;
	while (find(index_) != NULL)
	{
		cout << "The index has already EXIST!\nPlease input another one:";
		cin >> index_;
	}
	GOODS NewGood = GOODS(name_, price_, index_);
	GoodList.push_back(NewGood);
	cout << "New item added succesfully.\n";
	FirstLine();
	NewGood.show();
}
void STORE::add(string name_, int price_, int index_)
{
	if (find(index_) != NULL)
	{
		cout << "The index has already EXIST!\nPlease input another one:";
		return;
	}
	GOODS NewGood = GOODS(name_, price_, index_);
	GoodList.push_back(NewGood);
	cout << "New item added succesfully.\n";
}
void STORE::change()
{
	int index_;
	cout << "Input the index of good:";
	cin >> index_;
	//vector<GOODS>::const_iterator * f = find(index_);
	GOODS * f = find(index_);
	while (f == NULL) 
	{
		cout << "The index DOES NOT EXIST!\nPlease input another one:";
		cin >> index_;
		f = find(index_);
	}
	GOODS g = *f;
	FirstLine();
	g.show();
	cout << "Which do you want to change?\nName(n) Price(p) Index(i)\n";
	char c;
	cin >> c;
	switch (c)
	{
	case 'n': case 'N':
	{
		string name_;
		cout << "New name:";
		cin >> name_;
		for (int i = 0; i < GoodList.size(); i++)
			if (GoodList[i].GetIndex() == index_)
			{
				GoodList[i].ReName(name_);
				cin.ignore(1024, '\n'); //清除缓存
				return;
			}
		cout << "Unkonwn erro happened!Change FAILED!";
		break;
	}
	case 'p': case 'P':
	{
		int price_;
		cout << "New price:";
		cin >> price_;
		for (int i = 0; i < GoodList.size(); i++)
			if (GoodList[i].GetIndex() == index_)
			{
				GoodList[i].RePrice(price_);
				return;
			}
		cout << "Unkonwn erro happened!Change FAILED!";
		break;
	}
	case 'i': case 'I':
	{
		int NewIndex;
		cout << "New index:";
		cin >> NewIndex;
		while (find(NewIndex) != NULL)
		{
			cout << "The index has already existed.\nIndex:";
			cin >> NewIndex;
		}
		for (int i = 0; i < GoodList.size(); i++)
			if (GoodList[i].GetIndex() == index_)
			{
				GoodList[i].ReIndex(NewIndex);
				return;
			}
		cout << "Unkonwn erro happened!Change FAILED!";
		break;
	}
	default:
		cout << "Wrong type!";
		break;
	}
}
void STORE::change(GOODS good)
{
	cout << "Which do you want to change?\nName(n) Price(p) Index(i)\n";
	char c;
	cin >> c;
	switch (c)
	{
	case 'n': case 'N':
	{
		string name_;
		cout << "New name:";
		cin >> name_;
		good.ReName(name_);
		break;
	}
	case 'p': case 'P':
		int price_;
		cout << "New price:";
		cin >> price_;
		good.RePrice(price_);
		break;
	case 'i': case 'I':
		int NewIndex;
		cout << "New index:";
		cin >> NewIndex;
		good.ReIndex(NewIndex);
		break;
	default:
		cout << "Wrong type!";
		break;
	}
}
void STORE::delet()
{
	int index_;
	cout << "Index:";
	cin >> index_;
	bool flag = 0;
	vector<GOODS>::iterator iter = GoodList.begin();
	GOODS * f = find(index_);
	if (f == NULL)
	{
		cout << "The item with index:" << index_
			<< " does NOT exist.\n";
		return;
	}
	for (; iter != GoodList.end(); iter++)
	{
		if ((*iter).GetIndex() == (*f).GetIndex())  
		{
			iter = GoodList.erase(iter); //delet 
			flag = 1;
			return;
		}
		/*else
			iter++;*/
	}
	if (flag == 0)
		cout << "The item DOES NOT exist!\nPlease check index.\n";
}

//ENGINE类
void ENGINE::saler()
{
	while (true)
	{
		string cmd;
		cout << "Saler$ ";
		cin >> cmd;
		int h = handle(cmd);
		if (h == -1)
			cout << "Command \"" << cmd << "\" can't be found.Type \"help\" to get help.\n";
		if (h == 1)
			break;
		if (h == 9)
			continue;
		switch (h)
		{
		case 2:
			store->add();
			break;
		case 3:
			store->change();
			break;
		case 4:
			store->delet();
			break;
		case 5:
			ShowGoods();
			break;
		case 7:
			end();
			break;
		case 8:
			SalerHelp();
			break;
		}
	}
}
void ENGINE::customer()
{
	CUSTOMER customer = CUSTOMER(store);
	string cmd;
	while (1)
	{
		cout << "Customer$ ";
		cin >> cmd;
		int h = handle(cmd);
		if (h == -1)
			cout << "Command \"" << cmd << "\" can't be found.Type \"help\" to get help.\n";
		if (h == 1)
			break;
		if (h == 9)
			continue;
		if (h == 7)
		{
			AddToStore(customer);
			customer.show();
			cout << "Thank you!\n";
			break;
		}
		switch (h)
		{
			case 6: //show_chart
				customer.show();
				break;
			case 2: //add
			{
				int item[20][2], i = 0, a; //存放选择信息
				cout << "FORM \"Index, Num\"\nType \';\' to finishi add.\n->";
				while (cin >> item[i][0])
				{
					cin >> item[i][1];
					i++;
				}
				cin.clear();
				cin.get(); //重置输入流
				for (int j = 0; j < i; j++)
					customer.add(item[j][0], item[j][1]);
				break;
			}
			case 5: //show_goods
				ShowGoods();
				break;
			case 4: //delet
			{
				int item[20][2], i = 0; //存放选择信息
				cout << "FORM \"Index Num\"\nType \';\' to finishi delet.\n->";
				while (cin >> item[i][0])
				{
					cin >> item[i][1];
					i++;
				}
				cin.clear();
				cin.get(); //重置输入流
				for (int j = 0; j < i; j++)
					customer.cancel(item[j][0], item[j][1]);
				break;
			}
			case 8:
				CustomerHele();
				break;
		}
	}
}
void ENGINE::end() const
{
	FirstLine();
	for (int i = 0; i < SaleList.size(); i++)
		SaleList[i].show();
	cout << "Total: " << total << endl;
}
void ENGINE::AddToStore(CUSTOMER & cus)
{
	vector<SaleGood> & BuyList = cus.GetList();
	for (int i = 0; i < BuyList.size(); i++)
		SaleList.push_back(BuyList[i]);
	total += cus.GetTotal();
}
void ENGINE::ShowGoods() const
{
	FirstLine();
	for (int i = 0; i < store->size(); i += SHOW_LEN)
		store->show(i);
}

