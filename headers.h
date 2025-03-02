/* LUNGU Mihai-Teodor - 313CD */

#include <stdio.h>
#include <stdlib.h>

typedef struct pixel {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Pixel;

typedef struct node {
    Pixel pixel;
    struct node *children[4];
    unsigned char type;
} TreeNode, *Tree;

typedef struct image {
    unsigned int size;
    Pixel **pixels;
} Image;

Image *readppm(FILE *input);
Tree compression(Image *image, Tree tree, unsigned long long x, unsigned long long y, unsigned long long size, unsigned long long prag);
unsigned long long mean(Image *image, unsigned long long x, unsigned long long y, unsigned long long size);
unsigned long long height(Tree tree);
unsigned long long leaf_number(Tree tree);
unsigned long long largest(Image *image, unsigned long long x, unsigned long long y, unsigned long long size, unsigned long long prag);
