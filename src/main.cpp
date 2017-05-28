#include "MusicPlayer.h"

int main(int argv, char** args) {
	
	MusicPlayer player;
	player.init();
	
	player.addMusic("../media/songs/Detonautas_-_O_dia_que_nao_terminou.ogg");
	player.addMusic("../media/songs/Los_Hermanos_-_Anna_Julia.ogg");
	player.addMusic("../media/songs/Marcelo_D2_-_Desabafo_Desabafo.ogg");
	player.addMusic("../media/songs/I_heard_it_through_the_grapevine_-_Creedence.ogg");
	
	player.play();
	
	while(1) player.update();
	
	return 0;
}
