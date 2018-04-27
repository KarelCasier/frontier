# frontier

[trello board](https://trello.com/b/vcpQr5g3/frontier)

## dependencies

- CMake
- Ninja
- SDL2
- SDL2 image

### quickstart

#### macos

## install dependencies

```sh
brew install CMake Ninja sdl2 sdl2_image
brew install llvm
```

## clone

```sh
git clone git@github.com:KarelCasier/frontier.git
git submodule update --remote
```

## build

```sh
cd frontier
mkdir out/
cd out/
cmake ../src -G Ninja
ninja
ninja install
```

### tests

Currently only minimal tests in math library.

After build:
```sh
ninja test
# or
ctest
```

## run

```sh
./bin/frontier
```
