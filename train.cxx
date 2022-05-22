#include <string>
#include <vector>
#include <cctype>

#include <iostream>
#include <fstream>

#include "readers.h"

using namespace std;

int main()
{
    string fname = "C:\\Users\\benra\\Documents\\Academics\\Spring 22\\Systems (241)\\finalProject\\smallp.c";
    fstream newfile;
    newfile.open(fname, ios::in);

    // imports
    int icount = 0; // wholefreq
    // file lines
    int linec = 0;
    //'=' vs ' = '
    int eSpace = 0;
    int ecount = 0; // ratiofreq
    // mainsize
    float r = mainsize(fname); // wholefreq
    // tab vs spaces
    int tspace = 0;
    int tcount = 0; // ratiofreq
    // empty lines
    int mspace = 0; // wholefreq
    //! NULL
    int verbose = 0; // ratiofreq
    int nVerbose = 0;

    vector<int> names(11, 0); // 10 indexes initialized to 0
    std::cout << '\n';
    if (newfile.is_open())
    { // checking whether the file is open
        string line;

        while (getline(newfile, line))
        {
            linec++;
            // std::cout << line << "   "  << linec << " c\n";

            /////
            icount += imports(line);

            ////
            int a = equalSpacing(line);
            if (a)
            {
                eSpace += a;
                ecount++;
            }

            ////
            a = tabSpace(line);
            if (a)
            {
                tspace += a;
                tcount++;
                // std::cout << "val: "<< tspace<< " tcount: "<< tcount <<'\n';
            }

            ////
            a = emptyLine(line);
            if (a)
            {
                mspace++;
            }

            //// 
            vector<int> b = verboseif(line);
            if (b[0]!=0)
            {
                nVerbose+=b[0];
            }
             if (b[1]!=0)
            {
                verbose+=b[1];
            }            

            ////
            a = varNames(line);
            if (a != 0)
            {
                names[a] = names[a] + 1;
            }
        }
    }
    std::cout << "imports: " << icount << '\n';
    std::cout << "Main Ratio: " << r << '\n';

    std::cout << "espace: " << (float)eSpace / ecount << '\n';
    std::cout << "tspace: " << (float)tspace / tcount << '\n';
    std::cout << "nspace: " << (float)mspace / linec << '\n';
    std::cout << "Verbose: " <<(float) verbose / nVerbose << '\n';

    for (auto i : names)
    {
        std::cout << i << ", ";
    }

    std::cout << '\n';
    for (auto i : knownNames)
    {
        std::cout << i << ", ";
    }

    // call each method
    // add those to runing total
    // repeat
    // save to file/profile
}
