#include <stdio.h>

char ch;
int errflag = 0;

/*
    Recognition-failed message.
*/
void error()
{
    if (!errflag) {
        puts("FAIL! Wrong input");
        errflag = 1;
    }
}

void pa()
{
    if(ch == 'a')
        ch = getchar();
    else error();
}

void pb()
{
    if (ch == 'b'){
        ch = getchar();
    }
    else error();
}

void pc()
{
    if(ch == 'c'){
        ch = getchar();
    }
    else error();
}

void pd()
{
    if(ch == 'd'){
        ch = getchar();
    }
    else error();
}
void pS()
{
    void pA(void);
    
    if(ch == 'a'){
        pa(); pA();
    }else{
        error();
    }
}

void pA()
{
    void pB(void);
    switch (ch) {
        case 'a':
            pa(); pB();
            break;
            
        case 'b':
            pb(); pB();
            break;
    
        default:
            error();
    }
}

void pB()
{
    switch (ch) {
        case 'c':
            pc(); pB();
            break;
        case 'd':
            pd(); pB(); pc();
            break;
        case 'b':
            pb();
            break;
            
        default:
            error();
            break;
    }
}



int main()
{
    puts("CFG rules:");
    puts("\t1. S -> aA");
    puts("\t2. A -> aBb");
    puts("\t3. A -> bB");
    puts("\t4. B -> cB");
    puts("\t5. B -> dBc");
    puts("\t6. B -> b");
    printf("Input( 유효성을 테스트 하겠습니다 입력해주세요 :  ) = ");

    ch = getchar();
    pS();
    if (!errflag && ch == '\n') puts("OK");
    else error();
        
    return 0;
}

