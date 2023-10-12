all:
<<<<<<< HEAD
	g++ -IC:\SFML-2.5.1\include -LC:\SFML-2.5.1\lib \
	./source/button.cpp ./source/menu.cpp ./source/window.cpp ./source/canvas.cpp \
	./source/main.cpp ./source/region.cpp ./source/widgets.cpp ./source/ui.cpp    \
	./source/tool.cpp \
	-lm -o ps.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-main -mwindows
=======
	g++ -IC:\SFML-2.5.1\include -LC:\SFML-2.5.1\lib ./source/main.cpp -lm -o ps.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-main -mwindows 
>>>>>>> parent of 03800ab (MainScreen added)
