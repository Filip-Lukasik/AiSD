#include "add.h"

inline void result_push(char number , std::stack<char>& results){
	if(number > '9'){
		results.push(number - 10);
		results.push('1');
	}
	else{
		results.push(number);
		results.push('0');
	}
}

std::string add(std::string a,std::string b){
	std::stack<char> as;
	std::stack<char> bs;
	char number;
	std::stack<char> results;
	results.push('0');
	std::string result;
	for(char digit : a){
		as.push(digit - '0');
	}
	for(char digit : b){
		bs.push(digit - '0');
	}
	while( !( as.empty() ) && !( bs.empty() ) ){
		number = as.top() + bs.top() + results.top();
		as.pop();
		bs.pop();
		results.pop();
		result_push(number , results);
	}
	while( !as.empty() ){
		number = as.top() + results.top();
		as.pop();
		results.pop();
		result_push(number , results);	
	}
	while( !bs.empty() ){
		number = bs.top() + results.top();
		bs.pop();
		results.pop();
		result_push(number , results);
	}
	if(results.top() == '0'){
		results.pop();
	}
	while( !results.empty() ){
		result += results.top();
		results.pop();
	}
	return result;
}
