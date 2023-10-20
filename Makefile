all:
	g++ -IC:\SFML-2.5.1\include -LC:\SFML-2.5.1\lib \
	./source/button.cpp ./source/menu.cpp ./source/window.cpp ./source/canvas.cpp \
	./source/main.cpp ./source/region.cpp ./source/widgets.cpp ./source/ui.cpp    \
	./source/tool.cpp ./source/vect.cpp \
	-lm -o ps.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-main -mwindows

reg:
	g++ -IC:\SFML-2.5.1\include -LC:\SFML-2.5.1\lib \
	./source/button.cpp ./source/menu.cpp ./source/window.cpp ./source/canvas.cpp \
	./source/regionsDebug.cpp ./source/region.cpp ./source/widgets.cpp ./source/ui.cpp    \
	./source/tool.cpp ./source/vect.cpp \
	-lm -o reg.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-main -mwindows