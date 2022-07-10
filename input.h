while(ch != '\\'){
    ch = getch();
    switch(ch){
		case 'w':
		case 'W':{
			if(y >= 1) y--;
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
			Show(files[Y]);
			if(k){
				y = 0;
				SetConsoleCursorPosition(h, {0, y});
				SetConsoleCursorPosition(h, {0, y});
			}
			else{
				strcpy(command, "start \"\" \"");
				strcat(command, files[Y]);
				strcat(command, "\"");
				system(command);
				SetConsoleCursorPosition(h, {0, y});
			}
			break;
		}
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
			y = 0;
			SetConsoleCursorPosition(h, {0, y});
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
			y = 0;
			SetConsoleCursorPosition(h, {0, y});
			break;
		}
		case 'd':
		case 'D':{
			Show(files[Y]);
			if(k){
				Show("..");
				strcpy(command, "rmdir /s \"");
				strcat(command, files[Y]);
				strcat(command, "\"");
				SetConsoleTextAttribute(h, 6);
				system(command);
				SetConsoleTextAttribute(h, 7);
			}
			else{
				strcpy(deletefile, files[Y]);
				strcat(deletefile, ", Are you sure you want to delete this file? (Y/N)?");
				Print(6, deletefile);
				cin.get(validation);
				cin.get();
				if(validation=='y' || validation=='Y'){
					strcpy(command, "del \"");
					strcat(command, files[Y]);
					strcat(command, "\"");
					system(command);
				}
			}
			Show(".");
			y = 0;
			SetConsoleCursorPosition(h, {0, y});
			break;
        }
	}
}