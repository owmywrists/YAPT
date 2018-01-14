#YAPT

Yet Another PathTracer

to build:
- type "git clone --recursive https://github.com/owmywrists/YAPT
- add a lib folder and put glew and sfml inside
- copy imgui-sfml/imconfig-SFML.h to imgui/imconfig.h
- create build folder and inside run "cmake .."

Features:
- KD Trees
- Materials: emissive, lambertian, mirror
- Interactive rendering

TODO:
- Mix materials
- Fix normal issues
- Better sampling methods

example renders:
![Alt text](image_lighting.png?raw=true "Image Based lighting")
![Alt text](dragon.png?raw=true "Dragon clay")
![Alt text](test_github.gif?raw=true "ImGUI test")
![Alt text](suzanne.png?raw=true "Suzanne render")
![Alt text](finalrender.png?raw=true "Final render 12500 samples")
![Alt text](example.gif?raw=true "Example")
