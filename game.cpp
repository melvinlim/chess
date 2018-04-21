#include"game.h"
Game::Game(){
	board=new Board();
	board->reset();
}
void Game::step(){
	board->debug();
	board->display(false);
	board->display();
}
