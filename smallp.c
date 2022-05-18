//ben rapkin and gawain liu
//test add
#include<stdio.h>
#include<string.h> 
#include <ctype.h> 


	//if the current letter is a not a u with a q before it, then cont. 
			//otherwise, pretend no vowels found

int leadingVowel(char *word, int count){
    //check for capitalization
    //aeiou. 
    //!qu, it's a con
    //!y for leading, but y for shift
    if (word[0]==65||word[0]==69||word[0]==73||word[0]==79||word[0]==85 ||word[0]== 97||word[0]==101||word[0]==105||word[0]==111||word[0]==117){           
    //add yay                
        word[count]=121;
        word[count+1]=97;
        word[count+2]=121;
        word[count+3]='\0';
        return 1;
    }
    return 0;
}