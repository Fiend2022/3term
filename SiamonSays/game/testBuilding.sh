echo `g++ -c main.cpp player.cpp`
echo `g++ main.o player.o -o test -lsfml-window -lsfml-system -lsfml-graphics -lsfml-audio`
echo `./test`

