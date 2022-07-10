//WINDOWS EXPLORER WITH TERMINAL INTERFACE BY TEODOR POMOHACI
//ONLY AVAILABLE FOR WINDOWS
#include <iostream>
#include <windows.h>
#include <dirent.h>
#include <cstring>
#include <conio.h>
#include <fstream>

#define Y y-1

using namespace std;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); //basic console handle
char files[1000][300]; //the name of the files in the selected directory will be stored here
char ch; //character for different commands, mostly found in the switch loop
int y; //console cursor, as well as what file im selecting
int i=0;
char validation; //to secure accidental deletion of a file

//stuff that work but i dont understand how
DIR * d;
struct dirent * dir;

//colors
int FOLDER_COLOR = 11;
int INPUT_COLOR = 9;

int k; //return value of Show(), to enter folder or open file
char input[300]; //string for input mode
char command[350]; //string to execute a command
char deletefile[350]; //string to warn user about deleting a file
char path[MAX_PATH+1]; //stores the path to the executable location (without the executable name)
int pathlen; //the length of the source path

//FUNCTION TO OUTPUT IN DIFFERENT COLORS
void Print(int color, string str){
    SetConsoleTextAttribute(h, color);
    cout << str;
    SetConsoleTextAttribute(h, 7);
}

//FUNCTION TO DELETE THE LAST CHARACTERS OF A STRING (unused)
// char * last(char str[100], int l){
	// for(int i=0;i<l;i++){
		// str[strlen(str)-1] = '\0';
	// }
	// return str;
// }

//FUNCTION TO OUTPUT THE CONTENTS OF THE DIRECTORY
int Show(char path[300]){
    //refreshing files[]
    i = 0;
    //the rest of the thing
    if(SetCurrentDirectory(path)) k = 1; //succeed -> open folder
    else k = 0; //fail -> open file
    system("cls");
	system("cd");
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

//FUNCTION TO EXECUTE CODE FROM .TEX FILES
void Compiler(char temp[255]){
	char instruction[255];
	char name[255];
	char path_to_template[500];
	strcpy(path_to_template, path);
	strcat(path_to_template, temp);
	strcat(path_to_template, ".tex");
	ifstream fin(path_to_template);
	while(fin >> instruction){
		if(!strcmp(instruction, "dir")){
			fin >> name;
			strcpy(command, "mkdir ");
			strcat(command, name);
			system(command);
		}
		else if(!strcmp(instruction, "{")){
			SetCurrentDirectory(name);
		}
		else if(!strcmp(instruction, "}")){
			SetCurrentDirectory("..");
		}
		else if(!strcmp(instruction, "file")){
			fin >> name;
			strcpy(command, "type nul > \"");
			strcat(command, name);
			strcat(command, "\"");
			system(command);
		}
	}
}

int main(int argc, char ** argv){
	//get the path of the executable location
	GetModuleFileName(NULL, path, MAX_PATH);
	pathlen = strlen(path);
	while(path[pathlen] != '\\'){
		path[pathlen] = '\0';
		pathlen--;
	}
	#include "args.h"
    Show(".");
	y = 0;
    SetConsoleCursorPosition(h, {0, y});
	#include "input.h"
    system("cls");
    return 0;
}
