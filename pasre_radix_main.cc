#include <iostream>
#include "header/parse_radix.h"

int main()
{
    while(true)
    {
        string command;
        cin >> command;
        if(command == "eval")
        {
            string oprnd1, oprtr, oprnd2, to_radix;
            int num1, num2;
            cin >> oprnd1 >> oprtr >> oprnd2;
            if(IsError(oprnd1) || IsError(oprnd2))
            {
                cout << "Error" << endl;
                continue;
            }

            num1 = ParseRadix(oprnd1);
            num2 = ParseRadix(oprnd2);

            if(oprtr == "==" || oprtr == ">" || oprtr == "<")
            {

                if(oprtr == "==")   cout << (num1 == num2) << endl;
                else if(oprtr == ">")   cout << (num1 > num2) << endl;
                else    cout << (num1 < num2) << endl;
            }
            else
            {
                string result;
                int i, radix;
                cin >> to_radix;
                for(i=0;i<to_radix.length();i++)
                    if(!isdigit(to_radix[i]))   break;
                if(i == to_radix.length())  radix = atoi(to_radix.c_str());
                else    continue;
                if(oprtr == "+")    result = ConvertRadix(num1+num2, radix);
                else if(oprtr == "-")   result = ConvertRadix(num1-num2, radix);
                else if(oprtr == "*")   result = ConvertRadix(num1*num2, radix);
                else    continue;
                cout << result << endl;
            }
        }
        else    break;
    }
    return 0;
}
