CXXFLAGS_DEBUG = -std=c++20 -O0 -g3

CXXFLAGS_RELEASE = -std=c++20 -O3

CXXFLAGS_WARNINGS = -Wall -Wextra -Wpedantic -Werror

CXXFLAGS_SANITIZE = -fsanitize=address -fsanitize=undefined -fsanitize=shift -fsanitize=integer-divide-by-zero -fsanitize=unreachable -fsanitize=vla-bound -fsanitize=null -fsanitize=return -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=bounds-strict -fsanitize=alignment -fsanitize=object-size -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=nonnull-attribute -fsanitize=returns-nonnull-attribute -fsanitize=bool -fsanitize=enum -fsanitize=vptr

CXXFLAGS_ALLEGRO = $(shell pkg-config --libs --cflags allegro-5 allegro_font-5 allegro_image-5 allegro_ttf-5 allegro_primitives-5)

CXX = g++

OBJECTS = ProyectoJuegoUnison/Boton.o \
	ProyectoJuegoUnison/Comprador.o \
	ProyectoJuegoUnison/DrawObjects.o \
	ProyectoJuegoUnison/GuardarDatos.o \
	ProyectoJuegoUnison/InitMap.o \
	ProyectoJuegoUnison/MainGame.o \
	ProyectoJuegoUnison/Mochila.o \
	ProyectoJuegoUnison/Objetcs.o \
	ProyectoJuegoUnison/Objeto.o \
	ProyectoJuegoUnison/Personaje.o \
	ProyectoJuegoUnison/Player.o \
	ProyectoJuegoUnison/SubmenuOptions.o \
	ProyectoJuegoUnison/TiempoDia.o \
	ProyectoJuegoUnison/TiposCultivos.o \
	ProyectoJuegoUnison/sonidos.o

build: agromania-debug

agromania: CXXFLAGS = $(CXXFLAGS_RELEASE) $(CXXFLAGS_ALLEGRO)
agromania: ProyectoJuegoUnison/main.cpp $(OBJECTS)
	$(CXX) $(CXXFLAGS) $<

agromania-debug: CXXFLAGS = $(CXXFLAGS_DEBUG) $(CXXFLAGS_WARNINGS) $(CXXFLAGS_SANITIZE) $(CXXFLAGS_ALLEGRO)
agromania-debug: ProyectoJuegoUnison/main.cpp $(OBJECTS)
	$(CXX) $(CXXFLAGS) $<

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	rm -f ProyectoJuegoUnison/*.o

init: compile_flags.txt

compile_flags.txt: Makefile
	echo "-xc++"  > compile_flags.txt
	echo $(CXXFLAGS_DEBUG) | tr " " "\n" >> compile_flags.txt
	echo $(CXXFLAGS_WARNINGS) | tr " " "\n" >> compile_flags.txt
	echo $(CXXFLAGS_ALLEGRO) | tr " " "\n" >> compile_flags.txt
