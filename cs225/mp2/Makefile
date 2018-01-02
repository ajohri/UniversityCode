all : testimage

testimage : testimage.o png.o rgbapixel.o image.o
	clang++ testimage.o png.o rgbapixel.o image.o -std=c++1y -stdlib=libc++ -lpng -lc++abi -o testimage

testimage.o : testimage.cpp
	clang++ -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic testimage.cpp

png.o : png.cpp png.h rgbapixel.h
	clang++ -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic png.cpp

image.o : image.cpp image.h
	clang++ -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic image.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	clang++ -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic rgbapixel.cpp

clean : 
	-rm -f *.o testimage

all : testscene

testscene : testscene.o png.o rgbapixel.o scene.o image.o
	clang++ testscene.o png.o rgbapixel.o scene.o image.o -std=c++1y -stdlib=libc++ -lpng -lc++abi -o testscene

testscene.o : testscene.cpp
	clang++ -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic testscene.cpp

png.o : png.cpp png.h rgbapixel.h
	clang++ -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic png.cpp

image.o : image.cpp image.h
	clang++ -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic image.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	clang++ -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic rgbapixel.cpp

scene.o : scene.h scene.cpp
	clang++ -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic scene.cpp

clean : 
	-rm -f *.o testscene
