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

void FirstLine() //���������
{ 
	cout << "Index" << setw(8)
		<< "Name" << setw(8)
		<< "Price" << setw(8)
		<< "Number" << setw(8) << endl;
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
	else
		return -1;
}

//GOODS��
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
	//cout.setf(std::ios::left);
	cout << index << setw(8) 
		 << name << setw(8)
		 << price << setw(8) << endl;
}

//SaleGood��
SaleGood::SaleGood(const GOODS * good_ = NULL, int num_ = 0)
	:GOODS(*good_)
{
	num = num_;
	good = good_;
}
void SaleGood::show() const
{
	(*good).show();
	cout << num << setw(8) << endl;
}
void SaleGood::cancel(int num_ = 1)
{
	if (num_ > num)
	{
		cout << "There are only " << num
			<< "\nAre you sure to do?We'll clear ALL!(Y/N)";
		char c = '\0';
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

//CUSTOMER��
void CUSTOMER::show() const
{
	FirstLine();
	for (int i = 0; i < BuyList.size(); i++)
		BuyList[i].show();
}
vector<SaleGood>::iterator * CUSTOMER::find(int index_)
{
	/*for (int i = 0; i < BuyList.size(); i++)
		if (index_ == BuyList[i].GetIndex)
			return BuyList[i];*/
	vector<SaleGood>::iterator iter = BuyList.begin();
	while (iter != BuyList.end())
	{
		if ((*iter).GetIndex() == index_)
			return &iter;
	}
	return NULL;
}
void CUSTOMER::add(int index_, int num_)
{
	if (store->find(index_) == NULL)
	{
		cout << "The good DOES NOT exist!\nPlease check if index is right.\n";
		return;
	}
	vector<SaleGood>::iterator * item = find(index_);
	if (item != NULL)
	{
		(**item).add(num_);
		return;
	}
	GOODS g = **(store->find(index_)); //store_.find(index_) is a pointer to iter
	SaleGood good = SaleGood(&g, num_);
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
			BuyList[i].cancel(num_);
			total -= int(BuyList[i].GetPrice()) * num_;
			return;
		}
	cout << "Unkonwn Erro.Operation FAILED!\n";
}
void CUSTOMER::finish() const
{
	FirstLine();
	for (int i = 0; i < BuyList.size(); i++)
		BuyList[i].show();
	cout << "Total: " << total << endl;
}

//STORE��
vector<GOODS>::const_iterator * STORE::find(int index_) const
{
	/*for (int i = 0; i < GoodList.size(); i++)
		if (index_ == GoodList[i].GetIndex)
			return &(GoodList[i]);*/
	vector<GOODS>::const_iterator iter = GoodList.begin();
	while (iter != GoodList.end())
	{
		if ((*iter).GetIndex() == index_)
			return &iter;
	}
	return NULL;
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
}
void STORE::change()
{
	int index_;
	cout << "Input the index of good:";
	cin >> index_;
	while (find(index_) == NULL)
	{
		cout << "The index DOES NOT EXIST!\nPlease input another one:";
		cin >> index_;
	}
	GOODS g = **find(index_);
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
	/*for (int i = 0; i < GoodList.size; i++)
		if (GoodList[i].GetIndex == index_)
		{
			cout << "Sure to delete?(Y/N)";
			char c;
			cin >> c;
			if (c == 'Y')
				GoodList.erase(i);
			else
				cout << "Give up deleting.\n";
			return;
		}*/
	bool flag = 0;
	vector<GOODS>::iterator iter = GoodList.begin();
	while (iter != GoodList.end())
	{
		if (iter == *find(index_))
		{
			iter = GoodList.erase(iter); //delet
			flag = 1;
		}
		else
			iter++;
	}
	if (flag == 0)
		cout << "The item DOES NOT exist!\nPlease check index.\n";
}

//ENGINE��
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
			cout << "help\n";
			break;
		}
	}
}
void ENGINE::customer()
{
}
void ENGINE::end() const
{
}
void ENGINE::ShowGoods() const
{
	for (int i = 0; i < store->size(); i += SHOW_LEN)
		store->show(i);
}

