#ifndef _UTIL_H_
#define _UTIL_H_

#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <typeinfo>
#include <vector>
using namespace std;

class Util {
    public:
static string* strSplit(string strOrigin, string strTok) {
    int MAX_TOK = 15;
    int cutAt;  // 자르는 위치
    int index = 0;  // 문자열 인덱스
    int count = 0;
    string* strResult = new string[MAX_TOK]; 
		     
     while ( (cutAt = strOrigin.find_first_of(strTok)) != strOrigin.npos)
	          {
                 if (cutAt > 0)  // 자르는 위치가 0보다 크면
                         {
			    strResult[index++] = strOrigin.substr(0, cutAt);
			}
		    // 원본은 자른 부분을 제외한 나머지
		    strOrigin = strOrigin.substr(cutAt + 1);
		    }
								
		if (strOrigin.length() > 0) // 원본이 아직 남았으면
		{
		    strResult[index++] = strOrigin.substr(0, strOrigin.length());
		}                                                                                                         
		return strResult;
}
static vector<string> strSplit_vec(string strOrigin, string strTok) {
    int cutAt;  // 자르는 위치
    int index = 0;  // 문자열 인덱스
    int count = 0;
    vector<string> strResult; 
		     
     while ((cutAt = strOrigin.find_first_of(strTok)) != strOrigin.npos)
	          {
                 if (cutAt > 0)  // 자르는 위치가 0보다 크면
                         {
			    strResult.push_back(strOrigin.substr(0, cutAt));
			}
		    // 원본은 자른 부분을 제외한 나머지
		    strOrigin = strOrigin.substr(cutAt + 1);
		    }
								
		if (strOrigin.length() > 0) // 원본이 아직 남았으면
		{
		    strResult.push_back(strOrigin.substr(0, strOrigin.length()));
		}                                                                                                         
		return strResult;
}

static bool isNumber(const string &s){
    if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
    {
	return false;
    }
    char *p;
    double val = strtod(s.c_str(), &p);
    return p != s.c_str() && val != HUGE_VAL;
}

static double strToInt(const string &s){
    if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
    {
	cout << "It cannot convert from string to int. " << endl;
	assert(false);
    }
    char *p;
    long val = strtol(s.c_str(), &p, 10);
    if(p != s.c_str() && val != HUGE_VAL) return (int)val;
    assert(false);
}
static double strToUint(const string &s){
    if(s.empty() || ((!isdigit(s[0]))  && (s[0] != '+')))
    {
	cout << "It cannot convert from string to unsigned int. " << endl;
	assert(false);
    }
    char *p;
    unsigned long val = strtoul(s.c_str(), &p, 10);
    if(p != s.c_str() && val != HUGE_VAL) return (unsigned int)val;
    assert(false);
}
static double strToDouble(const string &s){
    if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
    {
	cout << "It cannot convert from string to double. " << endl;
	assert(false);
    }
    char *p;
    double val = strtod(s.c_str(), &p);
    if(p != s.c_str() && val != HUGE_VAL) return val;
    assert(false);
}
};
#endif
