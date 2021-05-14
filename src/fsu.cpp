#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <boost/filesystem.hpp>

#include "include/stu.hpp"
#include "include/fsu.hpp"
#include "include/file.hpp"

using namespace std;

struct confpair{
    string name;
    string value;
};

bool real_direxists(string path)
{
    return boost::filesystem::is_directory(path);
}

bool fs_direxists(string path){
    return real_direxists(getrealpath(path));
}

void real_makedir(string path){
    boost::filesystem::create_directory(path);
}

void fs_makedir(string path){
    real_makedir(getrealpath(path));
}

void real_makefile(string path){
    ofstream f(path);
    f.close();
}

void fs_makefile(string path){
    real_makefile(getrealpath(path));
}

string joinpath(string path1, string path2){ // /home ..
    if(path2 == ".."){
        string sonp = "";
        vector<string> splp = splitstr(path1, '/');
        /*for(int i = 0; i < splp.size(); i++){
            if(i != splp.size() - 1){
                sonp += splp[i] + "/";
            }
        }

        sonp.pop_back();*/

        splp.pop_back();
        for(string s : splp){
            sonp += s + "/";
        }
        //sonp.pop_back();

        if(sonp.size() != 1){
            sonp.pop_back();
        }
        return sonp;
    }
    else if(path2 == "."){
        return path1;
    }
    else{
        string newp = "";

        bool b1 = false;
        bool f2 = false;
    
        if(path1[path1.size() - 1] == '/'){
            b1 = true;
        }

        if(path2[0] == '/'){
            f2 = true;
        }

        if(b1){
            newp += path1;
            newp.pop_back();
        }
        else{
            newp += path1;
        }

        newp += "/";

        if(f2){
            newp += path2.substr(1, path2.size());
        }
        else{
            newp += path2;
        }

        return newp;
    }
}

string getappdir() {
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    string appPath = string(result, (count > 0) ? count : 0);

    size_t found = appPath.find_last_of("/\\");
    return appPath.substr(0, found);
}

string getfspath(){
    return joinpath(getappdir(), "env/");
}

string getrealpath(string pathinfs){
    return joinpath(getfspath(), pathinfs.substr(1, pathinfs.size()));
}

vector<confpair> readconf(string realpath){
    vector<confpair> configuration;
    for(string ln : ReadAllLines(realpath)){
        if(trimstdstr(ln) != "" || trimstdstr(ln)[0] != '#'){
            vector<string> spl = splitstrcount(trimstdstr(ln), '=', 1);
            
            confpair pr;
            pr.name = spl[0];

            if(spl[1][0] == '\"' && spl[1][spl[1].size() - 1] == '\"'){
                pr.value = spl[1].substr(1, spl[1].size() - 2);
            }
            else{
                pr.value = spl[1];
            }

            configuration.push_back(pr);
        }
    }

    return configuration;
}

vector<confpair> fs_readconf(string fspath){
    return readconf(getrealpath(fspath));
}

string getconfval(string name, string confpath){
    for(auto x : fs_readconf(confpath)){
        if(x.name == name){
            return x.value;
        }
    }

    return "error";
}

string gethomepath(){
    return getconfval("HOME_PATH", "/etc/sysinfo");
}

string gethostname(){
    return trimstdstr(readfs("/etc/hostname")[0]);
}

vector<string> readfs(string fls){
    return ReadAllLines(getrealpath(fls));
}

bool writefs(string fls, string text){
    return WriteAllText(getrealpath(fls), text);
}

bool real_fileexists(string path){
    ifstream infile(path);
    return infile.good();
}

bool fs_fileexists(string path){
    return real_fileexists(getrealpath(path));
}

vector<pair<string, char>> getdirindex(string fspath){
    vector<pair<string, char>> files;
    using namespace boost::filesystem;
    directory_iterator end_itr;
    path p(getrealpath(fspath));
    for (directory_iterator itr(p); itr != end_itr; ++itr){
        pair<string, char> cfl;
        vector<string> cx = splitstr(itr->path().string(), '/');
        cfl.first = cx[cx.size() - 1];
        if (is_regular_file(itr->path())){
            cfl.second = 'f';
        }
        else if(is_directory(itr->path())){
            cfl.second = 'd';
        }
        else{
            cfl.second = 'u';
        }
        files.push_back(cfl);
    }
    return files;
}
