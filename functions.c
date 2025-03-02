/* LUNGU Mihai-Teodor - 313CD */

#include "headers.h"

Image *readppm(FILE *input)
{
    char format[3];
    char aux;
    fscanf(input, "%s", format);

    Image *image = malloc(sizeof(Image));
    fscanf(input, "%u", &image->size);
    //fread(&aux, 1, 1, input);
    fscanf(input, "%u", &image->size);
    //fread(&aux, 1, 1, input);

    unsigned int channel;
    fscanf(input, "%u", &channel);
    fread(&aux, 1, 1, input);

    image->pixels = malloc(sizeof(Pixel*) * image->size);
    for(int i = 0; i < image->size; i++){
        image->pixels[i] = malloc(sizeof(Pixel) * image->size);
    }

    for(int i = 0; i < image->size; i++){
        for(int j = 0; j < image->size; j++){
            fread(&image->pixels[i][j], sizeof(Pixel), 1, input);
        }
    }

    return image;
}

unsigned long long mean(Image *image, unsigned long long x, unsigned long long y, unsigned long long size)
{
    unsigned long long red = 0, green = 0, blue = 0;

    for(int i = x; i < x + size; i++){
        for(int j = y; j < y + size; j++){
            red += image->pixels[i][j].r;
            green += image->pixels[i][j].g;
            blue += image->pixels[i][j].b;
        }
    }
    red = red / (size * size);
    green = green / (size * size);
    blue = blue / (size * size);

    unsigned long long mean = 0;

    for(int i = x; i < x + size; i++){
        for(int j = y; j < y + size; j++){
            unsigned long long red_mean = red - image->pixels[i][j].r;
            unsigned long long green_mean = green - image->pixels[i][j].g;
            unsigned long long blue_mean = blue - image->pixels[i][j].b;
            mean = mean + red_mean * red_mean + green_mean * green_mean + blue_mean * blue_mean;
        }
    }
    mean = mean / (3 * size * size);

    return mean;
}

Tree compression(Image *image, Tree tree, unsigned long long x, unsigned long long y, unsigned long long size, unsigned long long prag)
{
    if(size == 0)
        return NULL;

    unsigned long long factor = 0;
    factor = mean(image, x, y, size);

    if(factor <= prag){
        tree = malloc(sizeof(TreeNode));
        tree->type = 1;
        for(int i = 0; i < 4; i++){
            tree->children[i] = 0;
        }

        unsigned long long red = 0, green = 0, blue = 0;

        for(int i = x; i < x + size; i++){
            for(int j = y; j < y + size; j++){
                red += image->pixels[i][j].r;
                green += image->pixels[i][j].g;
                blue += image->pixels[i][j].b;
            }
        }

        red = red / (size * size);
        green = green / (size * size);
        blue = blue / (size * size);

        tree->pixel.r = red;
        tree->pixel.g = green;
        tree->pixel.b = blue;
        
        return tree;
    }

    tree = malloc(sizeof(TreeNode));

    tree->children[0] = compression(image, tree, x, y, size / 2, prag);
    tree->children[1] = compression(image, tree, x, y + size / 2, size / 2, prag);
    tree->children[2] = compression(image, tree, x + size / 2, y + size / 2, size / 2, prag);
    tree->children[3] = compression(image, tree, x + size / 2, y, size / 2, prag);
    tree->type = 0;

    return tree;
}

unsigned long long height(Tree tree)
{
    if(tree == NULL)
        return 0;
    
    unsigned long long height0, height1, height2, height3;

    height0 = height(tree->children[0]) + 1;
    height1 = height(tree->children[1]) + 1;
    height2 = height(tree->children[2]) + 1;
    height3 = height(tree->children[3]) + 1;

    unsigned long long max_height = height0;

    if(max_height < height1)
        max_height = height1;
    if(max_height < height2)
        max_height = height2;
    if(max_height < height3)
        max_height = height3;

    return max_height;     
}

unsigned long long leaf_number(Tree tree)
{
    if(tree == NULL)
        return 0;

    if(tree->children[0] == NULL)
        return 1;
    
    unsigned long long leaves0, leaves1, leaves2, leaves3;

    leaves0 = leaf_number(tree->children[0]);
    leaves1 = leaf_number(tree->children[1]);
    leaves2 = leaf_number(tree->children[2]);
    leaves3 = leaf_number(tree->children[3]);

    return leaves0 + leaves1 + leaves2 + leaves3;
}

unsigned long long largest(Image *image, unsigned long long x, unsigned long long y, unsigned long long size, unsigned long long prag)
{
    if(size == 0)
        return 0;

    unsigned long long factor = 0;
    factor = mean(image, x, y, size);

    if(factor <= prag){
        return size;
    }

    unsigned long long block0, block1, block2, block3;

    block0 = largest(image, x, y, size / 2, prag);
    block1 = largest(image, x, y + size / 2, size / 2, prag);
    block2 = largest(image, x + size / 2, y + size / 2, size / 2, prag);
    block3 = largest(image, x + size / 2, y, size / 2, prag);

    unsigned long long max_block = block0;

    if(max_block < block0)
        max_block = block1;
    if(max_block < block2)
        max_block = block2;
    if(max_block < block3)
        max_block = block3;

    return max_block; 
}
