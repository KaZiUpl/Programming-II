#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>

using namespace std;

#define SYNC_STDIO true

//#define WORDS_FSCANF_FPRINTF
//#define WORDS_IOSTREAM

//#define CHARS_GETC_PUTC
//#define CHARS_IOSTREAM

//#define ROWS_FGETS_FPUTS
//#define ROWS_IOSTREAM

//#define BLOCKS_FREAD_FWRITE
//#define BLOCKS_IOSTREAM

// copying single words
void copy_words_using_scanf_and_printf()
{
    ios::sync_with_stdio(SYNC_STDIO);

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
    ios::sync_with_stdio(SYNC_STDIO);

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
    ios::sync_with_stdio(SYNC_STDIO);

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
    ios::sync_with_stdio(SYNC_STDIO);

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
    ios::sync_with_stdio(SYNC_STDIO);

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
    ios::sync_with_stdio(SYNC_STDIO);

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
    ios::sync_with_stdio(SYNC_STDIO);

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
    ios::sync_with_stdio(SYNC_STDIO);

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

    #ifdef WORDS_FSCANF_FPRINTF
    copy_words_using_scanf_and_printf();
    cout<<"Copying using fscanf() and fprintf() has been completed."<<endl;
    #endif // WORDS_FSCANF_FPRINTF

    #ifdef WORDS_IOSTREAM
    copy_words_using_iostream();
    cout<<"Copying using <</>> has been completed."<<endl;
    #endif // WORDS_IOSTREAM

    #ifdef CHARS_GETC_PUTC
    copy_chars_using_getc_and_putc();
    cout<<"Copying using getc() and putc() has been completed."<<endl;
    #endif // CHARS_GETC_PUTC
    #ifdef CHARS_IOSTREAM
    copy_chars_using_iostream();
    cout<<"Copying using cin.get() and cout.put() has been completed."<<endl;
    #endif // CHARS_IOSTREAM

    #ifdef ROWS_FGETS_FPUTS
    copy_rows_using_fgets_fputs();
    cout<<"Copying using fgets() and fputs() has been completed."<<endl;
    #endif // ROWS_FGETS_FPUTS
    #ifdef ROWS_IOSTREAM
    copy_rows_using_iostream();
    cout<<"Copying using getline() and << has been completed."<<endl;
    #endif // ROWS_IOSTREAM

    #ifdef BLOCKS_FREAD_FWRITE
    copy_data_blocks_using_fread_and_fwrite();
    cout<<"Copying using fread() and fwrite() has been completed."<<endl;
    #endif // BLOCKS_FREAD_FWRITE
    #ifdef BLOCKS_IOSTREAM
    copy_data_blocks_using_iostream();
    cout<<"Copying using getline() and << has been completed."<<endl;
    #endif // BLOCKS_IOSTREAM

    return 0;
}
