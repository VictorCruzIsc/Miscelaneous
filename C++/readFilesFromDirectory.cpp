#include <string>
#include<stdio.h>
#include<cstdlib>
#include<iostream>
#include<string.h>
#include<fstream>
#include<dirent.h>
#include <iterator>
#include<regex>

using namespace std;

void listFile(const char *path, string regexPattern){
        DIR *pDIR;
        struct dirent *entry;
        regex validFile(regexPattern);
        if(pDIR = opendir(path)){
                while(entry = readdir(pDIR)){
                        string file(entry->d_name);
                        if(regex_match(file, validFile))
                                cout <<  file << endl;
                }
                closedir(pDIR);
        }
}

int main(){
        cout << "Listing current directory" << endl;
        string path = ".";
        string regexPattern = "(flows)(.*)(.csv)";
        listFile(path.c_str(), regexPattern);
}
