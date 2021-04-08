#include "genetic_algorythm.hpp"

int **initial_population(int m, int range) {
    int **chromosom = new int*[m]; // *** vertices -> m
    for (int i = 0; i < m; i++){
        chromosom[i] = new int[vertices]; // *** m -> vertices
    }
    for (int i = 0; i < m; i++){ // m -> vertices
        for (int j = 0; j < vertices; j++){
            chromosom[i][j] = rand()%range + 1;
        }
    }
    return chromosom;
}

int *crossover(int *parent1, int *parent2) {
    int crosspoint = rand()%(vertices-1)+1;
    // cout << " " << crosspoint;
    int *child = new int [vertices];
    for(int i = 0; i < crosspoint; i++)
        child[i] = parent1[i];
    for(int i = crosspoint; i < vertices; i++)
        child[i] = parent2[i];
    return child;
}

// mutations
int **mutation(int **tab, int pop_size, int mut, int range) {
    int it1 = 10;
    bool shift = true;
    for (int i = 0; i < pop_size; i++) {
        if (rand() % 100 < mut) {
            int temp = evaluate(tab[i]);
            if (it1 == 10){
                tab[i] = mutation4(tab[i], range);
                it1 = 0;
            }
            else if (temp > 50 || shift){
                tab[i] = mutation1(tab[i], range);
                shift = false;
                it1++;
            }
            else if (temp < 50 && temp > 0) {
                tab[i] = mutation2(tab[i], range);
                shift = true;
                it1++;
            }
            else
                tab[i] = mutation4(tab[i], range);

        }
    }
    return tab;
}

// valid colors
int *mutation1(int *tab, int range) {
    for (int j = 0; j < vertices - 1; j++)
        for (int k = j + 1; k < vertices; k++)
            if (matrix[j][k] && tab[j] == tab[k]){
                int most_j = most_used_color(tab, j, range);
                int most_k = most_used_color(tab, k, range);
                (most_j < most_k) ? tab[j] = most_j : tab[k] = most_k;
                return tab;
            }
    return tab;                
}

// random colors
int *mutation2(int *tab, int range) {
    for (int j = 0; j < vertices - 1; j++)
        for (int k = j + 1; k < vertices; k++)
            if (matrix[j][k] && tab[j] == tab[k]){
                tab[k] = rand() % range + 1;
            }
           
    return tab;
}

// random colors
int *mutation3(int *tab, int range) {
    int m = max(tab, vertices);
    int color;
    do {
        color = rand() % range + 1;
    } while (color > m);
    tab[rand() % vertices] = color;
    return tab;
}

int *mutation4(int *tab, int range) {
    tab[rand() % vertices] = rand() % range + 1;
    return tab;
}


// Counting the number of conflict in the population
int evaluate(int *tab){
    int conflict = 0;
    for(int i = 1; i < vertices; i++){
        for(int j = 0; j < i; j++) {
            if (matrix[i][j] && (tab[i] == tab[j])){
                conflict++;
            }
        }
    }
    return conflict;
}

int **keep_the_best(int **current_pop, int *fitness_tab, int M, int quantity) {
    int counter = 0;
    // int max_ft = max(fitness_tab, M);
    int min_ft = min(fitness_tab, M);
    int **tab = new int*[quantity]; 
    while(counter < quantity) {
        for(int i = 0; i < M; i++) {
            if (fitness_tab[i] == min_ft && counter < quantity) {
                tab[counter] = current_pop[i];
                counter++;
            }
        }
        min_ft++;
    }
    return tab;
}

int **keep_the_best_2tab(int **current_pop, int **offsprings, int *fitness_tab, int M, int quantity) {
    int counter = 0;
    //int max_ft = max(fitness_tab, M);
    int min_ft = min(fitness_tab, M);

    int **tab = new int*[quantity]; 
    while(counter < quantity) {
        for(int i = M-1; i >= 0; i--) {
            if (fitness_tab[i] == min_ft && counter < quantity) {
                if (i<quantity){
                    tab[counter] = current_pop[i];
                    counter++;
                }
                else {
                    tab[counter] = offsprings[i-quantity];
                    counter++;
                }
            }
        }
        min_ft++;
    }
    return tab;
}

int number_colors(int *tab, int vertices){
    int *temp = new int [vertices];
    int number_of_colors = 0;
    for (int i = 0; i<vertices; i++) {
        temp[i] = 0;
    }
    for (int i =0; i<vertices; i++) {
        temp[tab[i]-1]++;
    }
    for (int i = 0; i<vertices; i++) {
        
        if(temp[i] > 0) number_of_colors++;
    }
    return number_of_colors;
}

int *fitness(int **tab, int size){
    int *chromosome_fitness = new int[size];
    for(int i = 0; i < size; i++) {
        chromosome_fitness[i] = fitness_1(tab[i]);
    }
    return chromosome_fitness;
}

int fitness_1(int *tab){
    int chromosome_fitness;
    //int y = 6*evaluate(tab,matrix);
    // chromosome_fitness = y/number2_colors(tab, vertices);
    chromosome_fitness = number_colors(tab, vertices);
    // chromosome_fitness += number2_colors(tab, vertices);
    chromosome_fitness += evaluate(tab);
    // if (temp>200) chromosome_fitness += number2_colors(tab, vertices);

    // if (temp == 1) chromosome_fitness += 2;
    // else  chromosome_fitness += temp;
    
    return chromosome_fitness;
}

int number2_colors(int *tab, int vertices){
    int *temp = new int [vertices];
    int number_of_colors = 0;
    for (int i =0; i<vertices; i++) {
        temp[i] = 0;
    }
    for (int i =0; i<vertices; i++) {
        temp[tab[i]-1]++;
    }
    for (int i = 0; i<vertices; i++) {
        if(temp[i]==1) number_of_colors+=3;
        else if (temp[i]==2) number_of_colors+=2;
        else if (temp[i]==3) number_of_colors+=1;
        
    }
    return number_of_colors;
}