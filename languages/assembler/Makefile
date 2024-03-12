# ld (GNU Linker, используемый для связывания объектных файлов в ELF
# -s опция для удаления всех символьных таблиц и отладочной информации
#
# nasm программа ассемблер
# -f elf64 указывает формат выходного файла (ELF 64 бита)

hello: hello.o
	ld -o hello hello.o

hello.o: hello.asm
	nasm -f elf64 hello.asm -o hello.o

clean:
	rm hello *.o >/dev/null
