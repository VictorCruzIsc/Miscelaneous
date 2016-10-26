#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXLENGTH 1000

void invertCompleteString(char *str){
	char *local = str;
	char *aux;
	while(*local){
		local++;
	}
	local--;
	while(str < local){
		//*aux = *str;
		*str = *local ^ *str;
		*local = *local ^ *str;
		*str = *local ^ *str;
		str++;
		local--;
	}
}


//Oracle
//Given an string invert the words
//ej. Hello world this is an example  -> example an is this world Hello
void invertString(char *str){ //b2 b3
	invertCompleteString(str);
	char *guard = str;
	char *start = str;
	char *moving = str;
	char *aux;
	while(*guard){ 
		while(*moving !=' ' && *moving){ //b1
			moving++;
			guard++;
		}
		moving--;
		while(start<moving){
			*aux = *moving;
			*moving-- = *start;
			*start++ = *aux;
		}
		guard++;
		start = guard;
		moving = guard;
	}
}

void deleteChars(char *a, char *b){
	int s1l = strlen(a);
	int s2l = strlen(b);
	int i,j;
	int compare[255];
	for(i=0; i<s2l; i++){
		compare[b[i]] = 1;
	}
	for(i=j=0; i<s1l; i++){
		if(compare[a[i]] != 1){
			a[j++] = a[i];
		}
	}
	a[j]='\0';
}

int any(char *a, char *b){
	int al = strlen(a);
	int bl = strlen(b);
	int i;
	int compare[255];
	for(i=0; i<bl; i++){
		compare[b[i]] = 1;
	}
	for(i=0; i<al; i++){
		if(compare[a[i]] == 1){
			return i;
		}
	}
	return -1;
}

//Oracle
//Given an string, check if the ([{ are correctly balanced
int checkBalancedString(char *str){
	char *current = str;
	int elements = 0;
	char stack[MAXLENGTH];

	while(*str){
		switch(*str){
			case '{': case '[': case '(':
				stack[elements++] = *str;
			break;
			case '}':
				if(!elements || stack[elements - 1] != '{'){
					return 0;
				}
                elements--;
			break;
			case ']':
				if(!elements || stack[elements - 1] != '['){
					return 0;
				}
                elements--;
			break;
			case ')':
				if(!elements || stack[elements - 1] != '('){
					return 0;
				}
                elements--;
			break;
		}
        str++;
	}
	return !elements;
}

int main(){
	//char str[] = "Hello World Again My Man";
	//char str[] = "Hello";
	char str[] = "Hello World";
	//char str[] = "Hello World Again";
	//char str[] = "Hello World Again My";
	//char str[] = "Hello World Again My Man";
	printf("%s\n", str);
	invertString(str);
	printf("%s\n", str);

	char x[] = "Mi mejor amigo";
	char d[] = "oral";
	int index = any(x, d);
	printf("Index: %d \n", index);

	char a[] = "calabaza";
	char b[] = "wd";
	deleteChars(str, b);
	printf("Delete chars resulta %s\n", str);

	char balancedA[] = "{{{[[]]()}}}"; //1
	char balancedB[] = ""; //1
	char balancedC[] = "()(){{}}["; //0
	char *balancedD = "(((({{[]}[))))"; //0
	char *balancedE = "{(){}[][[]]{}((()))}"; //1
	char *balancedF = "]{}"; //0

	printf("%s\n", balancedA);
	int result = checkBalancedString(balancedA);
	printf("Result: %d\n",result);
	result = checkBalancedString(balancedB);
	printf("Result: %d\n",result);
	result = checkBalancedString(balancedC);
	printf("Result: %d\n",result);
	result = checkBalancedString(balancedD);
	printf("Result: %d\n",result);
	result = checkBalancedString(balancedE);
	printf("Result: %d\n",result);
	result = checkBalancedString(balancedF);
	printf("Result: %d\n",result);
}
