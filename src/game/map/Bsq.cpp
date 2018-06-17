/*
** EPITECH PROJECT, 2017
** indie
** File description:
** Bsq
*/

#include "Bsq.hpp"

int
Wornite::Bsq::test_row(t_map *map, t_vector *cur, int size, int row)
{
	int		index;
	int		limit;
	unsigned int	cmptd_row;

	limit = cur->x - 1;
	index = limit + size;
	cmptd_row = cur->y + row;
	if (cur->y + row >= (int) map->row)
		return (0);
	while (index != limit)
	{
		if (DOTS(map, index, cmptd_row) == OBS_CHAR)
			return (index);
		index -= 1;
	}
	return (-1);
}

int
Wornite::Bsq::test_col(t_map *map, t_vector *cur, int size, int col)
{
	int		index;
	int		limit;
	int	cmptd_col;

	limit = cur->y - 1;
	index = limit + size;
	cmptd_col = cur->x + col;
	if (cur->x + col >= (int) map->col)
		return (0);
	while (index != limit)
	{
		if (DOTS(map, cmptd_col, index) == OBS_CHAR)
			return (index);
		index -= 1;
	}
	return (-1);
}

int
Wornite::Bsq::test_square(t_map *map, t_vector *cur, int size, int n)
{
	int		index;
	int		obs_x;

	index = size - 1;
	if (n == 0)
	{
		while (index != -1)
		{
			if (test_col(map, cur, size, index) != -1)
				return (index);
			index -= 1;
		}
	}
	if (test_col(map, cur, size, size - 1) > -1)
		return (size - 1);
	if ((obs_x = test_row(map, cur, size, size - 1)) > -1)
		return (obs_x);
	return (-1);
}

void
Wornite::Bsq::test_squares(t_map *map, t_response *res, t_vector *cur)
{
	int		obs_x;
	unsigned int	n;

	n = 0;
	while (1)
	{
		if ((obs_x = test_square(map, cur, res->size + 1, n)) != -1)
		{
			cur->x += obs_x;
			break;
		}
		else
		{
			res->pos.x = cur->x;
			res->pos.y = cur->y;
			res->size += 1;
		}
		n += 1;
	}
}

void		Wornite::Bsq::find_bsq(t_map *map, t_response *res)
{
	t_vector	cur;

	cur.y = 0;
	res->pos.x = 0;
	res->pos.y = 0;
	res->size = 0;
	while (cur.y + res->size < map->row)
	{
		cur.x = 0;
		while (cur.x + res->size < map->col)
		{
			test_squares(map, res, &cur);
			cur.x += 1;
		}
		cur.y += 1;
	}
}