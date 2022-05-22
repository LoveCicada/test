
/**
 * @file intersection.cpp
 * @author your name (you@domain.com)
 * @brief 颠倒字符串中的单词
 *  1. 移除多余空格
 *  2. 将整个字符串反转
 *  3. 将每个单词反转
 * 
 * @version 0.1
 * @date 2022-05-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/**
 * @brief 移除多余空格
 * 
 * @param str 
 */
void removeExtraSpaces(string& s) {
    int slowIdx = 0, fastIdx = 0;

    // 去掉字符串前面的空格
    while(s.size() > 0
        && fastIdx < s.size()
        && s[fastIdx] == ' '){
        fastIdx++;
    }

    for(; fastIdx < s.size(); fastIdx++){
        // 去掉字符串中间部分的冗余空格
        if(fastIdx - 1 > 0
            && s[fastIdx - 1] == s[fastIdx]
            && s[fastIdx] == ' '){
            continue;
        } else{
            s[slowIdx++] = s[fastIdx];
        }
    }

    if(slowIdx-1 > 0 && s[slowIdx-1] == ' '){
        // 去掉字符串末尾的空格
        s.resize(slowIdx-1);
    } else{
        s.resize(slowIdx);
    }
}

/**
 * @brief 反转字符串s中左闭右闭的区间[start, end]
 * 
 * @param s 
 * @param start 
 * @param end 
 */
void reverse(string& s, int start, int end){
    for(int i = start, j = end; i < j; i++, j--){
        swap(s[i], s[j]);
    }
}

/**
 * @brief 
 * 
 * @param s 
 * @return string 
 */
string reverseWords(string s) {
    removeExtraSpaces(s);
    reverse(s, 0, s.size()-1);
    
    for(int i = 0; i < s.size(); i++){
        int j = i;
        // 查找单词间的空格，反转单词
        while(j<s.size() && s[j] != ' '){
            j++;
        }
        reverse(s, i, j-1);
        i = j;
    }

    return s;
}

template<class T>
void printArray(const vector<T>& v){
    for(int i=0; i<v.size(); i++){
        cout << v[i] << " ";
    }
    cout << endl;
}


int main()
{
    string src = "  hello world  ";
    cout << "src = " << src << endl;
    string dst = reverseWords(src);
    cout << "dst = " << dst << endl;

    return 0;
}
/**
 * @result 

 */