NAME			= miniRT

CC				= gcc
CFLAGS			= -Wall -Werror -Wextra
# -g -fsanitize=address

LIBS = ./library/LIBFT/libft.a
LIBV = ./library/Libft_vector/libvector.a
LIBMLX = ./library/mlx/libmlx.a
MLX = -Llibrary/mlx -lmlx -framework OpenGL -framework AppKit
# MLX = -Llibrary/mlx -framework OpenGL -framework AppKit

INCS_DIR		= 	-I ./library/LIBFT \
					-I ./library/mlx \
					-I ./library/Libft_vector \
					-I ./mlx_hook \
					-I ./print_info \
					-I ./scene \
					-I ./color \
					-I ./ray_cast \
					-I ./objects

SRCS_DIR		= 	./ \
					./ray_cast \
					./color \
					./print_info \
					./mlx_hook \
					./scene \
					./objects

SRCS			= 	main.c \
					\
					ray.c \
					light_source.c \
					reflection.c \
					diffuse_reflection.c \
					specular_reflection.c \
					\
					color.c \
					\
					print_scene.c \
					print_scene2.c \
					\
					mlx_event.c \
					mlx_mouse.c \
					mlx_mouse_wheel.c \
					mlx_keyboard_move.c \
					mlx_keyboard.c \
					mlx_part.c \
					\
					camera.c \
					light.c \
					parsing_utils.c \
					read_file.c \
					scene1.c \
					scene2.c \
					\
					cylinder.c \
					objs_base.c \
					sphere.c \
					plain.c \
					case_object.c \
					init_object.c \
					cone.c \
					object_ect.c


OBJS_DIR		= ./OBJS
OBJS			= $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))
vpath %.c $(SRCS_DIR)

RM				= rm -f

all: $(NAME)

$(NAME): $(OBJS) $(LIBS) $(LIBV) ${LIBMLX}
	$(CC) $(CFLAGS) $(MLX) -lm  $^ -o $@

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCS_DIR) -c $^ -o $@

$(OBJS_DIR):
	@mkdir -p $@

# libft
$(LIBS):
	@make -C ./library/LIBFT all
${LIBV} :
	@make -C ./library/Libft_vector all
${LIBMLX} :
	@make -C ./library/mlx all

# clean, fclean, re
clean :
	@make -C ./library/LIBFT clean
	@make -C ./library/Libft_vector clean
	$(RM) -r $(OBJS_DIR)

fclean : clean
	@make -C ./library/LIBFT fclean
	@make -C ./library/Libft_vector fclean
	${RM} ${NAME}

re: fclean all

.PHONY: all, $(NAME), clean, fclean, re