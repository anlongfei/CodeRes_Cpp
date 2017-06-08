#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/algorithm/string.hpp>


int main()
{
    using namespace std;

    // NOTE!!! 分隔符出现在开头或末尾会导致最后空字符串的产生
    // 所以一般在split之前先用分隔符trim
    string line = "123,4,,5,6,"; 
    vector<string> values;
    boost::split(values, line, boost::is_any_of(","), boost::token_compress_on);
    
    cout << values.size() << endl;
    for (auto &v : values) {
        if (v.empty())
            cout << "null" << endl;
        else
            cout << v << endl;
    } // for

    //!! 或者在split之后做以下操作
    auto newEnd = std::remove_if(values.begin(), values.end(), [](const string &s){
        return s.empty();
    });
    values.erase(newEnd, values.end());
    cout << values.size() << endl;

    return 0;
}

#if 0
5
123
4
5
6
null
#endif

