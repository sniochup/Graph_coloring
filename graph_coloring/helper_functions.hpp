#ifndef helper_functions_hpp
#define helper_functions_hpp
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <fstream>
#include <cstring>

using namespace std;

extern int vertices;
extern int **matrix;

int most_used_color(int *tab, int i, int range);
int **extend_table_2d(int **tab, int rows, int cols, int plus);
int brute_coloring(int **matrix);
int *brute_coloring1(int **matrix);

int **generator();
int **read_file(string path);
int **create_matrix(int vertices);
bool check_repeat(int **tab, int i, int j);
void DFS(int v, bool *visited);
void graph_generator(int counter, int edges);
int max(int *tab, int size);
void print_matrix_2d(int **tab, int rows, int cols);
int start();
int min(int *tab, int size);

#endif