#This make file is made for my projects
#All codes are avaliavle in my github

CC = gcc
CFlags = -Wall -ansi -g


banner:	banner.c
	$(CC) $(CFlags) -o banner banner.c
clean:
	rm -f banner
install:
	install banner /usr/bin/
