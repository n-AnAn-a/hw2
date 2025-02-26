#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(const std::set<T>& s1, const std::set<T>& s2)
{
  std::set<T> common;
  for (typename std::set<T>::iterator c = s1.begin(); c != s1.end(); c++) {
    if (s2.find(*c) != s2.end()) {
      common.insert(*c);
    }
  }
  return common;
}
template <typename T>
std::set<T> setUnion(const std::set<T>& s1, const std::set<T>& s2)
{
  std::set<T> uni;

	typename std::set<T>::iterator x;
	typename std::set<T>::iterator y;
	for(x = s1.begin(); x != s1.end(); x++){
		uni.insert(*x);
	}

	for(y = s2.begin(); y != s2.end(); y++){
		if(uni.find(*y) == uni.end()){
			uni.insert(*y);
		}
	}
	return uni;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
