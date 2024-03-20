include .env

CC=clang++
APP_NAME = app
VERSION=-std=c++17 -g -fsanitize=address -fno-omit-frame-pointer -Wall -Wextra
BUILD_DIR = bin
C_FILES = ./src/*.cpp ./src/context/*.cpp ./src/scene/*.cpp ./src/resources/*.cpp  ./src/camera/*.cpp ./src/systems/*.cpp ./src/systems/lights/*.cpp ./src/systems/objects/*.cpp ./src/systems/skybox/*.cpp ./src/systems/terrain/*.cpp ./deps/ImGui/*.cpp
HEADER_FILES = -I./src/utils/*.h -I./src/*.h -I./src/context/*.h -I./src/scene/*.h -I./src/resources/*.h -I./src/camera/*.h -I./src/systems/*.h -I./src/systems/lights/*.h -I./src/systems/objects/*.h -I./src/systems/skybox/*.h -I./src/systems/terrain/*.h
APP_INCLUDES = -I$(GLFW_PATH) -framework Cocoa -framework OpenGL -framework IOkit -I$(GLM_PATH) -I$(GLAD_PATH) -I${ASSIMP_INCLUDES_PATH} -I./deps/ImGui/*.h
APP_LINKERS = -L./deps/lib -lglfw3 -L${ASSIMP_BINARIES_PATH} -lassimp.5 

build:
	$(CC) $(VERSION) $(C_FILES) $(ENGINE_FILES) $(MATH_FILES) -o $(BUILD_DIR)/$(APP_NAME) $(APP_INCLUDES) $(HEADER_FILES) $(APP_LINKERS)

clean:
			rm -rf bin/app
