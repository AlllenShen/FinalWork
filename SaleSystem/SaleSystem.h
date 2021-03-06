#ifndef SALESTSTEM_H_
#define SALSESTEM_H_
#include <iostream>
//#include <fstream>
#include <string>
#include <vector>
using std::string;
using std::vector;

void FirstLine();
int handle(string cmd);
void help();
class GOODS
{
private:
	string name;
	int price;
	int index;
public:
	GOODS() {};
	GOODS(string, int, int);
	GOODS(const GOODS & g) { name = g.name; price = g.price; index = g.index; };
	virtual void show() const;
	void ReName(string name_) { name = name_; };
	void RePrice(int price_) { price = price_; };
	void ReIndex(int index_) { index = index_; };
	string GetName() const { return name; };
	int GetPrice() const { return price; };
	int GetIndex() const { return index; };
	bool operator==(const GOODS) const;
};
class STORE
{
private:
	vector<GOODS> GoodList;
public:
	STORE() {};
	//vector<GOODS>::const_iterator * find(int index_) const; //返回迭代器指针
	GOODS * find(int index_);
	void show(int begin) const;
	void add();
	void add(string name_, int price_, int index_);
	void change();
	void change(GOODS good);
	void delet();
	int size() const { return GoodList.size(); };
};
class SaleGood : public GOODS
{
private:
	int num;
	const GOODS * good;
public:
	SaleGood(const GOODS * good_, int num_); //注意这里使用指针
	virtual void show() const;
	void add(int num_ = 1) { num = num_; };
	void cancel(int num_);
	int GetNum() {return num;};
};
class CUSTOMER
{
private:
	vector<SaleGood> BuyList;
	int total;
	STORE * store; //错误的设计！为调用store中非const方法
public:
	CUSTOMER(STORE * store_ = NULL) { store = store_; };
	void show() const;
	//vector<SaleGood>::iterator * find(int index_); //返回迭代器指针
	SaleGood * find(int index_);
	void add(int index_, int num_);
	void cancel(int index_, int num_);
	vector<SaleGood> & GetList() { return BuyList; };
	int GetTotal() { return total; };
};
class ENGINE
{
private:
	vector<SaleGood> SaleList;
	int total;
	STORE * store;
public:
	ENGINE(STORE * store_) { total = 0; store = store_; };
	void ShowGoods() const;
	void saler();
	void customer();
	void end() const;
	void AddToStore(CUSTOMER & cus);
	//void DeletFromStore(const CUSTOMER & cus, int index_, int num_);

};
#endif