######################### source files ###############################

SRCS			= 	main.c \
					ft_split.c \
					ft_move_plr.c \
					ft_cast_rays.c \
					ft_mini_map.c \
					ft_rendering.c \
					ft_intersection.c \
					ft_face_list.c \
					ft_check_next.c \
					ft_door_ctl.c \
					ft_gun_sprite.c \
					cube_utils.c \
					ft_mouse.c \
					ft_texture.c


######################### object files ###############################

OBJS			= $(SRCS:%c=%o)

########################### variables #################################

NAME			= cube

# LINK			= -framework Cocoa -framework OpenGL -framework IOKit

LINK			= -lmlx42 -lglfw -lm

# LIBS			= MLX42/libmlx42.a -lglfw3


############################# rules ###################################

all				: $(NAME)

o%				: %c cube.h
	gcc -c $< -o $@ -O3 -ffast-math

$(NAME)			: $(OBJS)
	gcc $(OBJS)  -o $(NAME) $(LINK) $(LIBS)  -O3 -ffast-math
clean			:
	rm -rf *o

fclean			: clean
	rm -rf $(NAME)

re				: fclean all