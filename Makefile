include .env

CC=clang++
APP_NAME = app
VERSION=-std=c++17 -g -fsanitize=address -fno-omit-frame-pointer -Wall -Wextra
BUILD_DIR = bin
C_FILES = ./src/*.cpp ./src/render/*.cpp ./src/scene/*.cpp ./src/resources/*.cpp ./src/mesh/*.cpp ./src/mesh/material/*.cpp  ./src/camera/*.cpp
HEADER_FILES = -I./src/utils/*.h -I./src/*.h -I./src/render/*.h -I./src/scene/*.h -I./src/resources/*.h -I./src/mesh/*.h -I./src/mesh/geometry/*.h -I./src/mesh/material/*.h  -I./src/camera/*.h
APP_INCLUDES = -I$(GLFW_PATH) -framework Cocoa -framework OpenGL -framework IOkit -I$(GLM_PATH) -I$(GLAD_PATH) -I${ASSIMP_INCLUDES_PATH}
APP_LINKERS = -L./deps/lib -lglfw3 -L${ASSIMP_BINARIES_PATH} -lassimp.5

build:
	$(CC) $(VERSION) $(C_FILES) $(ENGINE_FILES) $(MATH_FILES) -o $(BUILD_DIR)/$(APP_NAME) $(APP_INCLUDES) $(HEADER_FILES) $(APP_LINKERS)

clean:
			rm -rf bin/app
