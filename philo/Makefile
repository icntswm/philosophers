.PHONY: all clean fclean re bonus

SRCS	=	main.c	\
			pars_and_init.c	\
			time.c	\
			life_process.c	\
			ft_atoi.c	\
			error.c	\
			check_death.c

OBJS	=	${SRCS:.c=.o}


NAME	=	philo
P_HEAD	=	philo.h

RM		=	rm -f
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g

.c.o:		${P_HEAD}
			${CC} ${CFLAGS} -c $< -o $@

${NAME}:	${OBJS}
			${CC} ${OBJS} -o ${NAME} -lpthread

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all
