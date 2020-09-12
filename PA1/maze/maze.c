#include "maze.h"
#include <stdio.h>

#define MAX_DEPTH 20

#define T_UP 0
#define T_LEFT 1
#define T_RIGHT 2
#define T_DOWN 3


static const long *g_maze;
static long g_width;
static long g_height;

long traverse(const long x_pos, const long y_pos, const long depth, const long prev_trav)
{
	
	if(depth >= MAX_DEPTH)
	{
		return -1;
	}

	if(x_pos < 0 || y_pos < 0)
	{
		return -1;
	}

	if(x_pos >= g_width || y_pos >= g_height)
	{
		return -1;
	}

	//Dead end
	if(g_maze[y_pos * g_width + x_pos])
	{
		return -1;
	}

	//Success
	if(x_pos == g_width - 1 && y_pos == g_height - 1)
	{
		return depth;
	}

	long min = -1;

	//Traverse up
	do
	{
		if(prev_trav == T_DOWN)
		{
			break;
		}

		min = traverse(x_pos, y_pos - 1, depth + 1, T_UP);
	}
	while(0);

	//Traverse left
	do
	{
		if(prev_trav == T_RIGHT)
		{
			break;
		}

		long result = traverse(x_pos - 1, y_pos, depth + 1, T_LEFT);
		if(result < 0)
		{
			break;
		}

		if(min < 0)
		{
			min = result;
			break;
		}

		if(min > result)
		{
			min = result;
		}
	}
	while(0);
	
	//Traverse right
	do
	{
		if(prev_trav == T_LEFT)
		{
			break;
		}

		long result = traverse(x_pos + 1, y_pos, depth + 1, T_RIGHT);
		if(result < 0)
		{
			break;
		}

		if(min < 0)
		{
			min = result;
			break;
		}

		if(min > result)
		{
			min = result;
		}
	}
	while(0);

	//Traverse down
	do
	{
		if(prev_trav == T_UP)
		{
			break;
		}

		long result = traverse(x_pos, y_pos + 1, depth + 1, T_DOWN);
		if(result < 0)
		{
			break;
		}

		if(min < 0)
		{
			min = result;
			break;
		}

		if(min > result)
		{
			min = result;
		}
	}
	while(0);

	
	return min;
}

long solve_maze(const long *maze, const long width, const long height)
{
	//Starting point: 0, 0
	//End point: width - 1, height - 1
	
	g_maze = maze;
	g_width = width;
	g_height = height;
	
	//Return shortest path length if solvable
	//Else, return -1;
	//Works too if you put T_DOWN instead of T_RIGHT
	return traverse(0, 0, 0, T_RIGHT);
}
