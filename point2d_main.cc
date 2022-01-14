#include <map>
#include <string>
#include "header/point2d.h"
#include <cstdio>

int main()
{
    map<string, Point> points;
    while(true)
    {
        string command;
        cin >> command;
        if(command == "set")
        {
            string name, sx, sy;
            bool flag = false;
            cin >> name >> sx >> sy;
            // treat exception
            for(int i=0;i<sx.length();i++)
            {
                if(!isdigit(sx[i]) && sx[i]!='-')
                {
                    flag = true;
                    break;
                }
            }
            if(flag)    continue;

            for(int i=0;i<sy.length();i++)
            {
                if(!isdigit(sy[i]) && sy[i]!='-')
                {
                    flag = true;
                    break;
                }
            }
            if(flag)    continue;

            int x, y;
            sscanf(sx.c_str(), "%d", &x);
            sscanf(sy.c_str(), "%d", &y);
            points.insert(make_pair(name, Point(x,y)));
        }
        else if(command == "eval")
        {
            string oprnd1, oprnd2, oprtr;
            int i, opnd1, opnd2;
            Point op_point1, op_point2;
            cin >> oprnd1 >> oprtr >> oprnd2;

            for(i=0;i<oprnd1.length(); i++)
                if(!isdigit(oprnd1[i]) && oprnd1[i]!='-') break;
            if(i == oprnd1.length()) // this is a number
            {
                sscanf(oprnd1.c_str(), "%d", &opnd1);
                op_point1 = Point(opnd1);
            }
            else
            {
                bool flag = false;
                if(oprnd1[0] == '-')
                {
                    flag = true;
                    oprnd1.erase(oprnd1.begin());
                }
                map<string, Point>::const_iterator it = points.find(oprnd1);
                if(it != points.end())
                {
                    op_point1 = it->second;
                    if(flag)    op_point1 = -op_point1;
                }
                else
                {
                    cout << "input error" << endl;
                    continue;
                }
            }

            for(i=0;i<oprnd2.length(); i++)
                if(!isdigit(oprnd2[i]) && oprnd2[i]!='-') break;
            if(i == oprnd2.length()) // this is a number
            {
                sscanf(oprnd2.c_str(), "%d", &opnd2);
                op_point2 = Point(opnd2);
            }
            else
            {
                bool flag = false;
                if(oprnd2[0] == '-')
                {
                    flag = true;
                    oprnd2.erase(oprnd2.begin());
                }
                map<string, Point>::const_iterator it = points.find(oprnd2);
                if(it != points.end())
                {
                    op_point2 = it->second;
                    if(flag)    op_point2 = -op_point2;
                }
                else
                {
                    cout << "input error" << endl;
                    continue;
                }
            }

            if(oprtr == "+" || oprtr == "-" || oprtr == "*")
            {
                if(oprtr == "+")
                {
                    cout << op_point1 + op_point2;
                }
                else if(oprtr == "-")
                {
                    cout << op_point1 - op_point2;
                }
                else
                {
                    cout << op_point1 * op_point2;
                }
            }
        }
        else if(command == "quit")  break;
        else    break;
    }
    return 0;
}
