#include <bits/stdc++.h>
using namespace std;

#include "include/fsu.hpp"
#include "include/stu.hpp"

int currentsession = 0;

int createsession(){
    int ses = 0;
    for(int i = 0; i <= 100; i++){
        if(fs_fileexists("/etc/session/" + to_string(i))){
            ses = max(ses, i + 1);
        }
    }

    currentsession = ses;
    writefs("/etc/session/" + to_string(ses), "/home");

    return ses;
}

int getcurrentsession(){
    return currentsession;
}

string getcurrentpath(){
    return trimstdstr(readfs("/etc/session/" + to_string(currentsession))[0]);
}

void updatepath(string path){
    writefs("/etc/session/" + to_string(currentsession), path);
}