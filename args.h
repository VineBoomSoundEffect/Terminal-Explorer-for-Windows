if(argc >= 2){
	if(!strcmp(argv[1], "-help")){
		cout << "File explorer with terminal interface\n";
		cout << "W - move cursor up\n";
		cout << "S - move cursor down\n";
		cout << "ENTER - access folder/file\n";
		cout << "T - manually type the folder/file you want to access\n";
		cout << "N - create new empty file\n";
		cout << "M - create new folder\n";
		cout << "D - delete a file/folder\n";
		cout << "\\ - close program\n\n";

		cout << "write the command without arguments to open the current directory\n";
		cout << "to open a specific directory write the path to it as argument\n";
		return 0;
	}
	else if(!strcmp(argv[1], "-newt")){
		if(argc >= 3){
			strcpy(command, "type nul > \"");
			strcat(command, path);
			strcat(command, argv[2]);
			strcat(command, ".tex\"");
			system(command);
		}
		else{
			cout << "The path where the templates are stored is:\n";
			cout << path << "\n";
		}
		return 0;
	}
	else if(!strcmp(argv[1], "-uset")){
		if(argc >= 3){
			Compiler(argv[2]);
		}
		else{
			cout << "The syntax is incorrect. A template name is required. Please try again";
		}
		return 0;
	}
	else{
		SetCurrentDirectory(argv[1]);
	}
}