char bannerHelpString [] = {"\
******************** This program is distributed in the hope that it will be useful, ********************\n\
******************** but WITHOUT ANY WARRANTY; without even the implied warranty of ********************\n\
******************** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the ********************\n\
******************** GNU General Public License for more details. ********************\n\
This is help for banner program \n\
You can use this program in 2 ways\n\
1) Without any option selected.\n\
\t\"banner this is sentence\" will output as separate lines\n\
\t\"banner \"this is a sentence\"\" will print one line \n\
2) with options \n\
\tbanner [options] words  \n\
\t-c [CHAR] change output character\n\
\t-s printing character is the same as letter\n\
\t-i reads from stdin\n\
\t-n no options print every line as it is try \"banner -s -n\" \"banner -n -s -n\"\n\
"};
