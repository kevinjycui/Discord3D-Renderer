CXX = g++
CPPFLAGS = -lglfw -lGLU -lGL -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl -lstb
# CPPFLAGS = -lGL -lGLU -lglut -lGLEW -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl

main: src/* include/*
	$(CXX) src/* /usr/local/include/glad/glad.c $(CPPFLAGS) -o main

install:
	sudo apt update
	sudo apt install mesa mesa-utils freeglut3-dev libgl-dev dos2unix git wget libx11-dev xorg-dev libglu1-mesa-dev libglew1.5 libglew1.5-dev libglu1-mesa libglu1-mesa-dev libgl1-mesa-glx libgl1-mesa-dev libglm-devi libstb-dev libglfw3 libglfw3-dev
	git clone https://github.com/Dav1dde/glad.git
	cd glad
	cmake ./
	make
	sudo cp -a include /usr/local/
