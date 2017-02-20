all: sine tri exp

sine: sine.c
	gcc sine.c -o sine -lm
	./sine 4096 176 3460 180 > ../Source/sinewave.h

tri: tri.c
	gcc tri.c -o tri -lm
	./tri 4096 176 3460 180 > ../Source/trianglewave.h

exp: exp.c
	gcc exp.c -o exp -lm

clean:
	rm sine exp tri

