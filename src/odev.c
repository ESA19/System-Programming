#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jval.h"
#include "dllist.h"
#include "fields.h"
#include <stdbool.h>

//it checks the file extension is '.dat' or not
int dat_mi(const char *filename)
{
    const char *nokta = strrchr(filename, '.');
    if (!nokta || nokta == filename)
    {
        return 0;
    }
    return strcmp(nokta, ".dat"); //if the two values same returns '0'
}

int main(int argc, char *argv[])
{
    IS is;
    Dllist list, tmp, cursor;
    char *str;
    char *token;
    int num;
    char ch;
    FILE *fp;
    
    //it checks arguman counter equals two
    if (argc != 2)
    {
        fprintf(stderr, "Lutfen bir dosya ismi giriniz!");
        return EXIT_FAILURE;
    }
    else
    {
        if (dat_mi(argv[1]))
        {
            fprintf(stderr, "Gecersiz dosya bicimi! Girdi olarak yalnizca '.dat' uzantili dosya veriniz!\n");
            return EXIT_FAILURE;
        }
        else
        {
            is = new_inputstruct(argv[1]); //new_inputstruct opens the file which inputted from the console.
            if (is == NULL) //if the inputted file didn't opened it gives a error.
            {
                fprintf(stderr, "Girilen dosya bulunamadi!\n");
                return EXIT_FAILURE;
            }
            else
            {
                fp = fopen("cikis.dat", "w"); // it creates a file for writing the program output.

                if (fp == NULL) //if the output file didn't create it gives a error message.
                {
                    fprintf(stderr, "cikis dosyasi olusturulamadi!\n");
                    return EXIT_FAILURE;
                }
                list = new_dllist(); //new_dllist, allocates and returns a new doubly linked list
                dll_append(list, new_jval_c('\0')); // dll_append, adds new node at end of the list. 
                cursor = dll_first(list);

                int exit = 0;
                while (get_line(is) != -1 && !exit)
                {
                    str = is->text1;
                    if (strncmp(str, "yaz: ", 5) == 0) // it compares str1('yaz: ') and str2('str') are equal or not. if they are equal it returns 0.
                    {
                        str += 5; //passing 5 charchter in str.
                        token = strtok(str, " ");// it makes tokenization according to the one blank
                        while (token != NULL)//the loop works until token equals to NULL
                        {
                            if (sscanf(token, "%d", &num) == 1) //sscanf is used for parsing from a specified string. scanf is used  for parsing from keybord input. it extracts an integer from token and store in num variable. it returns 1 if it find a number.
                            {
                                token = strtok(NULL, " "); //it moves another tokenizated world.
                                if (token != NULL && sscanf(token, "%c", &ch) == 1)
                                {
                                    if (ch == '\\') //it checks the characther starting with '\'
                                    {
                                        char nextChar = *(token + 1);//it points next memory location.
                                        if (nextChar == 'b')
                                        {
                                            ch = ' '; // if the next character equals to 'b' character will be ' '
                                        }
                                        else if (nextChar == 'n')
                                        {
                                            ch = '\n';//if the nextcharacter equals to 'n' character will be newline
                                        }
                                    }

                                    for (int i = 0; i < num; i++) //the loop works until reaching number of num.
                                    {
                                        dll_insert_a(cursor, new_jval_c(ch)); //dll_insert_a, adds a new node with new character value. after where the cursor pointed.
                                        cursor=cursor->flink;//now, cursor points new added node.
                                    }
                                }
                            }
                            token = strtok(NULL, " ");
                        }
                    }
                    else if (strncmp(str, "sil: ", 5) == 0)
                    {
                        str += 5;
                        token = strtok(str, " ");
                        while (token != NULL)
                        {
                            if (sscanf(token, "%d", &num) == 1)
                            {
                                token = strtok(NULL, " ");
                                if (token != NULL && sscanf(token, "%c", &ch) == 1)
                                {
                                    tmp = cursor->blink; //tmp points the node behind the cursor.
                                    while (tmp != dll_nil(list) && num > 0) //the loop works until not reaching list's sentinel node.
                                    {
                                        if (tmp->val.c == ch) //it checks the tmp's value equals to ch.
                                        {
                                            cursor = tmp->blink; //cursors points the node behind the tmp
                                            Dllist to_delete = tmp; // creates a Dllist object and assigned tmp adress.
                                            tmp = tmp->blink; //tmp points the node behind the tmp.
                                            dll_delete_node(to_delete);//Deletes the given node from the list.
                                            num--;//number of character are decreasing.
                                        }
                                        else
                                        {
                                            tmp = tmp->blink;
                                            if (tmp == dll_first(list))//if the tmp reached the beginning of the list the movement stops.
                                            {
                                                cursor=dll_first(list);//cursor points the beginning of the list.
                                                break;
                                            }
                                        }
                                    }
                                }
                            }

                            token = strtok(NULL, " ");
                        }
                    }
                    else if (strncmp(str, "dur:", 4) == 0) // the program stops successfully if the reading value equals to 'dur:'.
                    {

                        exit = 1;
                        printf("program basarili bir sekilde durduruldu!\n");
                        
                    }
                    else if(strncmp(str,"sonagit:",8)==0) //the cursor points the end of the list if the reading value equals to 'sonagit:' 
                    {
                        cursor=dll_last(list); //cursor points the end of the list.
                    }
                }

                for (tmp = dll_first(list); tmp != dll_nil(list); tmp = tmp->flink) // tmp moves to end of the list from beginning of the list until not reaching sentinel node.
                {
                    if (tmp->val.c != '\0') //it checks the tmp's value equals to sentinel node.
                    {
                        fprintf(fp, "%c", tmp->val.c); //it writes tmp's value into output file.
                        printf("%c", tmp->val.c); //it also writes into console.
                    }
                }
                
                fclose(fp); //output file closes.
                printf("\n");
                
            }
        }
    }
    free_dllist(list); //it frees list from memory.
    jettison_inputstruct(is);//closes the file associated with the IS and frees the IS
    return 0;
}
