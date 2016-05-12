#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    if(argc!=7) printf("Niepoprawna liczba argumentow! Ma byc 6.");
    else
    {
        char a=*argv[1];
        char b=*argv[2];
        char c=*argv[3];
        char d=*argv[4];
        char e=*argv[5];
        char f=*argv[6];
        if( (a<='0' || b==c || c<=d) && (d>='0' || e<=f) ) printf("1");
        else printf("0");
    }
    return 0;
}
