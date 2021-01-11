#include "rop.h"
#include "models.h"
#include <vector>
#include <algorithm>

class DataLayer {
	public: 
	std::vector<Customer*> customers = std::vector<Customer*>{
				new Customer("Stefan", 0, true),
				new Customer("Stephen", 1, true),
				new Customer("Steven", 2, true),
				new Customer("Stefano", 3, true),
				new Customer("Seth", 4, false, false),
				new Customer("Eric", 5, false)
	};
		
	Result<std::vector<Customer*>> getCustomers(); 

	Result<std::vector<Transaction*>> getTransactions(); 

	Result<Customer*> getCustomerById(int id); 

	Result<Transaction*> createNewTransaction(Customer* customer, int amount, bool is3DS);   

	Result<int> testFunc(int a, bool b); 
		
};

