#include "genetic_algorythm.hpp"
#include <chrono>

// Global variables
int vertices; // number of vertices
int **matrix; // adjacency matrix

int main(){

    srand(time(NULL));
    double time_total = 0;
    chrono::steady_clock::time_point Start;

    // Getting or creating an instance
    int selected_graph = start();
    // print_matrix_2d(matrix, vertices, vertices);
    
    // Brute force
    int range = brute_coloring(matrix);

    int M;  //Population size
    int NG; //Number of generation

    if (selected_graph == 1) {
        range = 8;
        M = 200;
        NG = 15000;
    }
    else if (selected_graph == 2) {
        range = 8;
        M = 500;
        NG = 10000;
    }
    else if (selected_graph == 3) {
        range = 155;
        M = 10;
        NG = 60000;
    }
    else if (selected_graph == 4) {
        range = 85;
        M = 5;
        NG = 50000;
    }
    else if (selected_graph == 5) {
        range = 11;
        M = 15;
        NG = 20000;
    }
    else {
        // range = 8;
        M = 500;
        NG = 8000;
    }

    // Genetic algorithm
    // int M; // = 1000;        // Population size
    // int NG; // = 5000;       // Number of generation
    int generation = 1;         // Current generation
    int N0 = M;                 // Number of offsprings
    int mutation_chance = 80;   // Probability of mutation (1-100)
    int initial_pop_size = 20000;

    int **current_pop = initial_population(initial_pop_size, range);

    int *chromosom_fitness = new int[initial_pop_size];
    chromosom_fitness = fitness(current_pop, initial_pop_size);
    
    current_pop = keep_the_best(current_pop, chromosom_fitness, initial_pop_size, M);

    int chosen_chromosome, chosen_chromosome_evaluate = 100;
    Start = chrono::steady_clock::now();

    while(generation <= NG && chosen_chromosome_evaluate!=0 /*&& time_total<240*/) {
        
        int **offsprings = new int*[N0];
        for (int i = 0; i < N0; i++)
            offsprings[i] = new int[vertices];

        for (int i = 0; i< N0; i++){
            int parent1 = i%M;
            int parent2;
            do {
                parent2 = rand()%M;
            }while(parent1==parent2);
            offsprings[i] = crossover(current_pop[parent1], current_pop[parent2]);
        }
        
        offsprings = mutation(offsprings, N0, mutation_chance, range);

        chromosom_fitness = new int[M+N0];
        for(int i = 0; i<M; i++){
            chromosom_fitness[i] = fitness_1(current_pop[i]);
            // cout << chromosom_fitness[i] << " ";
        }
        for (int i = 0, j = M; i < N0, j < M + N0; i++, j++){
            chromosom_fitness[j] = fitness_1(offsprings[i]);
            // cout << chromosom_fitness[j] << " ";
        }

        current_pop = keep_the_best_2tab(current_pop, offsprings, chromosom_fitness, M+N0, M);
        //  print_matrix_2d(current_pop, M, vertices);

        int min_number_of_color = vertices;
        for (int i=0; i<M; i++) {
            int temp = number_colors(current_pop[i], vertices);
            if (temp < min_number_of_color) {
                min_number_of_color = temp;
                chosen_chromosome_evaluate = evaluate(current_pop[i]);
                chosen_chromosome = i;
            }
        }
        cout << endl;
        cout << "Generation: " << generation << "; Min number of colors: " << min_number_of_color << "; Conflict: " << chosen_chromosome_evaluate << endl;

        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        time_total =chrono::duration_cast<chrono::duration<double>>(end - Start).count();

        generation++;
    }
    //  print_matrix_2d(current_pop, M, vertices);

    cout << endl;
    for (int i = 0; i < vertices; i++){
        cout << "Vertex: " << i+1 << " - Color: " << current_pop[chosen_chromosome][i] << endl;
    }
    
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    time_total =chrono::duration_cast<chrono::duration<double>>(end - Start).count();
    cout << "Time: " << time_total << " s" << endl;

    cout << "\nPress any key to close"; getch();
}