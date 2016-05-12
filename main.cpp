#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>

using namespace std;

char value (string filename, char x, char y)       //returns value of and/or/impl expression
{
    string line;
    fstream file;
    char v;
    file.open(filename.c_str());
    while(getline(file,line)!=NULL)
    {
        if(line[0]==x and line[2]==y)
        {
            v=line[4];
            file.close();
            return v;
        }
    }
    return ' ';
}

char NOTval (string filename, char x)    //returns value of negated argument
{
    string line;
    fstream file;
    char v;
    file.open(filename.c_str());
    while(getline(file,line)!=NULL)
    {
        if(line[0]==x)
        {
            v=line[2];
            file.close();
            return v;
        }
    }
    return ' ';
}

int main(int argc, char *argv[])
{
    if(argc!=9)
    {
        cout << "Niepoprawna liczba argumentow!" << endl;
        return 1;
    }

    string args[argc+1];
    string NOT,OR,AND,IMPL;
    char ans;
    int r1,r2,r3;
    int a1,a2,a3;
    char d1,d2,d3;
    string enquiry;
    string enq[5];
    int enqc;
    char x,y,z;

    for(int i=1; i<argc; i++)
    {
        args[i]=argv[i];
    }

    for(int i=1; i<argc; i+=2)
    {
        if(args[i]=="--not") NOT = args[i+1];
        if(args[i]=="--or") OR = args[i+1];
        if(args[i]=="--and") AND = args[i+1];
        if(args[i]=="--impl") IMPL = args[i+1];
    }

    cout << "Witaj w LogikoLotku!" << endl;
    cout << "Program losuje 3 rozne liczby z zakresu 1-10." << endl;
    cout << "Twoim zadaniem jest ich odgadniecie poprzez zadawanie pytan!" << endl;
    do
    {
        cout << "Aby kontynuowac wpisz k, aby wyjsc wpisz w: ";
        cin >> ans;
        if(ans=='w')
        {
            cout << "Do zobaczenia!" << endl;
            return 0;
        }
    }
    while (ans!='k');

    r1=rand()%10+1;
    do
    {
        r2=rand()%10+1;
    }
    while (r2==r1);
    do
    {
        r3=rand()%10+1;
    }
    while (r3==r2 or r3==r1);

    cout << "Wygenerowalem liczby! Sprobuj je odgadnac!" << endl;

    while(true)     //loop breaks when game is won
    {
        cout << "Wpisz 3 liczby 1-10:" << endl;
        while(true)
        {
            cin >> a1 >> a2 >> a3;
            if(!cin.good())
            {
                cin.clear();
                cin.sync();
            }
            else break;
        }

        if(a1>r1) d1='1';
        else if(a1==r1) d1='X';
        else d1='0';

        if(a2>r2) d2='1';
        else if(a2==r2) d2='X';
        else d2='0';

        if(a3>r3) d3='1';
        else if(a3==r3) d3='X';
        else d3='0';

        if(d1=='X' and d2=='X' and d3=='X')
        {
            cout << "Gratulacje, wygrales!" << endl;
            return 0;
        }

        cout << "Obliczylem nowe wartosci - a,b,c. Przyjmuja odpowiednio:" << endl;
        cout << "1 - gdy wpisana liczba jest wieksza od wylosowanej" << endl;
        cout << "X - gdy rowna wylosowanej" << endl;
        cout << "0 - gdy jest mniejsza" << endl;
        cout << "Jednoczesnie wartosci te oznaczaja (w logice trojwartosciowej):" << endl;
        cout << "1 - prawda, 0 - falsz, X - nieznana wartosc" << endl;
        cout << "Aby odgadnac wartosci a,b,c mozesz zadawac zapytania postaci:" << endl;
        cout << "(not) [a/b/c] [and/or/impl] (not) [a/b/c]" << endl;
        cout << "Gdzie: () - parametr opcjonalny; [] - jeden z podanych" << endl;
        cout << "Aby zakonczyc zadawanie zapytan, wpisz k." << endl;
        cin.ignore();

        while(true)     //breaks when k is typed
        {
            getline(cin,enquiry);       //reads an enquiry (including spaces)
            stringstream enqstring(enquiry);    //converts string to stream
            enqc=0;
            while(getline(enqstring,enq[enqc],' ')) enqc++;     //saves specific words to an array, and counts number of words

            if(enquiry=="k") break;
            else if(enqc==5)
            {
                if(enq[0]=="not" and enq[3]=="not")
                {
                    if ( (enq[1]=="a" or enq[1]=="b" or enq[1]=="c") and (enq[4]=="a" or enq[4]=="b" or enq[4]=="c") )
                    {
                        if(enq[1]=="a") x=d1;
                        else if(enq[1]=="b") x=d2;
                        else x=d3;

                        if(enq[4]=="a") y=d1;
                        else if(enq[4]=="b") y=d2;
                        else y=d3;

                        x=NOTval(NOT,x);
                        y=NOTval(NOT,y);
                        if(enq[2]=="and")
                        {
                            z=value(AND,x,y);
                            cout << "Odpowiedz: " << z << endl;
                        }
                        else if(enq[2]=="or")
                        {
                            z=value(OR,x,y);
                            cout << "Odpowiedz: " << z << endl;
                        }
                        else if(enq[2]=="impl")
                        {
                            z=value(IMPL,x,y);
                            cout << "Odpowiedz: " << z << endl;
                        }
                    }
                }
            }
            else if(enqc==4)
            {
                if(enq[0]=="not")
                {
                    if ( (enq[1]=="a" or enq[1]=="b" or enq[1]=="c") and (enq[3]=="a" or enq[3]=="b" or enq[3]=="c") )
                    {
                        if(enq[1]=="a") x=d1;
                        else if(enq[1]=="b") x=d2;
                        else x=d3;

                        if(enq[3]=="a") y=d1;
                        else if(enq[3]=="b") y=d2;
                        else y=d3;

                        x=NOTval(NOT,x);
                        if(enq[2]=="and")
                        {
                            z=value(AND,x,y);
                            cout << "Odpowiedz: " << z << endl;
                        }
                        else if(enq[2]=="or")
                        {
                            z=value(OR,x,y);
                            cout << "Odpowiedz: " << z << endl;
                        }
                        else if(enq[2]=="impl")
                        {
                            z=value(IMPL,x,y);
                            cout << "Odpowiedz: " << z << endl;
                        }
                    }
                }
                else if(enq[2]=="not")
                {
                    if ( (enq[0]=="a" or enq[0]=="b" or enq[0]=="c") and (enq[3]=="a" or enq[3]=="b" or enq[3]=="c") )
                    {
                        if(enq[0]=="a") x=d1;
                        else if(enq[0]=="b") x=d2;
                        else x=d3;

                        if(enq[3]=="a") y=d1;
                        else if(enq[3]=="b") y=d2;
                        else y=d3;

                        y=NOTval(NOT,y);
                        if(enq[1]=="and")
                        {
                            z=value(AND,x,y);
                            cout << "Odpowiedz: " << z << endl;
                        }
                        else if(enq[1]=="or")
                        {
                            z=value(OR,x,y);
                            cout << "Odpowiedz: " << z << endl;
                        }
                        else if(enq[1]=="impl")
                        {
                            z=value(IMPL,x,y);
                            cout << "Odpowiedz: " << z << endl;
                        }
                    }
                }
            }
            else if(enqc==3)
            {
                if ( (enq[0]=="a" or enq[0]=="b" or enq[0]=="c") and (enq[2]=="a" or enq[2]=="b" or enq[2]=="c") )
                {
                    if(enq[0]=="a") x=d1;
                    else if(enq[0]=="b") x=d2;
                    else x=d3;

                    if(enq[2]=="a") y=d1;
                    else if(enq[2]=="b") y=d2;
                    else y=d3;

                    if(enq[1]=="and")
                    {
                        z=value(AND,x,y);
                        cout << "Odpowiedz: " << z << endl;
                    }
                    else if(enq[1]=="or")
                    {
                        z=value(OR,x,y);
                        cout << "Odpowiedz: " << z << endl;
                    }
                    else if(enq[1]=="impl")
                    {
                        z=value(IMPL,x,y);
                        cout << "Odpowiedz: " << z << endl;
                    }
                }
            }
        }
    }
}
