#include <bits/stdc++.h>
using namespace std;

#include "include/colorizer.hpp"

string clgreen = "\e[32m";
string clred = "\e[31m";
string clcyan = "\e[36m";
string clwhite = "\e[37m";
string clyellow = "\e[33m";
string clblue = "\e[34m";

string bold = "\e[1m";
string reset = "\e[0m";

string colorize(string text, string col, bool ifbold)
{
    stringstream stream;

    string currentColor;

    if(col == "green")
    {
        currentColor = clgreen;
    }
    else if(col == "red")
    {
        currentColor = clred;
    }
    else if(col == "cyan")
    {
        currentColor = clcyan;
    }
    else if(col == "white")
    {
        currentColor = clwhite;
    }
    else if(col == "yellow")
    {
        currentColor = clyellow;
    }
    else if(col == "blue")
    {
        currentColor = clblue;
    }

    if(ifbold)
    {
        stream << bold << currentColor << text << reset;
    }
    else
    {
        stream << currentColor << text << reset;
    }

    return stream.str();
}