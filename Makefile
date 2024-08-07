
PROJECT_NAME    :=  FlintJVM
BUILD_DIR       :=  Build
BIN_DIR         :=  $(BUILD_DIR)/Bin
OBJECT_DIR      :=  $(BUILD_DIR)/Obj

CC              :=  g++

SOURCES       	:=  FlintJVM/VM/Src/flint_attribute_info.cpp                    \
                    FlintJVM/VM/Src/flint_class_loader.cpp                      \
                    FlintJVM/VM/Src/flint_class.cpp                             \
                    FlintJVM/VM/Src/flint_common.cpp                            \
                    FlintJVM/VM/Src/flint_const_name.cpp                        \
                    FlintJVM/VM/Src/flint_const_pool.cpp                        \
                    FlintJVM/VM/Src/flint_debugger.cpp                          \
                    FlintJVM/VM/Src/flint_execution.cpp                         \
                    FlintJVM/VM/Src/flint_field_info.cpp                        \
                    FlintJVM/VM/Src/flint_fields_data.cpp                       \
                    FlintJVM/VM/Src/flint_load_file_error.cpp                   \
                    FlintJVM/VM/Src/flint_method_info.cpp                       \
                    FlintJVM/VM/Src/flint_object.cpp                            \
                    FlintJVM/VM/Src/flint_out_of_memory.cpp                     \
                    FlintJVM/VM/Src/flint_thread.cpp                            \
                    FlintJVM/VM/Src/flint_string.cpp                            \
                    FlintJVM/VM/Src/flint_throwable.cpp                         \
                    FlintJVM/VM/Src/flint.cpp                                   \
                    FlintJVM/Native/Src/flint_native_character_class.cpp        \
                    FlintJVM/Native/Src/flint_native_class_class.cpp            \
                    FlintJVM/Native/Src/flint_native_class.cpp                  \
                    FlintJVM/Native/Src/flint_native_double_class.cpp           \
                    FlintJVM/Native/Src/flint_native_float_class.cpp            \
                    FlintJVM/Native/Src/flint_native_math_class.cpp             \
                    FlintJVM/Native/Src/flint_native_object_class.cpp           \
                    FlintJVM/Native/Src/flint_native_thread_class.cpp           \
                    FlintJVM/Native/Src/flint_native_print_stream_class.cpp     \
                    FlintJVM/Native/Src/flint_native_string_class.cpp           \
                    FlintJVM/Native/Src/flint_native_system_class.cpp           \
                    User/Src/main.cpp                                           \
                    User/Src/windows_tcp_debugger.cpp                           \
                    User/Src/windows_system_api.cpp                             \
                    User/Src/windows_system_file_api.cpp                        \
                    User/Src/windows_system_thread_api.cpp

INCLUDES      	:=  FlintJVM/Native/Inc                                         \
                    FlintJVM/VM/Inc                                             \
                    User/Inc

OPT             :=  -g

CFLAGS          :=  -m32                                                        \
                    -std=gnu++11                                                \
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
	@rm -rf $(BUILD_DIR)
	@echo -e "$(GREEN)Clean complete$(RESET)"
