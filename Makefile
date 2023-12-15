all:
	g++ -IC:\SFML-2.5.1\include -LC:\SFML-2.5.1\lib \
	./source/button.cpp ./source/menu.cpp          ./source/window.cpp   ./source/canvas.cpp        \
	./source/main.cpp   ./source/region.cpp        ./source/widgets.cpp  ./source/ui.cpp            \
	./source/tool.cpp   ./source/pluginManager.cpp ./source/events.cpp   ./source/editBox.cpp       \
	./source/filter.cpp ./source/renderTarget.cpp  ./source/gui.cpp      ./source/vect.cpp          \
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
	g++ ./plugins/Filters/abw_filter.cpp -shared -o ./plugins/DLL/abw_filter.dll

Senya_Plugin:
	g++ ./plugins/Filters/test_plugin.cpp -shared -o ./plugins/DLL/filter228.dll

elipse:
	g++ ./plugins/Tools/elipseTool.cpp -shared -o ./plugins/DLL/elipse_tool.dll

square:
	g++ ./plugins/Tools/squareTool.cpp -shared -o ./plugins/DLL/square_tool.dll

spline_tool:
	g++ ./plugins/Tools/splineTool/catmullrom.cpp \
		./plugins/Tools/splineTool/texture.cpp    ./plugins/Tools/splineTool/vec2.cpp		\
		./plugins/Tools/splineTool/spline_tool.cpp -shared -o ./plugins/DLL/splineTool.dll

sphere_filter:
	g++ -IC:\SFML-2.5.1\include -LC:\SFML-2.5.1\lib \
	./plugins/Filters/sphere_filter/sphere_filter.cpp ./plugins/Filters/sphere_filter/vector.cpp \
	-shared -o ./plugins/DLL/sphereFilter.dll -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-main -mwindows
