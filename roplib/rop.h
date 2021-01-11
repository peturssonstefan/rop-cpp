#include <functional>
#include <string>
#include <exception>

template<typename T> 
class Result {
	const bool success; 
	T result; 
	const std::string errmsg; 

	public: 
	Result(bool success, T result): success(success), result(result){}
	Result(std::string errmsg): success(false), errmsg(errmsg){}

	bool failed(){
		return !success; 
	}
	std::string getErrMsg(){
		return errmsg; 
	}
	T getResult(){
		return result; 
	}
};

template<typename T, typename K, typename ... Args>
using F = Result<T> (K::*)(Args...);

template<typename T, typename K, typename X, typename ... Args>
using G = Result<T> (K::*)(X, Args...);

template<typename T, typename K, typename ... Args>
using H = void (K::*)(T, Args...); 

template<typename T, typename K, typename ... Args>
std::function<Result<T>()> compose(K* instance, F<T, K, Args...> func, Args ... args){
	return std::bind(func, instance, std::forward<Args>(args)...);
}

template<typename T, typename K, typename X, typename ... Args>
std::function<Result<T>(X)> consume(K* instance,  Result<T> (K::*func)(X, Args...), Args ... args){
	return std::bind(func, instance, std::placeholders::_1, std::forward<Args>(args)...);
}

template<typename T, typename K, typename ... Args> 
std::function<void(T)> comp(K* instance, H<K, T, Args...> func, Args ... args){
	return std::bind(func, instance, std::placeholders::_1, std::forward<Args>(args)...);
}

template<typename T>
Result<T> liftSuccessInput(T in){
	return Result<T>(true, in); 
}

template<typename T>
Result<T> liftFailedInput(T in, std::string errmsg){
	return Result<T>(false, in, errmsg); 
}

//create bind (standard)
template<typename T, typename K>
Result<K> operator >> (Result<T> previous, std::function<Result<K>(T)> func){
	if(previous.failed()){
		return Result<K>(previous.getErrMsg()); 
	}
	return func(previous.getResult()); 
}

template<typename T, typename K>
Result<K> operator >> (Result<T> previous, std::function<Result<K>()> func){
	if(previous.failed()){
		return Result<K>(previous.getErrMsg()); 
	}
	return func(); 
}

//Map
template<typename T, typename K>
Result<K> operator || (Result<T> previous, std::function<K(T)> func){
	if(previous.failed()){
		return Result<K>(previous.getErrMsg()); 
	}
	return Result<K>(true, func(previous.getResult())); 
}

template<typename T, typename K>
Result<K> operator || (Result<T> previous, std::function<K()> func){
	if(previous.failed()){
		return Result<K>(previous.getErrMsg()); 
	}
	return Result<K>(true, func()); 
}

//Tee (dead end funcs)
template<typename T>
Result<T> operator |= (Result<T> previous, std::function<void(T)> func){
	if(previous.failed()){
		return Result<T>(previous.getErrMsg()); 
	}
	func(previous.getResult());
	return Result<T>(true, previous.getResult()); 
}

template<typename T>
Result<T> operator |= (Result<T> previous, std::function<void()> func){
	if(previous.failed()){
		return Result<T>(previous.getErrMsg()); 
	}
	func();
	return Result<T>(true, previous.getResult()); 
}

//create try catch functions (... exceptions doesnt fit into this model.. so we force them )
template<typename T, typename K>
Result<K> operator >= (Result<T> previous, std::function<K(T)> func){
	if(previous.failed()){
		return Result<K>(previous.getErrMsg()); 
	}
	try{
		return Result<K>(true, func(previous.getResult())); 
	}
	catch(std::exception& e){
		return Result<K>(e.what()); 
	}
}

//Supervisory function
template<typename T, typename K>
Result<K> operator >= (Result<T> previous, std::pair<std::function<K(T)>, std::function<void()>> funcs){
	if(previous.failed()){
		funcs.second(); 
		return Result<K>(previous.getErrMsg()); 
	}
	return Result<K>(true, funcs.first(previous.getResult())); 
}

//create try catch functions (... exceptions doesnt fit into this model.. so we force them )

//create supervisory functions (something that acts on both error and success results)

//create closure. 



