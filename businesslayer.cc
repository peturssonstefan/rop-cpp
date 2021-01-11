#include <numeric>
#include "businesslayer.h"
#include <functional>

Result<Customer*> BusinessLayer::validateCustomer(Customer* customer){
	return customer->name.find("S") == std::string::npos ? 
			Result<Customer*>("Customer does not meet name criteria"):
			Result<Customer*>(true, customer); 
}

Result<std::pair<int,int>> BusinessLayer::validateInput(int id, int amount){
	if(id < 0 || id > 100){
		return Result<std::pair<int,int>>("Given customer id not valid");
	}
	if(amount < 0 || amount > 10000){
		return Result<std::pair<int,int>>("Given amount not valid");
	}

	return Result<std::pair<int,int>>(true, {id, amount}); 
}

Result<Transaction*> BusinessLayer::validateTransaction(Transaction* trans){
	return (trans->amount > 25 && !trans->customer->isVIP) ?
			Result<Transaction*>("Customer " + trans->customer->name + " cannot transact an amount of size " + std::to_string(trans->amount)): 
			Result<Transaction*>(true, trans);  
	
}

Result<Transaction*> BusinessLayer::sendTransaction(Transaction* trans){
	bool success = false;
	srand(time(0)); 
 
	for(int i = 0 ; i < 3; i++){
		if((rand() % 2) == 0) {
			success = true; 
			std::cout << "Sending trans succeeded!" << std::endl; 
			break; 
		}
		std::cout << "Sending trans failed!" << std::endl; 
	}

	return success ? 
		   Result<Transaction*>(true, trans):
		   Result<Transaction*>("Could not send transaction"); 
}

void BusinessLayer::writeTransToFile(Transaction* trans){
	std::cout << "Trans " << trans->transactionNr << " with amount " << trans->amount << " has been written to file" << std::endl; 
} 