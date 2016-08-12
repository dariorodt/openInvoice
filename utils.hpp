/**
 * File: utils.hpp
 * @brief Several util tools for c++ coding.
 */
#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <sstream>
#include <ctime>
#include <string>

using namespace std;

/**
 * Get the global value.
 * @returns Returns the passed parameter converted in a string.
 */
template<class T> string to_string(T t) {
    ostringstream stm;
    stm << t;
    return stm.str();
}

int str_to_int(string str) {
	stringstream stm;
	int n;
	stm << str;
	stm >> n;
	return n; 
}

long str_to_long(string str) {
	stringstream stm;
	long n;
	stm << str;
	stm >> n;
	return n; 
}

double str_to_double(string str) {
	stringstream stm;
	double n;
	stm << str;
	stm >> n;
	return n; 
}

#endif