#include <bits/stdc++.h>
using namespace std;

struct command;
void initcommands();
bool builtincommandexists(string commandname);
void callbuiltincommand(string name, vector<string> args);
