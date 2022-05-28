#include <string>
#include <vector>
#include <cctype>
#include <array>

#include <iostream>
#include <fstream>

#include "readers.h"

using namespace std;

// extern int vector<string> knownNames;

array<float, 10> train(string a)
{
    array<float, 10> info = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    // string fname = "C:\\Users\\benra\\Documents\\Academics\\Spring 22\\Systems (241)\\finalProject\\smallp.c"
    fstream newfile;
    newfile.open(a, ios::in);

    // TODO make imports abs count
    // TODO make comment/multy comment tester

    // imports
    int icount = 0; // wholefreq
    // file lines
    int linec = 0;
    //'=' vs ' = '
    int eSpace = 0;
    int ecount = 0; // ratiofreq
    // mainsize
    float r = mainsize(a); // wholefreq
    // tab vs spaces
    int tspace = 0;
    int tcount = 0; // ratiofreq
    // empty lines
    int mspace = 0; // wholefreq
    // !NULL
    int verbose = 0; // ratiofreq
    int nVerbose = 0;
    // .'\n'
    int newLine = 0; // ratiofreq
    int dots = 0;
    // increment
    int total = 0;
    int sinc, sdec, cinc, cdec, vinc, vdec; // simple, complex, verbose
    sinc = sdec = cinc = cdec = vinc = vdec = 0;
    bool val = false;

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

            ///
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
            if (b[0] != 0)
            {
                nVerbose += b[0];
            }
            if (b[1] != 0)
            {
                verbose += b[1];
            }

            ////
            try
            {

                a = varNames(line);
                if (a != 0)
                {
                    names[a] = names[a] + 1;
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
                std::cout << line << "   " << linec << " c\n";
            }

            ////
            a = dotSpace(line);
            if (a == 1)
            {
                newLine++;
            }
            if (a > 1)
            {
                dots += (a - 1);
                // std::cout << "seq:" << line << "   " << linec << " " << (a - 1) << " c\n";
            }

            //
            b = increment(line);
            for (auto i : b)
            {
                if (i > 0)
                {
                    val = true;
                    break;
                }
            }
            if (val)
            {
                sinc += b[0];
                sdec += b[1];
                cinc += b[2];
                cdec += b[3];
                vinc += b[4];
                vdec += b[5];

                total = total + b[0] + b[1] + b[2] + b[3] + b[4] + b[5];
            }

            val = false;
        }
    }
    /*
    std::cout << "imports: " << icount << '\n';
    std::cout << "Main Ratio: " << r << '\n';

    std::cout << "espace: " << (float)eSpace / ecount << '\n';
    std::cout << "tspace: " << (float)tspace / tcount << '\n';
    std::cout << "nspace: " << (float)mspace / linec << '\n';
    std::cout << "Verbose: " << (float)verbose / nVerbose << '\n';
    std::cout << "dotSpace: " << (float)dots / newLine << '\n';

    std::cout << '\n';

    std::cout << "++: " << (float)sinc / total << '\n';
    std::cout << "--: " << (float)sdec / total << '\n';
    std::cout << "+=: " << (float)cinc / total << '\n';
    std::cout << "-=: " << (float)cdec / total << '\n';
    std::cout << "a=a+1: " << (float)vinc / total << '\n';
    std::cout << "a=a-1: " << (float)vdec / total << '\n';




    for (auto i : names)
    {
        std::cout << i << ", ";
    }

    std::cout << '\n';
    for (auto i : knownNames)
    {
        std::cout << i << ", ";
    }
    */
    info[0] = (float)icount;
    info[1] = (float)(eSpace / ecount);
    info[2] = (float)(tspace / tcount);
    info[3] = (float)(mspace / linec);
    info[4] = (float)(verbose / nVerbose);
    info[5] = (float)(dots / newLine);
    info[6] = (float)((sinc + sdec) / total);
    info[7] = (float)((cinc + cdec) / total);
    info[8] = (float)((vinc + vdec) / total);
    info[9] = r;

    return info;

    // call each method
    // add those to runing total
    // repeat
    // save to file/profile
}
