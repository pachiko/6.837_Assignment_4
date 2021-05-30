#!/bin/sh
rm *.tga
rm *.bmp

./a4 -input scene01_plane.txt  -size 200 200 -output 1.bmp -depth 1 35 depth01.bmp -normals normal01.bmp
./a4 -input scene02_cube.txt  -size 200 200 -output 2.bmp -depth 1 35 depth02.bmp -normals normal02.bmp
./a4 -input scene03_sphere.txt  -size 200 200 -output 3.bmp -depth 1 35 depth03.bmp -normals normal03.bmp
./a4 -input scene04_axes.txt  -size 200 200 -output 4.bmp -depth 1 35 depth04.bmp -normals normal04.bmp
./a4 -input scene05_bunny_200.txt  -size 200 200 -output 5.bmp -depth 1 35 depth05.bmp -normals normal05.bmp
./a4 -input scene06_bunny_1k.txt  -size 200 200 -output 6.bmp -depth 1 35 depth06.bmp -normals normal06.bmp
./a4 -input scene07_shine.txt  -size 200 200 -output 7.bmp -depth 1 35 depth07.bmp -normals normal07.bmp
./a4 -input scene08_c.txt -size 200 200 -output 8.bmp -depth 1 35 depth08.bmp -normals normal08.bmp
./a4 -input scene09_s.txt -size 200 200 -output 9.bmp -depth 1 35 depth09.bmp -normals normal09.bmp
