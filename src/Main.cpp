#include "GameWindow.h"
#include "al.h" 
#include "alc.h" 

int main(int argc, char** argv)
{
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);
	GameWindow window = GameWindow( "Game", argc, argv);
}