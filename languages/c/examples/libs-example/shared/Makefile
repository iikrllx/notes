# Лучше помещать библиотеки в /usr/lib и /lib
# Иногда можно в /usr/local/lib
#
# -Wl,-rpath,. указывает что нужно искать в текущем каталоге
# Если убрать эту опция при запуске программы будет:
# error while loading shared libraries: libworld.so:
# cannot open shared object file: No such file or directory
#
binary: main.o libworld.so
	gcc -o binary main.o -L. -lworld -Wl,-rpath,.

main.o: main.c
	gcc -c main.c

# Создание shared библиотеки используется с -shared
# А статической с помощью ar
libworld.so: h_world.o g_world.o
	gcc -shared -o libworld.so h_world.o g_world.o

# Опции -fPIC сообщаются компилятору, что объектные файлы,
# должны содержать позиционно-независимый код (PIC), который
# используется в динамических библиотеках. Это позволяет
# коду из библиотеки подключаться к программе в момент запуска
#
h_world.o: h_world.c
	gcc -c -fPIC h_world.c

g_world.o: g_world.c
	gcc -c -fPIC g_world.c

clean:
	rm -f *.o *.so binary
