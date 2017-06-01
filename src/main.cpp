#include "MusicPlayer.h"

int main(int argc, char** argv) {
	
	MusicPlayer player;
	if (!player.init()) {
		player.printError();
	else {
		if (argc == 1) {
			player.addMusic("../media/songs/Detonautas_-_O_dia_que_nao_terminou.ogga");
			player.addMusic("../media/songs/Los_Hermanos_-_Anna_Julia.ogg");
			player.addMusic("../media/songs/Marcelo_D2_-_Desabafo_Desabafo.ogg");
			player.addMusic("../media/songs/I_heard_it_through_the_grapevine_-_Creedence.ogg");
		} else
			for (int i = 1; i < argc; i++)
				player.addMusic(argv[i]);
		
		player.play();
		
		while(1)
			player.update();
	}
	
	return 0;
}