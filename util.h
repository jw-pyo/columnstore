#ifndef _UTIL_H_
#define _UTIL_H_

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <typeinfo>

using namespace std;
#define	MAX_TOK	15


string* strSplit(string strOrigin, string strTok) {
    int cutAt;  // 자르는 위치
    int index = 0;  // 문자열 인덱스
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



template <typename T> T convert_to(std::string &str) {
    
    T val;
    std::stringstream ss(str);
    ss >> val;
    if(typeid(val).name() == typeid(str).name())
    {
	return (T)str;
    }
    return val;
}





#endif
