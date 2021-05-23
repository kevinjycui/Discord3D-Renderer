CXX = g++
CPPFLAGS = -lglfw -lGLU -lGL -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl -lstb -pthread -DBOOST_ERROR_CODE_HEADER_ONLY -lboost_system

main: src/* include/*
	$(CXX) src/* /usr/local/include/glad/glad.c $(CPPFLAGS) -o main

install:
	sudo apt update
	sudo apt install libgl-dev dos2unix git wget libx11-dev xorg-dev libglm-devi libstb-dev libglfw3 libglfw3-dev libwebsocketpp-dev libboost-all-dev rapidjson-dev
	git clone https://github.com/Dav1dde/glad.git
	cd glad
	cmake ./
	make
	sudo cp -a include /usr/local/
