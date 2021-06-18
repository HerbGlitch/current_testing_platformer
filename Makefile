all: compile link

test: compile link run

compile: main_code menu game

main_code:
	cd src/compiled && g++ -isystem../../src/include -c ../../platformer/main.cpp -o main.o -Wall -Werror

menu:
	cd src/compiled && g++ -isystem../../src/include -c ../../platformer/menu/menu.cpp -o menu.o -Wall -Werror
	cd src/compiled && g++ -isystem../../src/include -c ../../platformer/menu/components/uibox.cpp -o uibox.o -Wall -Werror
	cd src/compiled && g++ -isystem../../src/include -c ../../platformer/menu/components/button.cpp -o uiboxbutton.o -Wall -Werror

game:
	cd src/compiled && g++ -isystem../../src/include -c ../../platformer/game/game.cpp -o game.o -Wall -Werror
	cd src/compiled && g++ -isystem../../src/include -c ../../platformer/game/player/player.cpp -o player.o -Wall -Werror
	cd src/compiled && g++ -isystem../../src/include -c ../../platformer/game/map/map.cpp -o map.o -Wall -Werror

link:
	g++ src/compiled/*.o -o main -lsfml-graphics -lsfml-window -lsfml-system

run:
	./src/bin/main
