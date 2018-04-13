XLIBS = -L /usr/X11/lib -L /usr/X11R6/lib -lX11 -lXext -lXi -lXmu

GLUTFenetre: GLUTFenetre.o
	g++ -o GLUTFenetre GLUTFenetre.o l $(XLIBS) -lm
GLUTFenetre.o: GLUTFenetre.cxx
	g++ -c GLUTFenetre.cxx
