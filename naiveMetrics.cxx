#include <string>
#include <vector>
#include <cctype>
using namespace std;



//TODO

//Varible Names
//in fucture would like to consider scope, ie globle
vector<float> varNames(string line){ //right now plan to store in profile
    //strip start
    size_t offset=0;
    //vscode changes tab to space
    char tab=char(9);

    if (line.find(tab)!=string::npos){
        offset=line.find(tab);
    }

    //assuming tab won't be other than offseting
    else if (line.find(" ")!=string::npos){
        offset=line.find(" ");
    }

    //make data of var names so we only store each once
    vector<float> names(7,0); //7 indexs all to 0
    size_t Eindex = line.find("=");
    if (Eindex!=string::npos && line.find("==")==string::npos && line.find("===")==string::npos){
        if (offset>=Eindex){
            size_t offset=0;
        }

        string var = line.substr(offset, Eindex);

            if (var.find("_")!=string::npos){
                //snake_Case,
                size_t Uindex=var.find("_");                
                if (isupper(var.at(Uindex+1))){
                    //upper or snake
                    if (isupper(var.at(Uindex-1))){
                        //upper
                        names[0]=names[0]+1;
                    }
                    else {
                        //snake
                        names[1]=names[1]+1;
                    }
                }
                else {
                    //lower, assuming no odD_case
                    names[2]=names[2]+1;
                }
            }
            else if (var.find("-")!=string::npos){
                //- means kabab-case (- overides capitilization)
                names[3]=names[3]+1;
            }
            else {
                int capCount=0;
                for (int i=0; i<var.length(); i++) {
                    if (isupper(var.at(i))){
                        capCount++;
                    }
                }
                if (capCount==1){
                    //camel case
                    names[4]=names[4]+1;
                }
                if (capCount==2){
                    //capital case
                    names[5]=names[5]+1;
                }
                else {
                    //flat or single word, undescriptive
                    names[6]=names[6]+1;
                }
            }
        //call profile to store prevelance
        float sum=0;
        for (int i=0; i<7; i++){
            sum+=names[i];
        }
        for (int i=0; i<7; i++){
            names[i]=names[1]/sum;
        }
    }
    return names;
} 

//Tab vs Spaces
int tabSpace(string line){
    //assume it will be first char
    //0 for error/niether, 1 for tab, 2 for space
    char tab=char(9);
    if (line.at(0)==tab){
        return 1;
    }
    if (line.at(0)==' '){
        return 2;
    }
    else{
        return 0;
    }
}

// ' = ' vs '=' 
int equalSpacing(string line){
    //return 1 for " = " and 2 for "="
    size_t Eindex = line.find("=");
    if (Eindex!=string::npos && line.find("==")==string::npos 
    && line.find("===")==string::npos){
        if (line.at(Eindex-1)==' ' && line.at(Eindex+1)==' '){
            return 1;
        }
        else{
            return 2;
        }
    }
}
    
//Empty Lines
int emptyLine(string line){
    // allow ' ' '\n' tab 
    for (int i=33; i<127; i++){
        if (line.find(char(i))!=string::npos){
            return 0;
        }
    }
    return 1;
}

//!=NULL
int nullForm(string line){
    int count=0;
    size_t offset=line.find("!=null");
    if (offset==string::npos){
        return 0;
    }
    while (offset){
        line=line.substr(offset,line.length()-1);
        count++;
        offset=line.find("!=null");
    }
    return count;
}

//not done // ++ vs +=1 vs a=a+1
vector<int> increment (string line){
    //++ -- += -= these corraspond to vector indexes
    vector<int> a={0,0,0,0}; 
    // a line can have multiple inc and dec
    string temp=line;
    while (temp.find("++")){
        a[0]=a[0]+1;
        temp=temp.substr(temp.find("++"),temp.length());        
    }
    temp=line;
    while (temp.find("--")){
        a[1]=a[1]+1;
        temp=temp.substr(temp.find("--"),temp.length());        
    }
    temp=line;
    while (temp.find("+=")){
        a[2]=a[2]+1;
        temp=temp.substr(temp.find("+="),temp.length());        
    }
    temp=line;
    while (temp.find("-+")){
        a[3]=a[3]+1;
        temp=temp.substr(temp.find("-="),temp.length());        
    }
}

// \n after . 
int dotSpace(string line){
    char tab= char (9);
    size_t dotIndex=line.find(".");
    if (dotIndex!=string::npos){
        if (line.at(dotIndex-1)==' ' ||line.at(dotIndex-1)==tab){
            return 1;
        }
    }
    return 0;
}
