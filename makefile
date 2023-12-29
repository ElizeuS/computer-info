build:
	gcc ./main.c ./modules/disk_info.c ./modules/system_info.c -o main.o -I modules
run:
	./main.o	