//Made by Hikari
//Contains print_bits(int ch int y), which takes in a char and int outputs it, with leading zeros.
//Outputs it in binary if y is one, octal if it is two, and hex if it is three.
//Contains decode_bits(ch int), which takes input, skipping whitespace, putting digits into a buffer, and throws an error on other inputs.
//When the buffer reaches CHAR_BIT characters it decodes it.
//y controls the output in the same way as print_bits.
#include <stdio.h>
#include <limits.h>
int static buffer = 0;
int static count = 0;
void print_bits(int ch, int y){
	int i, rem, p_out; 
	if(y == 1){
		for(i = 32 - CHAR_BIT - 1; i > CHAR_BIT -1 ; --i){
			p_out = x;
			p_out << i;
			p_out >> 32 - CHAR_BIT - 1;
			printf("%d", p_out);
		}
	}
	if(y == 2){
		for(i = 32 - CHAR_BIT - 3; i > CHAR_BIT  -1; i - 3){
			p_out = x;
			p_out << i;
			p_out >> 32 - CHAR_BIT - 3;
			printf("%o", p_out);
		}
		//takes care of the extra octal digit if CHAR_BIT isn't divisible by three.
		rem = CHAR_BIT % 3;
		if(rem != 0){
			p_out = x;
			p_out >> 32 - CHAR_BIT - 3; 
			printf("%o", p_out);
		}
	}
	if(y == 3){
		for(i = CHAR_BIT - 4; i > CHAR_BIT  - 1; i - 4){
			p_out = x;
			p_out << i;
			p_out >> CHAR_BIT - 4;
			printf("%X", p_out);
		}
		//takes care of the extra hex digit if CHAR_BIT isn't divisible by four for some reason
		rem = CHAR_BIT % 4;
		if(rem != 0){
			p_out = x;
			p_out >> CHAR_BIT - 4; 
			printf("%X", p_out);
		}
	}
}

void decode_bits(int ch, int y){
	if(y == 1){	
		if((char) ch  == '0'){
			buffer << 1;
			++ count;
		}
		else if ((char ch) == '1'){
			buffer << 1;
			++ buffer;
			++ count;
		}
		else{
			printf("%s\n", "Error decoding, unexpected input.");
			exit(0);
		}
		if(count == CHAR_BIT){
			putchar((char) buffer);
			count = 0;
			buffer = 0; 
		}
	}
}
