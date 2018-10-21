#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

#define SYNC_STDIO true

//#define WORDS

//#define CHARS

//#define ROWS

//#define BLOCKS

// copying single words
void copy_words_using_scanf_and_printf()
{
    FILE *input = fopen("text.txt","r");
    FILE *output = fopen("output.txt","w");
    char word[100];

    while(!feof(input))
    {
        fscanf(input,"%s",word);
        fprintf(output,"%s",word);
    }

    fclose(input);
    fclose(output);
}
void copy_words_using_iostream()
{
    ifstream input("text.txt");
    ofstream output("output2.txt");
    string word;

    while(!input.eof())
    {
        input>>word;
        output<<word;
    }

    input.close();
    output.close();
}
// copying single characters
void copy_chars_using_getc_and_putc()
{
    FILE *input = fopen("text.txt","r");
    FILE *output = fopen("output.txt","w");
    char character;

    while(!feof(input))
    {
        character = getc(input);
        putc(character,output);
    }

    fclose(input);
    fclose(output);
}
void copy_chars_using_iostream()
{
    ifstream input("text.txt");
    ofstream output("output2.txt");
    char character;

    while(!input.eof())
    {
        input.get(character);
        output.put(character);
    }

    input.close();
    output.close();
}
// copying single rows
void copy_rows_using_fgets_fputs()
{
    FILE *input = fopen("text.txt","r");
    FILE *output = fopen("output.txt","w");
    char row[300];

    while(!feof(input))
    {
        fgets(row,300,input);
        fputs(row,output);
    }

    fclose(input);
    fclose(output);
}
void copy_rows_using_iostream()
{
    ifstream input("text.txt");
    ofstream output("output2.txt");
    string row;

    while(!input.eof())
    {
        getline(input,row,'\r');
        output<<row<<endl;
    }

    input.close();
    output.close();
}
// copying data blocks
void copy_data_blocks_using_fread_and_fwrite()
{
    FILE *input = fopen("text.txt","r");
    FILE *output = fopen("output.txt","w");
    char data_block[50];

    while(!feof(input))
    {
        fread(data_block,1,50,input);
        fwrite(data_block,1,50,output);
    }

    fclose(input);
    fclose(output);
}
void copy_data_blocks_using_iostream()
{
    ifstream input("text.txt");
    ofstream output("output2.txt");
    char data_block[50];

    while(!input.eof())
    {
        input.read(data_block,50);
        output.write(data_block,50);
    }

    input.close();
    output.close();
}

int main()
{

    time_t start,end;

    for(int i=0;i<5;i++)
    {
        #ifdef WORDS
        ios::sync_with_stdio(SYNC_STDIO);
        start = clock();
        copy_words_using_scanf_and_printf();
        end = clock();
        cout<<"Copying using fscanf() and fprintf() has been completed in "<<(end-start)/(double)CLOCKS_PER_SEC<<"s"<<endl;

        start = clock();
        copy_words_using_iostream();
        end = clock();
        cout<<"Copying using <</>> has been completed in "<<(end-start)/(double)CLOCKS_PER_SEC<<"s"<<endl;
        #endif // WORDS

        #ifdef CHARS
        ios::sync_with_stdio(SYNC_STDIO);
        start = clock();
        copy_chars_using_getc_and_putc();
        end = clock();
        cout<<"Copying using getc() and putc() has been completed in "<<(end-start)/(double)CLOCKS_PER_SEC<<"s"<<endl;

        start = clock();
        copy_chars_using_iostream();
        end = clock();
        cout<<"Copying using cin.get() and cout.put() has been completed in "<<(end-start)/(double)CLOCKS_PER_SEC<<"s"<<endl;
        #endif // CHARS

        #ifdef ROWS
        ios::sync_with_stdio(SYNC_STDIO);
        start = clock();
        copy_rows_using_fgets_fputs();
        end = clock();
        cout<<"Copying using fgets() and fputs() has been completed in "<<(end-start)/(double)CLOCKS_PER_SEC<<"s"<<endl;

        start = clock();
        copy_rows_using_iostream();
        end = clock();
        cout<<"Copying using getline() and << has been completed in "<<(end-start)/(double)CLOCKS_PER_SEC<<"s"<<endl;
        #endif // ROWS

        #ifdef BLOCKS
        ios::sync_with_stdio(SYNC_STDIO);
        start = clock();
        copy_data_blocks_using_fread_and_fwrite();
        end = clock();
        cout<<"Copying using fread() and fwrite() has been completed in "<<(end-start)/(double)CLOCKS_PER_SEC<<"s"<<endl;

        start = clock();
        copy_data_blocks_using_iostream();
        end = clock();
        cout<<"Copying using getline() and << has been completed in "<<(end-start)/(double)CLOCKS_PER_SEC<<"s"<<endl;
        #endif // BLOCKS
    }

    return 0;
}
