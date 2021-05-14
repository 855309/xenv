#include <bits/stdc++.h>
using namespace std;

#include "include/fsu.hpp"
#include "include/session.hpp"
#include "include/colorizer.hpp"

struct command{
    string name;
    int (*action)(vector<string>);
};

vector<command> commands;

int getpathcm(vector<string> args){
    cout << getcurrentpath() << endl;
    return 0;
}

int sessioncm(vector<string> args){
    cout << getcurrentsession() << endl;
    return 0;
}

int cdcm(vector<string> args){
    if(fs_direxists(joinpath(getcurrentpath(), args[1]))){
        updatepath(joinpath(getcurrentpath(), args[1]));
    }
    else{
        cout << "cd: Directory not exists: " << joinpath(getcurrentpath(), args[1]) << endl;
    }

    return 0;
}

int lscm(vector<string> args){
    vector<pair<string, char>> pth = getdirindex(getcurrentpath());
    for(auto x : pth){
        if(x.first != "." || x.first != ".."){
            string filestr;
            
            filestr = x.first;
            if(x.second == 'f'){
                filestr = colorize(filestr, "", true);
            }
            else if(x.second == 'd'){
                filestr = colorize(filestr, "blue", true);
            }
            else{
                filestr = colorize(filestr, "red", true);
            }

            cout << filestr << endl;
        }
    }
    return 0;
}

int mkdircm(vector<string> args){
    fs_makedir(joinpath(getcurrentpath(), args[1]));
    return 0;
}

int touchcm(vector<string> args){
    fs_makefile(joinpath(getcurrentpath(), args[1]));
    return 0;
}

int catcm(vector<string> args){
    for(string ln : readfs(joinpath(getcurrentpath(), args[1]))){
        cout << ln << endl;
    }
    return 0;
}

void initcommands(){
    command gp = {
        .name = "getpath",
        .action = getpathcm
    };
    commands.push_back(gp);

    command se = {
        .name = "session",
        .action = sessioncm
    };
    commands.push_back(se);

    command cdcomm = {
        .name = "cd",
        .action = cdcm
    };
    commands.push_back(cdcomm);

    command lscomm = {
        .name = "ls",
        .action = lscm
    };
    commands.push_back(lscomm);

    command mkdircomm = {
        .name = "mkdir",
        .action = mkdircm
    };
    commands.push_back(mkdircomm);
    
    command touchcomm = {
        .name = "touch",
        .action = touchcm
    };
    commands.push_back(touchcomm);

    command ccm = {
        .name = "cat",
        .action = catcm
    };
    commands.push_back(ccm);
}

void callbuiltincommand(string name, vector<string> args){
    for(command com : commands){
        if(com.name == name){
            try{
                int (*action)(vector<string>);
                action = com.action;
                action(args);
            }
            catch(const std::exception& e){
                cout << colorize("error: ", "red", true) << e.what() << endl;
            }
            
            break;
        }
    }
}

bool builtincommandexists(string commandname){
    for(command com : commands){
        if(com.name == commandname){
            return true;
        }
    }

    return false;
}
