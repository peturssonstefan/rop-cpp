#include <iostream>
#include <string>
#include <ctime>


class Customer {
	public: 
		std::string name; 
		int id; 
		bool isVIP; 
		bool isActive; 
		Customer(std::string name, int id, bool vip, bool isActive = true): 
			name(name), id(id), isVIP(vip), isActive(isActive){}

};


class Transaction {
	public: 
		const Customer* customer; 
		int transactionNr; 
		int sisterTransaction; 
		int amount; 
		time_t created; 
		bool is3DSecure; 
		
		
		Transaction(const Customer* cust, int transNr, int amount, time_t created, bool is3ds, int sisterTransaction = 0)
			:customer(cust), transactionNr(transNr), amount(amount), created(created), is3DSecure(is3ds), sisterTransaction(sisterTransaction) {}
};
