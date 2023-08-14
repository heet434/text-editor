#include<iostream>
#include<ncurses.h>
#include<string>
#include<vector>
#include<fstream>
#include<string.h>

using namespace std;

vector<string> load_text(string filename);

void print_text_at_loc(WINDOW * win, vector<string> text, int xloc, int yloc);

vector<string> type_text(vector<string> text, int cursorx, int cursory, WINDOW * win);

vector<string> start_text(string filename, WINDOW * win);

vector<string> input_text(vector<string> text, int cursorx, int cursory, WINDOW * win);

int * cursorcontrol(int arrow);

int main(int argc, char ** argv){
	initscr();
	int win_x_in, win_y_in, win_x_end, win_y_end;
	getyx(stdscr, win_y_in, win_x_in );
	getmaxyx(stdscr,win_y_end,win_x_end);
	noecho();
	refresh();
	int cursorx = 0, cursory = 0;
	WINDOW * win = newwin(5, win_x_end-4,2,2 );
	wrefresh(win);
	box(win,0,0);
	keypad(win, true);
	mvwprintw(win, 1,1,"welcome, if you want to load a new file type its file name, if you want to start new file type newfile123");
	refresh();
	wrefresh(win);
	string filename="";
	char c='\0';
	while(c!='\n'){
		c = getch();
		filename+=getch();
	}
	for(int i=0; i<filename.length(); i++){
		mvwprintw(win, 1,1,"%c",filename[i]);
	}
	wrefresh(win);
	vector<string> text = start_text(filename,win);
	char mode; 
	mode  = getch();
	switch(mode){
		case 'i':
			
			break;
			;
	}

}

vector<string> load_text(string filename){
	
	ifstream fin(filename);
	vector<string> loaded_text;
	if(fin.is_open()){

		string line;
		while(getline(fin, line)){
			line+='\n';
			loaded_text.push_back(line);
		}
	}else{
		string line = "File not valid";
		loaded_text.push_back(line);
	}
	fin.close();
	return loaded_text;	
}

void print_text_at_loc(WINDOW * win, vector<string> text, int xloc, int yloc){
	
	wmove(win, yloc+1,xloc+1);
	refresh();
	wrefresh(win);
	waddch(win, text[yloc][xloc]);
	wrefresh(win);

}

vector<string> input_text(vector<string> text, int cursorx, int cursory, WINDOW * win){

	int max_cols = getmaxy(win);
	char c = getch();
	if (cursorx==text[cursory].length()){
		text[cursory]+=c;
	}
	else if (cursorx<=text[cursory].length()){
		char dum = text[cursory][cursorx];
		text[cursory][cursorx]= c;
		text[cursory][cursorx+1]=dum;
		for (int i=2; i<text[cursory].length()-cursorx;i++){
			text[cursory][cursorx+i]=text[cursory][cursorx+i-1];
		}
	}
	else if (cursorx>text[cursory].length()){
		cursorx = text[cursory].length();
	};
	if(text[cursory].length()>max_cols){
		string newline="";
		for (int i=1; i<text[cursory].length()-max_cols; i++){
			newline+=text[cursory][i-1];
		}
		//text.insert(cursory , newline);
	}
	
	return text;
}

vector<string> start_text(string filename, WINDOW * win){
	int win_x_end = getmaxx(win);
	if(filename=="newfile123"){
		vector<string> text;
		return text;
	}else{
		vector<string> text = load_text(filename);
		wclear(win);
		int cursorx = 0, cursory = 0;
       		 WINDOW * win = newwin(5, win_x_end-4,2,2 );
       		 wrefresh(win);
		 box(win,0,0);
		 for(int i=0; i<text.size();i++){
		 	for(int j=0; j<text[i].length();j++){
				print_text_at_loc(win, text, j, i);
			}
		 }
		 print_text_at_loc(win, text, text.size() , text[text.size()-1].length());
		 wrefresh(win);
		 refresh();
		 return text;
	};

}

vector<string> type_text(vector<string> text, int cursorx, int cursory, WINDOW * win){

	wrefresh(win);
	refresh();
	string line;
	
	

}

int * cursorcontrol(int arrow, int cursorx, int cursory){

	switch(arrow){

		case KEY_UP:
			cursory-=1;
			break;
		case KEY_DOWN:
			cursory+=1;
			break;
		case KEY_LEFT:
			cursorx-=1;
			break;
		case KEY_RIGHT:
			cursorx+=1;
			break;
	}


}