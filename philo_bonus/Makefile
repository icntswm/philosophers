.PHONY: all clean fclean re bonus

SRCS	=	main.c	\
			pars_and_init.c	\
			time.c	\
			life_process.c	\
			ft_atoi.c	\
			ft_itoa.c	\
			error.c	\
			threads_death.c

OBJS	=	${SRCS:.c=.o}


NAME	=	philo_bonus
P_HEAD	=	philo_bonus.h

RM		=	rm -f
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g

.c.o:
			${CC} ${CFLAGS} -c $< -I ${P_HEAD} -o $@

${NAME}:	${OBJS}
			${CC} ${OBJS} -o ${NAME} -lpthread

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all
