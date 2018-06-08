/*
** EPITECH PROJECT, 2017
** cpp_d0
** File description:
** Bsq
*/

#pragma once

namespace Wornite
{
	class Bsq {
	public:
		Bsq() = default;
		~Bsq() = default;

		typedef struct	s_vector
		{
			int		x;
			int		y;
		}		t_vector;

		typedef struct	s_response
		{
			t_vector	pos;
			unsigned int	size;
		}		t_response;

		typedef struct	s_map
		{
			char		*dots;
			unsigned int	row;
			unsigned int	col;
		}		t_map;

		void find_bsq(t_map *map, t_response *res);

	private:
		void test_squares(t_map *map, t_response *res, t_vector *cur);
		int test_square(t_map *map, t_vector *cur, int size, int n);
		int test_col(t_map *map, t_vector *cur, int size, int col);
		int test_row(t_map *map, t_vector *cur, int size, int row);


	};

# define OBS_CHAR		'o'

# define IDX(map, x, y)		(x + (y * (map->col + 1)))
# define DOTS(map, x, y)	(map->dots[IDX(map, x, y)])
}
