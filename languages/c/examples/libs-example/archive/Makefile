# Какая бы не была библиотека (static or shared)
# будет писаться -lworld, НЕ -lworld.a или -lworld.so
# линковщику это неважно
#
# Опция -l посылает линковщику библиотеку (чтобы подключил к бинарнику)
# Опция -L указывает где искать библиотеку
# -L/usr или -L. (указывается путь)
#
# В случае если библиотека находится в /usr/lib или /lib
# тогда опция -L не требуется! В нашем случае библиотека находится
# в текущем каталоге, линковщик не просматривает этот каталог
# поэтому -L. требуется
#
binary: main.o libworld.a
	gcc -o binary main.o -L. -lworld

main.o: main.c
	gcc -c main.c

# Два объектных файла объединяются в один libworld.a (static lib)
# Так получается статическая библиотека
libworld.a: h_world.o g_world.o
	ar cr libworld.a h_world.o g_world.o

h_world.o: h_world.c
	gcc -c h_world.c

g_world.o: g_world.c
	gcc -c g_world.c

clean:
	rm -f *.o *.a binary
