all : mp1

mp1 : main.o png.o rgbapixel.o
	clang++ main.o png.o rgbapixel.o -std=c++1y -stdlib=libc++ -lpng -lc++abi -o mp1

main.o : main.cpp png.h rgbapixel.h
	clang++ -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic main.cpp

png.o : png.cpp png.h rgbapixel.h
	clang++ -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic png.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	clang++ -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic rgbapixel.cpp

clean :
	-rm -f *.o mp1
