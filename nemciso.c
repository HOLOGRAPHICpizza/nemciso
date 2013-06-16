#define EXIT_ERROR	1
#define EXIT_IO_ERROR	2
#define EXIT_BAD_USAGE	3

#define LEVEL_MAGIC_NUM 69

#include <stdio.h>
#include <stdlib.h>

//char *program; // program name

// made up level format
struct Level {
	char magicNum;
	int xSize, ySize, zSize;
	char *blocks;
};

// addressing scheme of Level.blocks
int positionAddr(int x, int y, int z, int xSize, int ySize) {
	return (z * xSize * ySize) + (y * xSize) + x;
}

struct Level *loadLevel(FILE *file) {
	struct *level = malloc(sizeof(struct Level));
	
	level->magic = getc(file);
	assert(magicNum == LEVEL_MAGIC_NUM);

	assert(fread(level->xSize, 3, 1, file) == 3 && level->zSize != EOF);
	
	int blocksSize = level->xSize * level->ySize * level->zSize;
	assert(blocksSize > 0);

	level->blocks = malloc(blocksSize);
	
	fread(level->blocks, 1, blocksSize, file); //TODO: error check
}

void freeLevel(struct Level *level) {
	assert(level != NULL);

	free(level->blocks);
	free(level);
}

int main(int argc, char *argv[]) {
	
	char *program = argv[0];
	
	// check args
	if(argc == 1) {
		fprintf(stderr, "%s: Must specify world to render.\n", program);
		exit(EXIT_BAD_USAGE);
	}
	
	char *filename = argv[1];
	FILE *file = fopen(filename, "r");
	if(level == NULL) {
		fprintf(stderr, "%s: Error opening %s for reading.\n", program, filename);
		exit(EXIT_IO_ERROR);
	}

	// ------------
	// Render World
	// ------------
	printf("%s: Rendering %s...\n", program, filename);
	
	struct Level *level = loadLevel(file);
	
	// cleanup
	freeLevel(level);
	fclose(file);	
	return 0;
}
