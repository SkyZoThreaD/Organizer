

CFLAGS = -std=c++11 -I/usr/include/ -I/usr/include/gtkmm-3.0/ -I/usr/include/glibmm-2.4/ -I/usr/lib/x86_64-linux-gnu/glibmm-2.4/include/ -I/usr/include/glib-2.0/ -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/ -I/usr/include/sigc++-2.0/sigc++/ -I/usr/include/sigc++-2.0/ -I/usr/lib/x86_64-linux-gnu/sigc++-2.0/include/ -I/usr/include/giomm-2.4/ -I/usr/lib/x86_64-linux-gnu/giomm-2.4/include/ -I/usr/include/gdkmm-3.0/ -I/usr/lib/x86_64-linux-gnu/gdkmm-3.0/include/ -I/usr/lib/x86_64-linux-gnu/pangomm-1.4/include/ -I/usr/include/gtk-3.0/ -I/usr/include/pango-1.0/ -I/usr/include/cairo/ -I/usr/include/gdk-pixbuf-2.0/ -I/usr/include/cairomm-1.0/ -I/usr/include/freetype2/ -I/usr/lib/x86_64-linux-gnu/gtkmm-3.0/include/ -I/usr/include/pangomm-1.4/ -I/usr/include/atkmm-1.6/ -I/usr/include/atk-1.0/

LDFLAGS = $(shell pkg-config --cflags --libs gtkmm-3.0) -lmysqlcppconn

all: Organizer

Organizer: Organizer.o MainWindow.o DatabaseConnector.o AddWindow.o ModelColumns.o
	g++ -o Organizer Organizer.o MainWindow.o DatabaseConnector.o AddWindow.o ModelColumns.o $(LDFLAGS)

Organizer.o: Organizer.cpp
	g++ -o Organizer.o -c Organizer.cpp $(CFLAGS)

ModelColumns.o: ModelColumns.cpp
	g++ -o ModelColumns.o -c ModelColumns.cpp $(CFLAGS)

MainWindow.o: MainWindow.cpp
	g++ -o MainWindow.o -c MainWindow.cpp $(CFLAGS)

AddWindow.o: AddWindow.cpp
	g++ -o AddWindow.o -c AddWindow.cpp $(CFLAGS)

DatabaseConnector.o: DatabaseConnector.cpp
	g++ -o DatabaseConnector.o -c DatabaseConnector.cpp $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf Organizer


