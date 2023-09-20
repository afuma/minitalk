CC = cc

RM = rm -f
AR = ar
ARFLAGS = crs

# /* ~~~~~~ SOURCES ~~~~~~ */
SRCS_DIR = srcs/
UTILS_DIR = utils/

SRCS_CLIENT = client.c
SRCS_SERVER = serveur.c
SRCS_UTILS = ft_itoa.c \
		ft_atoi.c \
		ft_utils.c

NAME_SERVER = server
NAME_CLIENT = client

CLIENT = $(addprefix $(SRCS_DIR), $(SRCS_CLIENT))
SERVER = $(addprefix $(SRCS_DIR), $(SRCS_SERVER))
UTILS = $(addprefix $(UTILS_DIR), $(SRCS_UTILS))
OBJS_SERVER = ${SERVER:.c=.o}
OBJS_CLIENT = ${CLIENT:.c=.o}
OBJS_UTILS = ${UTILS:.c=.o}

# /* ~~~~~~~ COMPILING INFO ~~~~~~~ */
# CC = clang
CFLAGS = -Wall -Werror -Wextra
IFLAGS:= -I ./includes

all :		${NAME_SERVER} ${NAME_CLIENT}
		clear

$(NAME_SERVER): $(OBJS_SERVER) $(OBJS_UTILS)
	${CC} ${CFLAGS} $(IFLAGS) ${OBJS_SERVER} $(OBJS_UTILS) -o ${NAME_SERVER}

$(NAME_CLIENT): $(OBJS_CLIENT) $(OBJS_UTILS)
	${CC} ${CFLAGS} $(IFLAGS) ${OBJS_CLIENT} $(OBJS_UTILS) -o ${NAME_CLIENT}

clean:
		${RM} ${OBJS_CLIENT} ${OBJS_SERVER} $(OBJS_UTILS)

fclean: clean
		${RM} ${NAME_CLIENT} ${NAME_SERVER}

re: 	fclean all

.PHONY: all clean fclean re