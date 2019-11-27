
//
//  Predictive1.c
//  Algo
//
//  Created by Junho's Mac on 2019/11/25.
//  Copyright © 2019 Junho's Mac. All rights reserved.
//
/*
 Predictive parser
 2017.11.03 by Kang, Seung-Shik at Kookmin University
 */
#include <stdio.h>
#include <string.h>

#define NONTERMINALS 3
#define TERMINALS 3
#define RULESIZE 400
#define MAX 100

//#define INPUT_END_MARK '$'
#define STACK_BOTTOM_MARK '_'

char create_rule[RULESIZE][MAX];
int parsing_table[NONTERMINALS][TERMINALS];
char stack[999];
int top;

void input_data(char *str)
{
    printf("CFG rules:");
    printf("\t1. A -> aB");
    printf("\t2. B -> aCb");
    printf("\t3. B -> bC");
    printf("\t4. C -> cC");
    printf("\t5. C -> b");
    string str = aacbb;
    printf("Input(%s 를 Parsing을 해 보겠습니다. : ) = ",str);

    strcat(str, "$");
}

void load_create_rule()
{
    strcpy(create_rule[0], "aB");
    strcpy(create_rule[1], "aCb");
    strcpy(create_rule[2], "bC");
    strcpy(create_rule[3], "cC");
    strcpy(create_rule[4], "b");
    
    puts("CFG rules:");
    puts("\t1. A -> aB");
    puts("\t2. B -> aCb");
    puts("\t3. B -> bC");
    puts("\t4. C -> cC");
    puts("\t5. C -> b");
}

/*
 생성 규칙이 없는 빈칸은 -1 로 표시를 한다.
 Vn/Vt  |    a    b    c
 --------------------------------------
    A   |    1   -1   -1
    B   |    2    3   -1
    C   |   -1    5    4
 */

void load_parsing_table()
{
    parsing_table[0][0] = 0;
    parsing_table[1][0] = 1;
    parsing_table[1][1] = 2;
    parsing_table[2][1] = 4;
    parsing_table[2][2] = 3;
}

char stack_top()
{
    return stack[top-1];
}

void push(char ch)
{
    stack[top++] = ch;
}

void pop()
{
    top--;  // pop 은 top 이라는 것을 하나씩 줄여서 나가는 것이고
    //printf("현재의 top 은 %c",stack_top());
}

void init_stack()
{
    top=0;
    push(STACK_BOTTOM_MARK);
    push('A');
}

int is_nonterminal(char ch)
{
    if ('A' <= ch && ch <= 'Z') return 1;
    else return 0;
}

int is_terminal(char ch)
{
    return (is_nonterminal(ch) == 0);
}

void predictive_parsing(int table[NONTERMINALS][TERMINALS], char rule[RULESIZE][MAX], char *input)
{
    char *p = input;
    char *str_p;
    int index=0;
    int len;
    
    while (1) {
        if (stack_top() == STACK_BOTTOM_MARK) {
            if (*p == '$')
                printf("[accept]\n");    // parsing OK 마지막인 $ 만 남게 된다면 파싱이 완료가 되었다고 문구를 띄우면 되는 거고
            else printf("[error] -- Input is not empty! - line 113\n");
            return;
        }
        
        if (is_terminal(stack_top())) {    // pop -- terminal symbol 터미널인 경우에는 pop을 하고
            if (*p == stack_top()) {
                pop();
                p++;
            } else {
                printf("[error] -- Stack is not empty! - line 121 \n");
                return;
            }
        } else {        // expand -- nonterminal 터미널이 아닌 넌터미널심볼이라면 expand 를 해야지
            index = parsing_table[stack_top()-'A'][*p-'a'];
            if (index != -1) {
                str_p = rule[index];
                len = strlen(str_p);
                printf("[CFG %d] %c -> %s\n", index+1, stack_top(), str_p);
                pop();
                for (int i=len-1; i>=0; i--) {
                    push(str_p[i]);
                }
            } else { // error
                printf("[error] %c -> %c - line 128 \n", stack_top(), *p);
                return;
            }
        }
    }
}

int main()
{
    char input[100];
    
    load_create_rule();
    load_parsing_table();
    
    input_data(input);
    init_stack();
    
    predictive_parsing(parsing_table, create_rule, input);
    return 0;
}
