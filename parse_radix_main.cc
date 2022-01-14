#include <iostream>
#include "header/parse_radix.h"
#include <cstdio>

int main()
{
    while(true)
    {
        string command;
        cin >> command;
        getchar();
        if(command == "eval")
        {
            string statement;
            vector<string> vs;
            getline(cin, statement);
            split(&vs, statement, " ");

            if(IsError(vs[0]) || IsError(vs[2]))
            {
                cout << "Error" << endl;
                continue;
            }

            string op = vs[1];
            int val1 = ParseRadix(vs[0]), val2 = ParseRadix(vs[2]);

            if(vs.size() == 4)
            {
                int radix = atoi(vs[3].c_str()), result;
                string _radix = "_"+ConvertRadix(radix, 10);
                if(op == "+")   result = val1 + val2;
                else if(op == "*")  result = val1 * val2;
                else if(op == "-")  result = val1 - val2;
                else if(op == "/")  result = val1 / val2;
                else    continue; // invalid operator

                cout << ConvertRadix(result, radix) << (radix == 10 ? "" : _radix) << endl;
            }
            else if(vs.size() == 3)
            {
                if(op == "==")  cout << ((val1 == val2) ? "true" : "false") << endl;
                else if(op == ">")  cout << ((val1 > val2) ? "true" : "false") << endl;
                else if(op == "<")  cout << ((val1 < val2) ? "true" : "false") << endl;
                else    continue; // invalid operator
            }
            else    continue; // invalid input
        }
        else    break;
    }
    return 0;
}
