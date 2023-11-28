all:
	g++ -IC:\SFML-2.5.1\include -LC:\SFML-2.5.1\lib \
	./source/button.cpp ./source/menu.cpp          ./source/window.cpp  ./source/canvas.cpp  \
	./source/main.cpp   ./source/region.cpp        ./source/widgets.cpp ./source/ui.cpp      \
	./source/tool.cpp   ./source/vect.cpp          ./source/events.cpp  ./source/editBox.cpp \
	./source/filter.cpp ./source/renderTarget.cpp  ./source/gui.cpp                          \
	-lm -o ps.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-main -mwindows

reg:
	g++ -IC:\SFML-2.5.1\include -LC:\SFML-2.5.1\lib \
	./source/button.cpp ./source/menu.cpp ./source/window.cpp ./source/canvas.cpp \
	./source/regionsDebug.cpp ./source/region.cpp ./source/widgets.cpp ./source/ui.cpp    \
	./source/tool.cpp ./source/vect.cpp ./source/events.cpp \
	-lm -o reg.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-main -mwindows

box:
	g++ -IC:\SFML-2.5.1\include -LC:\SFML-2.5.1\lib \
	./source/button.cpp ./source/menu.cpp ./source/window.cpp ./source/canvas.cpp \
	./source/debugEditBox.cpp ./source/region.cpp ./source/widgets.cpp ./source/ui.cpp    \
	./source/tool.cpp ./source/vect.cpp ./source/events.cpp ./source/editBox.cpp  \
	-lm -o box.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-main -mwindows

plugin:
	g++ ./plugins/Filter/abw_filter.cpp -shared -o ./plugins/DLL/abw_filter.dll