# ********************************************************************* #
#  __   __  _______  ___   _  _______  _______  ___   ___      _______  #
# |  |_|  ||   _   ||   | | ||       ||       ||   | |   |    |       | #
# |       ||  |_|  ||   |_| ||    ___||    ___||   | |   |    |    ___| #
# |       ||       ||      _||   |___ |   |___ |   | |   |    |   |___  #
# |       ||       ||     |_ |    ___||    ___||   | |   |___ |    ___| #
# | ||_|| ||   _   ||    _  ||   |___ |   |    |   | |       ||   |___  #
# |_|   |_||__| |__||___| |_||_______||___|    |___| |_______||_______| #
#                                                                       #
# ********************************************************************* #


# ************************************************** #


NAME			= 	philo

CC				=	cc

CFLAGS			=	${SANITIZE} -pthread -Wall -Wextra -Werror -I includes/

#SANITIZE		=	-fsanitize=thread -g3

INCLUDES		=	includes/philo.h

SRCS_D			=	srcs/
				
OBJS_D			=	.obj/

SRCS			=	${SRCS_D}main.c \
					${SRCS_D}utils.c \
					${SRCS_D}lst_utils.c \
					${SRCS_D}errors.c \
					${SRCS_D}init.c \
					${SRCS_D}routine.c \
					${SRCS_D}check.c \
					${SRCS_D}forks.c \

OBJS			=	${patsubst ${SRCS_D}%.c, ${OBJS_D}%.o, ${SRCS}}

# ************************************************** #

all :				${NAME}

${NAME} :			${OBJS_D} ${OBJS} ${INCLUDES} Makefile
	${CC} ${CFLAGS} ${OBJS} -o $@

${OBJS_D}%.o :		${SRCS_D}%.c ${INCLUDES} Makefile
	${CC} ${CFLAGS} -c $< -o $@

${OBJS_D}:
	@mkdir -p $@

clean :
	rm -rf ${OBJS_D}

fclean :			clean
	rm -rf ${NAME}

re :				fclean all

# ************************************************** #

.PHONY :			all clean fclean re

# ************************************************** #