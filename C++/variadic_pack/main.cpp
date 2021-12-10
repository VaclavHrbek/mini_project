#include <iostream>

#include "json.hpp"

template<typename Ta, typename Tb>
Tb print_vp(Tb& json ,const Ta& val){
	return json[val];
}

template<typename T1, typename ... T>
void print_vp(T1& json, std::string&& key, const T& ... pack){
	nlohmann::json b = print_vp(json[key], pack...);
	std::cout << b.dump() << "\n";
}

template<typename ... T>
int fold_expresion(const T&& ... pack){
	//return (pack - ...);
	//return (... - pack);
	//return (pack - ... - 7);
	return (7 - ... - pack);
}

int main(){

	nlohmann::json json;
	json = {
  {"answer", {
    {"everything", 42}
  }},
  };
	

	print_vp(json, "answer", "everything");
	std::cout << fold_expresion(1, 2, 3) << "\n";
	
	return 0;
}
