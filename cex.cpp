//WINDOWS EXPLORER WITH TERMINAL INTERFACE BY POMOHACI TEODOR
//ONLY AVAILABLE FOR WINDOWS
#include <iostream>
#include <windows.h>
#include <dirent.h>
#include <string>
#include <cstring>
#include <conio.h>

using namespace std;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); //basic console handle
char files[1000][300]; //the name of the files in the selected directory will be stored here
//char CD[300]; //manual input
char ch; //character for different commands, mostly found in the switch loop
int y; //console cursor, as well as what file im selecting
int i=0;
//stuff that work but i dont understand how
DIR * d;
struct dirent * dir;

//colors
int FOLDER_COLOR = 11;
int INPUT_COLOR = 9;

int k; //return value of Show(), to enter folder or open file
char input[300]; //string for input mode
char command[350]; //string to execute a command

//FUNCTION TO OUTPUT IN DIFFERENT COLORS
void Print(int color, string str){
    SetConsoleTextAttribute(h, color);
    cout << str;
    SetConsoleTextAttribute(h, 7);
}

//FUNCTION TO OUTPUT THE CONTENTS OF THE DIRECTORY
int Show(char path[300]){
    //refreshing files[]
    i = 0;
    //the rest of the thing
    if(SetCurrentDirectory(path)) k = 1; //succeed -> open folder
    else k = 0; //fail -> open file
    system("cls");
    d = opendir(".");
    if(d){
        while((dir = readdir(d)) != NULL){
            if(!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..")){
                Print(FOLDER_COLOR, dir->d_name);
                cout << "\n";
            }
            else{
                if(SetCurrentDirectory(dir->d_name)){
                    Print(FOLDER_COLOR, dir->d_name);
                    cout << "\n";
                    SetCurrentDirectory("..");
                }
                else cout << dir->d_name << "\n";
            }
            strcpy(files[i], dir->d_name);
            i++;
        }
        closedir(d);
    }
    return k;
}
int main(int argc, char ** argv){
    if(argv[1] != NULL){
        if(!strcmp(argv[1], "help") && argc > 1){
            cout << "File explorer with terminal interface\n";
            cout << "W - move cursor up\n";
            cout << "S - move cursor down\n";
            cout << "ENTER - access folder/file\n";
            cout << "T - manually type the folder/file you want to access\n";
            cout << "N - create new empty file\n";
            cout << "M - create new folder\n";
            cout << "D - delete a file\n";
            cout << "F - delete a folder\n";
            cout << "\\ - close program\n\n";

            cout << "write the command without arguments to open the current directory\n";
            cout << "to open a specific directory write the path to it as argument";
            return 0;
        }
        else{
            SetCurrentDirectory(argv[1]);
        }
    }
    Show(".");
    SetConsoleCursorPosition(h, {0, 0});
    while(ch != '\\'){
        ch = getch();
        switch(ch){
            case 'w':
            case 'W':{
                if(y != 0) y--;
                SetConsoleCursorPosition(h, {0, y});
                break;
            }
            case 's':
            case 'S':{
                y++;
                SetConsoleCursorPosition(h, {0, y});
                break;
            }
            case '\r':{
                Show(files[y]);
                if(k){
                    y = 0;
                    SetConsoleCursorPosition(h, {0, y});
                }
                else{
                    //since files have spaces inbetween, quotations are mandatory
                    //!code readability is low, pay close attention
                    strcpy(command, "\"");
                    strcat(command, files[y]);
                    strcat(command, "\"");

                    system(command);
                    SetConsoleCursorPosition(h, {0, y});
                }
                break;
            }
            //case t is different due to folders existing
            case 't':
            case 'T':{
                Show(".");
                SetConsoleTextAttribute(h, INPUT_COLOR);
                cin.get(input, 300);
                cin.get();
                SetConsoleTextAttribute(h, 7);
                Show(input);
                if(k){
                    y = 0;
                    SetConsoleCursorPosition(h, {0, y});
                }
                else{
                    strcpy(command, "\"");
                    strcat(command, input);
                    strcat(command, "\"");

                    system(command);
                    SetConsoleCursorPosition(h, {0, y});
                }
                break;
            }
            case 'n':
            case 'N':{
                Show(".");
                SetConsoleTextAttribute(h, INPUT_COLOR);
                cin.get(input, 300);
                cin.get();
                SetConsoleTextAttribute(h, 7);
                strcpy(command, "type nul > \"");
                strcat(command, input);
                strcat(command, "\"");
                system(command);
                Show(".");
                SetConsoleCursorPosition(h, {0, 0});
                break;
            }
            case 'm':
            case 'M':{
                Show(".");
                SetConsoleTextAttribute(h, INPUT_COLOR);
                cin.get(input, 300);
                cin.get();
                SetConsoleTextAttribute(h, 7);
                strcpy(command, "mkdir \"");
                strcat(command, input);
                strcat(command, "\"");
                system(command);
                Show(".");
                SetConsoleCursorPosition(h, {0, 0});
                break;
            }
            case 'd':
            case 'D':{
                Show(".");
                SetConsoleTextAttribute(h, INPUT_COLOR);
                cin.get(input, 300);
                cin.get();
                SetConsoleTextAttribute(h, 7);
                strcpy(command, "del \"");
                strcat(command, input);
                strcat(command, "\"");
                system(command);
                Show(".");
                SetConsoleCursorPosition(h, {0, 0});
                break;
            }
            case 'f':
            case 'F':{
                Show(".");
                SetConsoleTextAttribute(h, INPUT_COLOR);
                cin.get(input, 300);
                cin.get();
                SetConsoleTextAttribute(h, 7);
                strcpy(command, "rmdir \"");
                strcat(command, input);
                strcat(command, "\"");
                system(command);
                Show(".");
                SetConsoleCursorPosition(h, {0, 0});
                break;
            }
        }
    }
    system("cls");
    return 0;
}
/*
Developer Notes:
    - to create a new file: type nul > filename
*/
