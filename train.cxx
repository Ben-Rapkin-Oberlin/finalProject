#include <string>
#include <vector>
#include <cctype>

#include <iostream>
#include <fstream> 

#include "readers.h"

using namespace std;

int main(){
    string fname="C:\\Users\\benra\\Documents\\Academics\\Spring 22\\Systems (241)\\Final\\pig.c";
    fstream newfile;
    newfile.open(fname,ios::in);

    int icount=0;
    float r=mainsize(fname);

    if (newfile.is_open()){   //checking whether the file is open
        string line;
        while(getline(newfile, line)){ 
            icount+=imports(line);
        }
    }
    printf("imports: %i\n", icount);
    printf("ratio: %f\n", r);

    //call each method
    //add those to runing total
    //repeat
    //save to file/profile

    



}
