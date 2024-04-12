


SRC_DIR = ./src
OBJ_DIR = ./obj
BIN_DIR = ./bin
UTL_DIR = ./src/util
INC_DIR = \
		./src \
		-I ./include \

		
GCCFLAGS += \
	-g \
	-fsanitize=address \


OBJ_SRC += \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/parse.c \
	$(SRC_DIR)/opcode.c \
	$(SRC_DIR)/rform.c \
	$(SRC_DIR)/iform.c \
	$(SRC_DIR)/jform.c \
	$(SRC_DIR)/vmemory.c \
	$(SRC_DIR)/label.c \
	$(SRC_DIR)/util.c \
	

TARGET_OBJ =\
    $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(OBJ_SRC)))

all : runfile

runfile: $(TARGET_OBJ)
	@mkdir -p $(BIN_DIR)
	gcc -o $(BIN_DIR)/$@ $^ -I$(INC_DIR) $(GCCFLAGS)
	ln -sf $(BIN_DIR)/$@ ./runfile

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	gcc -c $< -o $@ -I$(INC_DIR) $(GCCFLAGS)


.c.o:
	gcc -c $< -o $@ -I$(INC_DIR)

-include $(OBJS:.o=.d)

clean:
	@rm -vf $(BIN_DIR)/*
	@rm -vf $(OBJ_DIR)/*.o
	@rm -vf $(SRC_DIR)/*.o
	@rm -vf $(UTL_DIR)/*.o