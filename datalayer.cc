#include "datalayer.h"

Result<std::vector<Customer*>> DataLayer::getCustomers(){
	return Result<std::vector<Customer*>>(true, this->customers); 
}

Result<std::vector<Transaction*>> DataLayer::getTransactions(){
	return Result<std::vector<Transaction*>>(true,std::vector<Transaction*>{});
}



Result<Customer*> DataLayer::getCustomerById(int id){
	auto customer = Customer("", id, false);

	auto it = std::find_if(this->customers.begin(), this->customers.end(), [id](Customer* cust){
		return cust->id == id; 
	});

	return it == this->customers.end() ? 
		Result<Customer*>("Could not find customer given id : " + std::to_string(id)) :
		Result<Customer*>(true, *it);
				
}

Result<int> DataLayer::testFunc(int a, bool b){
	return b ? Result<int>(true, a) : Result<int>("err");
} 

Result<Transaction*> DataLayer::createNewTransaction(Customer* customer, int amount, bool is3DS){
	return Result<Transaction*>(true, new Transaction(customer, 1, amount, time(0), is3DS));
}