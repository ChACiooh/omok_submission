#include "../header/parse_radix.h"
int square(int num, int e)
{
    if(e == 0)  return 1;
    int res = 1;
    for(int i=0;i<e;i++)
    {
        res *= num;
    }
    return res;
}

bool IsError(const string& str)
{
    vector<string> sv;
    split(sv, str, "_");
    if(sv.size() == 1)  return false; // decimal
    int num = atoi(sv[0].c_str());
    int radix = atoi(sv[1].c_str());
    while(num>0)
    {
        if(num%10 >= radix) return true;
        num /= 10;
    }
    return false;
}

int ParseRadix(const string& number)
{
    vector<string> sv;
    split(sv, number, "_");
    if(sv.size() == 1)  return atoi(sv[0].c_str());
    // exactly, sv[0] is number and sv[1] is radix.
    int num = atoi(sv[0].c_str());
    int radix = atoi(sv[1].c_str()), i=0;
    int result = 0;
    while(num>0)
    {
        result += (num%10)*square(radix, i++);
        num /= 10;
    }
    return result;
}

string ConvertRadix(int number, int radix)
{
    string res = "";
    while(number>0)
    {
        int r = number%radix;
        number /= radix;
        char cr = r+'0';
        if(r>9) cr = cr - '0' - 9 + 'a';
        res.append(&cr);
    }
    return res;
}

void split(vector<string>& sv, const string str, const string pivot)
{
    vector<size_t> pos_v;
    size_t past;
    for(size_t i=0;i+pivot.length()<str.length();i++)
    {
        if(!i) past = i;
        string sub_str = str.substr(i, pivot.length());
        if(sub_str == pivot)
        {
            pos_v.push_back(i);
            sv.push_back(str.substr(past, i-past));
            past = i+pivot.length();
        }
    }
}
