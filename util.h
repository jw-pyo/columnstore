#ifndef _UTIL_H_
#define _UTIL_H_

#include <string>
#include <sstream>
#include <fstream>

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
		    strResult[index++] = strOrigin.substr(0, cutAt);
		}                                                                                                         
		return strResult;
}

template <typename T> T convert_to(const std::string &str) {
    std::istringstream ss(str);
    T val;
    ss >> val;
    return val;
}
#endif
