/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*Includes*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
/*banner map contains the "font", banner help contains help string*/
#include "bannerMap.h"
#include "bannerHelp.h"

/* making bool type avaliable */
typedef int bool;
#define true  1
#define false 0


/*Variables */
int width;
char character;
bool useCharacter = false;
bool useLetterChar = false;
bool rawInput = false;
int enc(int c) { return strchr(vec,c)-vec; }
bool stdinEnable = false;
/* this function is responsible for printing*/
void show(char *s) {
    int row,col;
    char *sp;

    if(useLetterChar == true){
        for (row=0; row<8; row++, putchar('\n'))/*after each level of text print next line*/
            for (sp = s; *sp; sp++)
                if (strchr(vec,*sp)!=NULL)
                    for (col=0; col<8; col++)
                        /*if is then print else print ' '*/
                        putchar(map[enc(*sp)][row] & 1<<col ? *sp:' ');
    }else if ( useCharacter == true){
        for (row=0; row<8; row++, putchar('\n'))
            for (sp = s; *sp; sp++)
                if (strchr(vec,*sp)!=NULL)
                    for (col=0; col<8; col++)
                        /*if is then print else print ' '*/
                        putchar(map[enc(*sp)][row] & 1<<col ? character:' ');}
    else {
        for (row=0; row<8; row++, putchar('\n'))
            for (sp = s; *sp; sp++)
                if (strchr(vec,*sp)!=NULL)
                    for (col=0; col<8; col++)
                        /*if is then print else print ' '*/
                        putchar(map[enc(*sp)][row] & 1<<col ? '#':' ');}
}

/*Function return
 * 2 when it's -n arg. In main it makes pushing one string foreward and printing raw input 
 * 1 - when find -[option]
 * -1 when there is error
 *    errors: when printing char is already initialize
 * 0 when there is no -[char] options or when -[char] or -n option is used
 * This function set variables for printing
 */ 

int scanForVar(char *s){
    if (s[0] == '-'){
        /* -C -c Character printing section*/ 
        if (s[1] == 'C' || s[1] == 'c'){
            if (s[2] != '\0') {
                if (useCharacter == true ){
                    fprintf(stderr,"bad syntax double -C or -c initializing \n");
                    fflush(stderr);
                    /*exit with code 255 smth for bash lovers echo $?*/
                    exit( -1 ); 
                }else{
                    useCharacter = true;
                    character = s[2];
                    return 1; 
                }
            }
            else {
                fprintf(stderr,"bad syntax: there is no character ex. usage -Ca or -cR\n");
                fflush(stderr);
                exit ( -1 );
            }
            /* -s -S same as letter Character printing section */
        }else if (s[1] == 'S' || s[1]=='s'){
            if (useLetterChar == true ){
                fprintf(stderr,"bad syntax double -S or -s initializing \n");
                fflush(stderr);
                /*exit with code 255 sth for bash lovers echo $?*/
                exit( -1 ); 
            }else{
                useLetterChar = true;
            }
            return 1;
            /* -n -N RAW input selecting section */ 
        }else if (s[1] == 'N' || s[1]=='n'){
            rawInput = true;     

            return 2;
        }else if (s[1] == 'I' || s[1]=='i'){
            stdinEnable = true;     

            return 2;
        } 
        else {
            fprintf(stderr,"bad syntax: there is no character ex. usage -Ca or -cR\n");
            fflush(stderr);
            exit ( -1 );
        }
    } 

    return 0;
}
void findTerminalWidth(void){
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    width = w.ws_col;
}
/*main takes args from command line*/

int main(int argc,char **argv){

    int howManyVarArgs=0;
    char **v = argv;
    int c = argc;
    for (v++,c--;*v;v++,c--){
        int tmp = scanForVar(*v);
        if( tmp == 1 ){
            howManyVarArgs++;
        } else  if ( tmp == 2) {
            howManyVarArgs++;
            if (howManyVarArgs !=1){
                fprintf(stderr, "You can't use -n or -N with other switches\n");
                fflush (stderr);
                exit (-1);
            } 
            break;
        }
        else {
            break;
        }

    }
    
    findTerminalWidth(); 
    int maxCharsToPrint = (width/8);
    char* maxStringToPrint=(char*)malloc(maxCharsToPrint+1);

    v = argv+howManyVarArgs;
    c = argc -howManyVarArgs;
    
    char line [300];
    /*info about stdin*/ 
    if (argc == 1 && stdinEnable == false){
        printf ("%s",bannerHelpString);
    }
    /* smart for it takes line */
    if (stdinEnable == false){
        for (v++,c--;*v;v++,c--){
            strncpy(maxStringToPrint, *v, maxCharsToPrint);
            /* Just in case */
            maxStringToPrint[maxCharsToPrint]=0;
            show(maxStringToPrint);
        }
    }
    else {
        while( scanf("%s",line) != EOF ){
             
            show (line); 
        }
    }

    return 0;
}
