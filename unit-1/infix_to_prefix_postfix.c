#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

int prec(char c) {
    if (c == '^') return 3;
    else if (c == '/' || c == '*') return 2;
    else if (c == '+' || c == '-') return 1;
    else return 0;
}

char associativity(char c) {
    if (c == '^') return 'R';
    else return 'L';
}

void reverse(char s[]) {
    int len = strlen(s);
    for (int i = 0; i < len / 2; i++) {
        char temp = s[i];
        s[i] = s[len - i - 1];
        s[len - i - 1] = temp;
    }
}

void replace_brackets(char s[]) {
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(') s[i] = ')';
        else if (s[i] == ')') s[i] = '(';
    }
}

void infix_to_postfix(char s[], char result[]) {
    char operator_stack[1000];
    int position = 0, top = -1, len = strlen(s);
    
    for (int i = 0; i < len; i++) {
        char c = s[i];       
        if((c>='a' && c<='z')||(c>='A' && c<='Z')||(c>='0' && c<='9')){
            result[position++] = c;
        } 
        else if (c == '(') {
            operator_stack[++top] = c;
        } 
        else if (c == ')') {
            while (top >= 0 && operator_stack[top] != '(') {
                result[position++] = operator_stack[top--];
            }
            top--;  // Pop '(' from the stack
        } else {
            while (top >= 0 && prec(c) <= prec(operator_stack[top])) {
                if (associativity(c) == 'L' || prec(c) < prec(operator_stack[top])) {
                    result[position++] = operator_stack[top--];
                } else {
                    break;
                }
            }
            operator_stack[++top] = c;
        }
    }
    while (top >= 0) {
        result[position++] = operator_stack[top--];
    }
    result[position] = '\0';
}

void infix_to_prefix(char s[]) {
    char reversed_infix[1000], postfix[1000];
    
    strcpy(reversed_infix, s);
    reverse(reversed_infix);
    replace_brackets(reversed_infix);

    infix_to_postfix(reversed_infix, postfix);

    reverse(postfix);
    printf("Prefix expression: %s\n", postfix);
}

int main() {
    // char exp[] = "a+b*(c^d-e)^(f+g*h)-i";
    char exp[] = "a*b+c";
    // infix_to_prefix(exp);
    // char s[] = "a+b*c";
    char s1[strlen(exp)];
    infix_to_postfix(exp, s1);
    printf("%s\n", s1);
    return 0;
}