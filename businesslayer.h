#include <string>
#include <tuple>
#include "datalayer.h"

class BusinessLayer {
	public: 
	Result<std::pair<int, int>> validateInput(int id, int amount);
	Result<Customer*> validateCustomer(Customer* customer); 
	Result<Transaction*> validateTransaction(Transaction* trans);
	Result<Transaction*> sendTransaction(Transaction* trans);
	void writeTransToFile(Transaction* trans); 
};
