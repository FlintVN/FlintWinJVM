
PROJECT_NAME    :=  FlintJVM
BUILD_DIR       :=  Build
BIN_DIR         :=  $(BUILD_DIR)/Bin
OBJECT_DIR      :=  $(BUILD_DIR)/Obj

CC              :=  g++

SOURCES       	:=  User/Src/main.cpp                                           \
                    User/Src/windows_system_api.cpp                             \
                    User/Src/windows_system_io_api.cpp                          \
                    User/Src/windows_system_thread_api.cpp                      \
                    User/Src/windows_system_native.cpp                          \
                    User/Src/windows_tcp_debugger.cpp                           \
                    FlintJVM/VM/Src/flint.cpp                                   \
                    FlintJVM/VM/Src/flint_utf8.cpp                              \
                    FlintJVM/VM/Src/flint_mutex.cpp                             \
                    FlintJVM/VM/Src/flint_common.cpp                            \
                    FlintJVM/VM/Src/flint_const_pool.cpp                        \
                    FlintJVM/VM/Src/flint_fields_data.cpp                       \
                    FlintJVM/VM/Src/flint_field_info.cpp                        \
                    FlintJVM/VM/Src/flint_method_info.cpp                       \
                    FlintJVM/VM/Src/flint_java_class.cpp                        \
                    FlintJVM/VM/Src/flint_java_object.cpp                       \
                    FlintJVM/VM/Src/flint_java_string.cpp                       \
                    FlintJVM/VM/Src/flint_java_thread.cpp                       \
                    FlintJVM/VM/Src/flint_java_throwable.cpp                    \
                    FlintJVM/VM/Src/flint_array_object.cpp                      \
                    FlintJVM/VM/Src/flint_class_loader.cpp                      \
                    FlintJVM/VM/Src/flint_execution.cpp                         \
                    FlintJVM/VM/Src/flint_debugger.cpp                          \
                    FlintJVM/VM/Src/flint_utf8_dict_node.cpp                    \
                    FlintJVM/VM/Src/flint_java_class_dict_node.cpp              \
                    FlintJVM/VM/Src/flint_java_string_dict_node.cpp             \
                    FlintJVM/Native/Src/flint_native_interface.cpp              \
                    FlintJVM/Native/Src/flint_native.cpp                        \
                    FlintJVM/Native/Src/flint_native_math.cpp                   \
                    FlintJVM/Native/Src/flint_native_class.cpp                  \
                    FlintJVM/Native/Src/flint_native_array.cpp                  \
                    FlintJVM/Native/Src/flint_native_float.cpp                  \
                    FlintJVM/Native/Src/flint_native_double.cpp                 \
                    FlintJVM/Native/Src/flint_native_object.cpp                 \
                    FlintJVM/Native/Src/flint_native_string.cpp                 \
                    FlintJVM/Native/Src/flint_native_system.cpp                 \
                    FlintJVM/Native/Src/flint_native_thread.cpp                 \
                    FlintJVM/Native/Src/flint_native_character.cpp              \
                    FlintJVM/Native/Src/flint_native_reflection.cpp             \
                    FlintJVM/Native/Src/flint_native_print_stream.cpp

INCLUDES      	:=  FlintJVM/Native/Inc                                         \
                    FlintJVM/VM/Inc                                             \
                    User/Inc

OPT             :=  -g

CFLAGS          :=  -m32                                                        \
                    -std=c++20                                                  \
                    -fdiagnostics-color=always                                  \
                    -static -static-libgcc -static-libstdc++                    \
                    -Wall                                                       \
                    -Wno-sign-compare                                           \
                    -Wno-strict-aliasing                                        \
                    -Wno-uninitialized                                          \
                    $(addprefix -I,$(INCLUDES))                                 \
                    $(OPT)

LIBS            :=  -lws2_32

OBJECTS         +=  $(addprefix $(OBJECT_DIR)/,$(SOURCES:.cpp=.o))

BUILD_DIRS      :=  $(sort $(dir $(OBJECTS))) $(BIN_DIR)
BUILD_DIRS      :=  $(BUILD_DIRS:/=)

GREEN           :=  \033[0;32m
CYAN            :=  \033[0;36m
RESET           :=  \033[0m

all: $(BIN_DIR)/$(PROJECT_NAME).exe

$(BUILD_DIRS):
	@mkdir -p $@

$(OBJECT_DIR)/%.o: %.cpp Makefile | $(BUILD_DIRS)
	@echo -e "$(CYAN)Compiling$(RESET)" $<
	@$(CC) -c $(CFLAGS) $< -o $@

$(BIN_DIR)/$(PROJECT_NAME).exe: $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LIBS)
	@echo -e "$(GREEN)Build complete$(RESET)"

clean:
	@rm -rf $(OBJECT_DIR) $(BIN_DIR)/$(PROJECT_NAME).exe
	@echo -e "$(GREEN)Clean complete$(RESET)"
