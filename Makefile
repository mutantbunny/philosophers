CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LIBFLAGS =
RM = rm -rf

MANDATORY_DIR = ./philo
NAME = ${MANDATORY_DIR}/philo
INC_DIR = ${MANDATORY_DIR}
INC_FILES = ${INC_DIR}/philo.h
SRC_DIR = ${MANDATORY_DIR}
SRC_FILES = ${append ${SRC_DIR}, philo.c}
OBJ_DIR = ${MANDATORY_DIR}/obj
OBJ_FILES = ${append ${OBJ_DIR}, ${notdir ${SRC_FILES:.c=.o}}}

all: ${NAME}

${OBJ_DIR}:
	mkdir -p ${OBJ_DIR}

${NAME}: ${OBJ_FILES}
	${CC} ${CFLAGS} ${OBJ_FILES} -o $@

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c ${OBJ_DIR} ${INC_FILES}
	${CC} ${CFLAGS} -I${INC_DIR} -c $< ${LIBFLAGS} -o $@

clean:
	${RM} OBJ_DIR

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
