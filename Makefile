CC		= g++

NAME	= test

SRC_DIR	= ./src/

SCIPLOT_DIR = ./libraries/sciplot/sciplot/

INC_DIR = ./include

OBJ_DIR	= ./obj/

SRCS	= $(SRC_DIR)main.cpp $(SRC_DIR)applicationStart.cpp $(SRC_DIR)convert.cpp $(SRC_DIR)inputData.cpp $(SRC_DIR)readFile.cpp	\
		  $(SRC_DIR)filters.cpp $(SRC_DIR)calcProbabilityCharact.cpp $(SRC_DIR)math.cpp $(SRC_DIR)draw.cpp $(SRC_DIR)ahrs.cpp		\
		  $(SRC_DIR)gravitationalAccelerationCalc.cpp  $(SRC_DIR)estimatePositionWGS.cpp $(SRC_DIR)coordinateTransform.cpp			\
		  $(SRC_DIR)rotationMatrix.cpp $(SRC_DIR)initialExhibition.cpp $(SRC_DIR)readConfigFile.cpp
 
OBJS	= $(patsubst $(SRC_DIR)%.cpp, $(OBJ_DIR)%.o, $(SRCS))

CFLAGS	= -g#-Wall -Wextra -Werror 

$(OBJ_DIR)%.o:	$(SRC_DIR)%.cpp
	$(CC) $(CFLAGS) -c $< -I $(SCIPLOT_DIR) -I $(INC_DIR) -o $@ -std=c++17	

all:	$(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME):	$(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -I $(SCIPLOT_DIR) -I $(INC_DIR) -o $(NAME) -std=c++17

clean:
	rm -rf $(OBJS)
	rm -rf $(OBJ_DIR)

fclean:	clean
	rm -rf $(NAME)

re:	fclean all