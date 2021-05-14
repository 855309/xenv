#include <bits/stdc++.h>
using namespace std;

struct confpair;

string getappdir();
string joinpath(string path1, string path2);
vector<confpair> fs_readconf(string fspath);
vector<confpair> readconf(string realpath);
string gethomepath();
string getfspath();
string gethostname();
vector<string> readfs(string fls);
bool writefs(string fls, string text);
bool real_fileexists(string path);
bool fs_fileexists(string path);
string getconfval(string name, string confpath);
string getrealpath(string pathinfs);
bool real_direxists(string path);
bool fs_direxists(string path);
vector<pair<string, char>> getdirindex(string fspath);
void fs_makedir(string path);
void real_makedir(string path);
void fs_makefile(string path);
void real_makefile(string path);
