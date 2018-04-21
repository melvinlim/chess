#include<iostream>
#include"game.h"
using namespace std;
Game::Game(){
	board=new Board();
	board->reset();
	p1=new Human(White);
	p2=new Human(Black);
	move.quit=false;
	running=true;
}
void Game::start(){
	while(running){
		step();
	}
}
void Game::step(){
//	board->debug();
//	board->display(false);
	board->display();
	prompt(move);
	p1->decide(move);
	if(move.quit){
		running=false;
		return;
	}
	board->move(move);
}
Square *Game::coordToSquare(string s,Coord &coord){
	int j=toupper(s[0])-65;
	int i=7-(s[1]-49);
	printf("%s -> %d %d\n",s.data(),i,j);
	coord.i=i;
	coord.j=j;
	return board->square[i][j];
}
int Game::getCoord(string type,Move &move){
	Square *square;
	printf(":");
	cin>>str;
	if((str.size()==1)&&((str[0]=='q')||(str[0]=='Q'))){
		move.quit=true;
		return 0;
	}
	//if((str.size()!=2)||(!isalpha(str[0]))||(!isnumber(str[1]))){
	int npart=str[1]-48;
	char apart=tolower(str[0]);
	if((str.size()!=2)||(apart<'a')||(apart>'h')||(npart<1)||(npart>8)){
		printf("%s must be a letter from A-H followed by a number from 1-8.\n",type.data());
		return -1;
	}
	if(type[0]=='s'){
		square=coordToSquare(str,move.src);
		if(square->piece==0){
			printf("%s must be occupied.\n",type.data());
			return -1;
		}
	}else{
		square=coordToSquare(str,move.dst);
		if(square->piece!=0){
			//printf("%x\n",square->piece);
//			square->piece->display();
			printf("%s must be vacant.\n",type.data());
			return -1;
		}
	}
	return 0;
}
void Game::prompt(Move &move){
	int n;
	while((n=getCoord("starting square",move))<0);
	if(move.quit)	return;
	//move.src=n;
	while((n=getCoord("ending square",move))<0);
	if(move.quit)	return;
	//move.dst=n;
}
