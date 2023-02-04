NAME			= miniRT

CC				= gcc
CFLAGS			=  -Wall -Werror -Wextra  -O3 -mavx2
# -g -fsanitize=address  -Wall -Werror -Wextra
#-mavx512f -mavx512dq -mavx512bw -mavx512vbmi -mavx512vbmi2 -mavx512vl
LIBS = ./library/LIBFT/libft.a
LIBV = ./library/Libft_vector/libvector.a
LIBMLX = ./library/mlx/libmlx.a
MLX = -Llibrary/mlx -lmlx -framework OpenGL -framework AppKit

INCS_DIR		= 	-I ./library/LIBFT \
					-I ./library/mlx \
					-I ./library/Libft_vector \
					-I ./mlx_manager \
					-I ./print_info \
					-I ./scene \
					-I ./color \
					-I ./ray_cast \
					-I ./timer \
					-I ./quadrics \
					-I ./scene_editer \
					-I ./debug_msgs \
					-I .

SRCS_DIR		= 	./ \
					./ray_cast \
					./color \
					./print_info \
					./mlx_manager \
					./scene \
					./timer \
					./quadrics \
					./scene_editer \
					./debug_msgs 


SRCS			= 	main.c \
					\
					ray.c \
					light_source.c \
					reflection.c \
					ray_thread.c \
					specular_diffuse.c \
					\
					color.c \
					color_disruption.c \
					get_texture_color.c \
					\
					print_scene.c \
					print_scene2.c \
					\
					mlx_event.c \
					mlx_mouse.c \
					mlx_mouse_wheel.c \
					mlx_keyboard_move.c \
					mlx_keyboard.c \
					mlx_manager.c \
					mlx_messages.c \
					\
					camera.c \
					light.c \
					parsing_utils.c \
					read_file.c \
					scene1.c \
					scene2.c \
					set_bounding_sphere.c \
					\
					timer.c \
					\
					quadrics.c \
					quadrics_util.c \
					quadrics_helper.c \
					quadrics_equations.c \
					\
					scene_editer.c \
					\
					debug_quadrics.c \
					debug_raycast.c \
					debug_reflection.c 

OBJS_DIR		= ./OBJS
OBJS			= $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))
vpath %.c $(SRCS_DIR)

RM				= rm -f

all: $(NAME)

$(NAME): $(OBJS) $(LIBS) $(LIBV) $(LIBMLX)
	$(CC) $(CFLAGS) $(MLX) -lm  $^ -o $@

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCS_DIR) -c $^ -o $@

$(OBJS_DIR):
	@mkdir -p $@

# libft
$(LIBS):
	$(MAKE) -C ./library/LIBFT all
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