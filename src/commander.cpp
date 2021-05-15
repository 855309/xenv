#include <bits/stdc++.h>
#include <readline/readline.h>
#include <readline/history.h>
using namespace std;

#include "include/stu.hpp"
#include "include/fsu.hpp"
#include "include/commander.hpp"
#include "include/session.hpp"
#include "include/colorizer.hpp"
#include "include/builtin.hpp"

string inputstr = "";

int startubProc(string proc, vector<string> args){
    args.erase(args.begin());
    string argstr = "";
    for(string arg : args){
        argstr += arg + " ";
    }

    string comm = "cd " + getrealpath(getcurrentpath()) + " && " + getrealpath(joinpath("/usr/bin/", proc)) + " " + trimstdstr(argstr);
    return system(comm.c_str());
}

int startvaultProc(string proc, vector<string> args){
    args.erase(args.begin());
    string argstr = "";
    for(string arg : args){
        argstr += arg + " ";
    }

    string comm = "cd " + getrealpath(getcurrentpath()) + " && " + getrealpath(joinpath("/usr/vault/" + proc + "/", proc)) + " " + trimstdstr(argstr);
    return system(comm.c_str());
}

string getpathstr(){
    string path = getcurrentpath();

    if(path == "/home"){
        return "~";
    }
    else{
        return path;
    }
}

void cnf(string c){
    cout << colorize("xenv2:", "", true) << " command not found: " << colorize(c, "red", true) << endl;
}

void commander::startinput(){
    // start a xenv session
    createsession();

    // initialize built-in commands
    initcommands();

    rl_bind_key('\t', rl_insert);

    // main input loop :)
    while(1){
        inputstr = colorize("[" + trimstdstr(readfs("/etc/defaultuser")[0]) + "@" + gethostname() + " ", "green", true) + colorize(getpathstr(), "", true) + colorize("]$ ", "green", true);
        
        //cout << inputstr;
        string inp;
        //getline(std::cin, inp);
        inp = readline(inputstr.c_str());
        inp = trimstdstr(inp);
        
        add_history(inp.c_str());

        vector<string> parts = splitstr(inp, ' ');

        if(builtincommandexists(parts[0])){ // trimstdstr(parts[0])[0] == '.'
            callbuiltincommand(parts[0], parts);
        }
        else if(trimstdstr(parts[0]) != ""){
            if(fs_fileexists("/usr/bin/" + parts[0])){
                startubProc(parts[0], parts);
            }
            else if(fs_fileexists(joinpath(joinpath("/usr/vault/", parts[0]), parts[0]))){
                startvaultProc(parts[0], parts);
            }
            else{
                cnf(parts[0]);
            }
        }
        else{
            if(inp != ""){
                cnf(parts[0]);
            }
        }
    }
}