include .env

CC=clang++
APP_NAME = app
VERSION=-std=c++17
BUILD_DIR = bin
C_FILES = ./src/*.cpp

APP_INCLUDES:= -I$(GLFW_PATH) -framework Cocoa -framework OpenGL -framework IOkit -I$(GLM_PATH) -I$(GLAD_PATH) -I./src/utils/*.h -I./src/*.h
APP_LINKERS:= -L./deps/lib -lglfw3

build:
	$(CC) $(VERSION) $(C_FILES) $(ENGINE_FILES) $(MATH_FILES) -o $(BUILD_DIR)/$(APP_NAME) $(APP_INCLUDES) $(APP_LINKERS)

clean:
			rm -rf bin/app
