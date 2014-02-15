main: main.o carte.o graphique.o robot.o
	gcc main.o carte.o graphique.o robot.o -lSDL -lSDL_ttf -lSDL_mixer -lSDL_image -o robot
carte.o: carte.c carte.h
	gcc -g -c carte.c
graphique.o: graphique.c graphique.h
	gcc -g -c graphique.c
main.o: main.c carte.h robot.h appart.h
	gcc -g -c main.c
robot.o: robot.c robot.h carte.h
	gcc -g -c robot.c
clean:
	rm *.o robot
