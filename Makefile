all:
	g++ -IC:\SFML-2.5.1\include -LC:\SFML-2.5.1\lib ./source/main.cpp ./source/region.cpp ./source/widgets.cpp ./source/ui.cpp -lm -o ps.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-main -mwindows