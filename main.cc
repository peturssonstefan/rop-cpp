#include <memory>
#include <iostream>
#include <string>
#include "businesslayer.h"

void log(std::string msg){
	std::cout << msg << std::endl; 
}

void error(std::string msg){
	std::cerr << "Error: " << msg << std::endl;
	exit(0);  
}

int main(int argc, char** argv){

	int customerId = atoi(argv[1]); 
	int amount = atoi(argv[2]); 
	auto bl = new BusinessLayer();
	auto dl = new DataLayer(); 

	auto res = initial >> compose(bl, &BusinessLayer::validateInput, customerId, 10)
	                   >> compose(dl, &DataLayer::getCustomerById, customerId)
					   >> consume(bl, &BusinessLayer::validateCustomer)
					   >> consume(dl, &DataLayer::createNewTransaction, amount, true) 
					   >> consume(bl, &BusinessLayer::validateTransaction)
					   >> consume(bl, &BusinessLayer::sendTransaction); 
	
	if(res.failed()){
		error(res.getErrMsg()); 
	}

	return 0; 


	// if(verify input failed..){
	// 	fail()...
	// }

	// //Get customer 
	// auto customerResult = dl->getCustomerById(std::get<0>(inputResult.getResult())); 
	// if(customerResult.failed()){
	// 	error("Fetching customers failed."); 
	// }

	//Validate customer
	// auto verificationResult = bl->validateCustomer(customerResult.getResult());
	// if(verificationResult.failed()){
	// 	error(verificationResult.getErrMsg());
	// }  

	//Setup trans

	//Validate trans 
	// auto validTransResult = bl->validateTransaction(trans); 
	// if(validTransResult.failed()){
	// 	error(validTransResult.getErrMsg());
	// }

	//Send transaction
	// auto sendResult = bl->sendTransaction(trans); 
	// if(sendResult.failed()){
	// 	error(sendResult.getErrMsg()); 
	// }

	//Finish
	std::cout << "Success" << std::endl; 
	
}

	// auto f = std::bind(func, dl, 5, false); 
	// auto g = compose(dl, &DataLayer::testFunc, 5, true); 
	// auto fG = consume(dl, &DataLayer::testFunc, true); 
	// auto res = fG(6); 


	int main(int argc, char** argv){
		auto dl = new DataLayer(); 
		auto bl = new BusinessLayer(); 
		int customerId = atoi(argv[1]); 
		int amount = atoi(argv[2]); 
		bl->validateInput(amount, customerId); 
		if(not valid input){
			log("bla");
			exit(-1); 
		}
		Customer* customer; 
		try{
			customer = dl->getCustomerById(customerId);
				if(customer == nullptr){
					log(":(");
					exit(-1);
				}
		}
		catch(exception e){
			log(e.msg);
			exit(-1);
		}

		dl->validateCustomer(customer); 
		if(not valid customer){
			log(....)
			exit(-1)
		}
		...
		...
		...
		return 0; 
	}

	let result = 
		input << validate
			  << fetchCustomer 
			  << validateCustomer 
			  << createTransaction
			  << validateTransaction
			  << sendTransaction 
	result