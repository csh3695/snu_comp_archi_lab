#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "maze.h"

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		fprintf(stderr, "Usage: %s [inputfile]\n", argv[0]);
		return -1;
	}

	FILE *fp = fopen(argv[1], "r");
	if(!fp)
	{
		fprintf(stderr, "Failed to open %s\n", argv[1]);
		return -1;
	}

	int width, height;
	fscanf(fp, "%d %d\n", &width, &height);

	if(width <= 0)
	{
		fprintf(stderr, "Width must be positive integer!");
		fclose(fp);
		return -1;
	}

	if(height <= 0)
	{
		fprintf(stderr, "Height must be positive integer!");
		fclose(fp);
		return -1;
	}


	//load maze
	long *maze = (long*)malloc(sizeof(long) * width * height);

	printf("Maze layout:\n");
	for(size_t i = 0 ; i < height ; i++)
	{
		for(size_t j = 0 ; j < width ; j++)
		{
			printf("%ld", (maze[i * width + j] = (getc(fp) == '1' ? 1 : 0)));
		}
		getc(fp);	//Remove return character ('\n')
		putchar('\n');
	}

	long ret = solve_maze(maze, width, height);

	if(ret < 0)
	{
		printf("This maze is not solvable\n");
	}
	else
	{
		printf("The shortest path length is: %ld\n", ret);
	}

	free(maze);
	fclose(fp);
	return 0;
}
