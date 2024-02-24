# Apple Game
Учебный проект для XYZ-School курс "C++ для разработки игр"

## Сборка и компиляция

###  Зависимости для Linux (Ubuntu)
```sh
    sudo apt update
    sudo apt install \
        libxrandr-dev \
        libxcursor-dev \
        libudev-dev \
        libfreetype-dev \
        libopenal-dev \
        libflac-dev \
        libvorbis-dev \
        libgl1-mesa-dev \
        libegl1-mesa-dev
```
### MacOS и Linux
```sh
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
    cmake --build build
```

### Windows
```sh
    cmake -S . -B build
    cmake --build build --config Release
```

## License

The source code is dual licensed under Public Domain and MIT -- choose whichever you prefer.
