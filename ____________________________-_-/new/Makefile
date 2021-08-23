.PHONY: all clean fclean re bonus

SRCS	=	alg/first_part_algbig/first_part.c	\
			alg/first_part_algbig/utils_for_first_part.c	\
			alg/second_part_algbig/second_part.c	\
			alg/second_part_algbig/utils_for_second_part.c	\
			alg/utils_func/check_swap.c	\
			alg/utils_func/stack_counter.c	\
			alg/utils_func/delete_elem.c	\
			alg/utils_func/utils_func_1.c	\
			alg/utils_func/utils_func_2.c	\
			alg/alg23.c	\
			alg/alg45.c	\
			alg/algbig.c	\
			alg/selection_algoritm.c	\
			commands/command_pp.c	\
			commands/command_rr.c	\
			commands/command_rrr.c	\
			commands/command_ss.c	\
			errors/error_func.c	\
			errors/error_search.c	\
			libft/ft_atoi.c	\
			libft/ft_strdup.c	\
			libft/ft_strjoin.c	\
			libft/ft_strlen.c	\
			libft/ft_substr.c	\
			others/fill_list.c	\
			others/ft_free.c	\
			others/print_sortlist.c	\
			others/save_str.c	\
			others/sort_position.c	\
			push_swap.c

B_SRCS	=	alg/utils_func/stack_counter.c	\
			alg/utils_func/delete_elem.c	\
			commands/command_pp_bonus.c	\
			commands/command_rr_bonus.c	\
			commands/command_rrr_bonus.c	\
			commands/command_ss_bonus.c	\
			errors/error_func.c	\
			errors/error_search.c	\
			libft/ft_atoi.c	\
			others/fill_list.c	\
			others/ft_free.c	\
			bonus_checker/command_exec.c	\
			bonus_checker/checker.c	

OBJS	=	${SRCS:.c=.o}
B_OBJS	=	${B_SRCS:.c=.o}


NAME	=	push_swap
B_NAME	=	checker
P_HEAD	=	push_swap.h

RM		=	rm -f
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g

.c.o:
			${CC} ${CFLAGS} -c $< -I ${P_HEAD} -o $@

${NAME}:	${OBJS}
			${CC} ${OBJS} -o ${NAME}

all:		${NAME}

clean:
			${RM} ${OBJS} ${B_OBJS}

fclean:		clean
			${RM} ${NAME} ${B_NAME}

re:			fclean all

bonus:		${B_OBJS}
			${CC} ${B_OBJS} -o ${B_NAME}
