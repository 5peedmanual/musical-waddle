objs =	compile/download_file.o \
	compile/parse.o \
	compile/connect_to_site.o

download: download_file.o parse.o connect_to_site.o
	cc -c -g -Wall -g -o down $(objs)

download_file.o: download_file.c
	cc -c -g -Wall -c download_file.c -o compile/download_file.o

connect_to_site.o: connect_to_site.c
	cc -c -g -Wall -c connect_to_site.c -o compile/connect_to_site.o

parse.o: parse.c
	cc -c -g -Wall -c parse.c -o compile/parse.o


create:
	mkdir -p compile/

clear:
	rm -r compile/
	rm -r down
