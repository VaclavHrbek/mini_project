#include <iostream>
#include <cstdlib>
#include <stdlib.h>

template<typename T>
void set_env(const T& name, const T& val, const int& ower){
	setenv(name, val, ower);
}

template<typename T>
constexpr const char* get_env(const T& name){
	if(const char* env_p = std::getenv(name)){
		return env_p;
	}else{
		return "Nenalezeno";
	}
}

template<typename T>
constexpr void put_val(T& val){
	putenv(val);
}
int main(){
	set_env("NAME","VALU", 1);
	const char* env = get_env("NAME");
	std::cout << env << "\n";
	static char* a = "NAME=NEWVALUE";
	put_val(a);
	env = get_env("NAME");
	std::cout << env << "\n";

	return 0;
}
