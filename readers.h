#include <string>
#include <vector>
#include <cctype>
using namespace std;

extern vector<string> knownNames;

int varNames(string line);

int tabSpace(string line);

int equalSpacing(string line);

int emptyLine(string line);

vector<int> verboseif(string line);

vector<int> increment (string line);

int dotSpace(string line);

int imports(string line);

float mainsize(string fname);
