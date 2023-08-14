#include <ncurses.h>
#include <iostream>
#include <string>
#include <vector>


using namespace std;

// typedef struct curs {
//     int x;
//     int y;
// }curs;

char typing(int cursorx, int cursory, WINDOW * printt, string text, vector<string>line){
        char c=getch();
        box(printt,0,0);
        int newline = 0;
        string linestring="";
        while(c!=27){
            if(c == '\n'){
                newline++;
                line.push_back(linestring);
                linestring.replace(0,linestring.length(),"");
                cursorx=0;
                cursory+=1;
            };
            text+=c;         
            if(c!='\n'){
                linestring+=c;
                cursorx+=1;
                };
            wmove(printt, cursory +1,cursorx+1);
            mvcur(50,50, cursory+1, cursorx+1);
            wrefresh(printt);
            refresh();
            wprintw(printt,"%c",linestring[linestring.length()-1]); 
            wrefresh(printt);
            c = getch();
        }
        
        if (c == 27){
            char a;
            a = getch();
            if(a == 91){
                char arrow;
                arrow = getch();
                switch (arrow)
                {
                case 65:
                    cursory=cursory-1;
                    typing(cursorx, cursory, printt, text, line);
                    break;
                case 66:
                    cursory=cursory+1;
                    typing(cursorx, cursory, printt, text, line);
                    break;
                case 67:
                    cursorx=cursorx+1;
                    typing(cursorx, cursory, printt, text, line);
                    break;
                case 68:
                    cursorx=cursorx-1;
                    typing(cursorx, cursory, printt, text, line);
                    break;
                default:
                    break;
                }
                
            }
        }
        return c;

}




int main(int argc, char ** argv)
{
    // init screen and sets up screen
    initscr();
    WINDOW * win = newwin(50,100, 2, 5);
    int cursorx=0; int cursory=0;
    refresh();
    box(win, 0,0);
    wrefresh(win);
    // print to screen
    noecho();
    mvwprintw(win, 1, 1, "Welcome, press i to insert text");
    wrefresh(win);
    // refreshes the screen
    //refresh();
    // pause the screen output
    char i;
    i = getch();
    if(i == 'i'){
        string text = "";
        refresh();
        wrefresh(win);
        mvwprintw(win, 5, 2, "press escape to escape");
        wrefresh(win);
        getch();
        wrefresh(win);
        wclear(win);
        //char c=getch();
        refresh();
        wrefresh(win);
        WINDOW * printt = newwin(50,100, 2, 2);
        vector <string> line;
        char c = typing( cursorx, cursory, printt, text, line);
        
        // box(printt,0,0);
        // int newline = 0;
        // vector <string> line;
        // string linestring="";
        // while(c!=27){
        //     if(c == '\n'){
        //         newline++;
        //         line.push_back(linestring);
        //         linestring.replace(0,linestring.length(),"");
        //     };
        //     text+=c;         
        //     if(c!='\n'){linestring+=c;};
        //     mvwprintw(printt, newline +1,linestring.length()+1,"%c",linestring[linestring.length()-1]); 
        //     wrefresh(printt);
        //     c = getch();
        // }
        // for(int i=0; i<text.length(); i++){
        //     wprintw(printt,"%c",text[i]); 
        //     wrefresh(printt); 
        // }
        

        wrefresh(printt);

       getch();
    }
    

    // deallocates memory and ends ncurses
    endwin();
    return 0;
}