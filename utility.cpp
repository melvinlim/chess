#include"utility.h"
void Utility::stringToCoord(string s,Coord &coord){
	int j=toupper(s[0])-65;
	int i=7-(s[1]-49);
	printf("%s -> %d %d\n",s.data(),i,j);
	coord.i=i;
	coord.j=j;
}
