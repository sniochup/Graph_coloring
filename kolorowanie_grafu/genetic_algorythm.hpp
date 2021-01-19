#ifndef genetic_algoryth_hpp
#define genetic_algoryth_hpp
#include "helper_functions.hpp"

int **initial_population(int vertices, int range);
int **keep_the_best(int **current_pop, int *fitness_tab, int M, int ilosc);
int **keep_the_best_2tab(int **current_pop, int **offsprings, int *fitness_tab, int M, int ilosc);
int **mutation(int **tab, int pop_size, int mut, int range);
int *mutation1(int *tab, int range);
int *mutation2(int *tab, int range);
int *mutation3(int *tab, int range);
int *mutation4(int *tab, int range);
int *crossover(int *parent1, int *parent2);
int evaluate(int *tab);
int number_colors(int *tab, int vertices);
int *fitness(int **tab, int size);
int fitness_1(int *tab);
int number2_colors(int *tab, int vertices);

#endif