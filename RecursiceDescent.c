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

void ps()
{
    if (ch == 's'){
        ch = getchar();
    }
    else error();
}

void pe()
{
    if(ch == 'e'){
        ch = getchar();
    }
    else error();
}

void pS()
{
    void pE(void);
    
    if(ch == 'a'){
        pa(); pE();
    }else{
        error();
    }
}

void pE()
{
    switch (ch) {
        case 's':
            ps(); pE();
            break;
            
        case 'e':
            pe();
            break;
    
        default:
            error();
    }
}




int main()
{
    puts("CFG rules:");
    puts("\t1. S -> aE");
    puts("\t2. E -> sE");
    puts("\t3. E -> e");

    printf("Input( 유효성을 테스트 하겠습니다 입력해주세요 :  ) = ");

    ch = getchar();
    pS();
    if (!errflag && ch == '\n') puts("OK");
    else error();
        
    return 0;
}

