#include "helper_functions.hpp"

int most_used_color(int *tab, int i, int range){
    int *tmp = new int[vertices];
    for (int j = 0; j < vertices; j++)
        tmp[j] = 0;
    for (int j = 0; j < vertices; j++)
        tmp[tab[j]-1]++;
    for (int j = 0; j < vertices; j++)
        if (matrix[i][j])
            tmp[tab[j]-1] = 0;
    int id = min(tmp, vertices);
    if(id!=0){
        for (int j = 0; j < vertices; j++)
            if (tmp[j] == id)
                return j+1;
    }
    return rand()%range+1;
}

int brute_coloring(int **matrix){
    int *colors = new int[vertices];
    colors[0] = 1;
    int color;
    bool temp;

    for(int i = 1; i < vertices; i++){
        color = 1;
        temp = true;

        while (temp) {
            temp = false;

            for(int j = 0; j < i; j++){
                if (matrix[i][j] == 1){
                    if (colors[j] == color) {
                        temp = true;
                    }
                }
            }
            if (temp){
                color += 1;
            }
        }
        colors[i] = color;
    }

    //PRINT COLORS
    for (int i = 0; i < vertices; i++){
        cout << "Vertex: " << i+1 << " - Color: " << colors[i] << endl;
    }
    cout << endl;
    int max_c = max(colors, vertices);
    cout << "Number of used colors (brute force): " << max_c << endl;

    return max_c;
}

int *brute_coloring1(int **matrix){
    int *colors = new int[vertices];
    colors[0] = 1;
    int color;
    bool temp;

    for(int i = 1; i < vertices; i++){
        color = 1;
        temp = true;

        while (temp) {
            temp = false;

            for(int j = 0; j < i; j++){
                if (matrix[i][j] == 1){
                    if (colors[j] == color) {
                        temp = true;
                    }
                }
            }
            if (temp){
                color += 1;
            }
        }
        colors[i] = color;
    }

    return colors;
}

int **create_matrix(int vertices){
    int **tab = new int*[vertices];
    for (int i = 0; i < vertices; i++){
        tab[i] = new int[vertices];
    }

    for (int i = 0; i < vertices; i++){
        for (int j = 0; j < vertices; j++){
            tab[i][j] = 0;
        }
    }
    return tab;
}

int **extend_table_2d(int **tab, int rows, int cols, int plus){
    int **tmp = new int*[rows+plus];
    for (int i = 0; i <= rows; i++)
        tmp[i] = new int[cols];
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            tmp[i][j] = tab[i][j];
    
    return tab;    
}

int **generator() {
    // GRAPH GENERATOR
    cout << "Number of vertices: "; cin >> vertices;
    matrix = create_matrix(vertices);
    cout << "Vert: " << vertices << endl;

    int density = 30;                                       // density
    int edges = vertices * (vertices - 1) * density / 200;  // number of edges
    int counter = 0;                                        // edge iterator

    bool *visited = new bool[vertices];
    for (int i = 0; i < vertices; i++) visited[i] = false;

    graph_generator(counter, edges);
    DFS(0, visited);

    // GRAPH COHERENCE (uspójnianie grafu)
    for (int i = 0; i < vertices; i++){
        if (!visited[i]) {
            if (i > 0) {
                matrix[i-1][i] = 1;
                matrix[i][i-1] = 1;
                counter++;
            }
            else {
                matrix[vertices-1][0] = 1;
                matrix[0][vertices-1] = 1;
                counter++;
            }
        }
        for (int i = 0; i < vertices; i++) visited[i] = false;
        DFS(i, visited);
    }

    // WRITE TO FILE
    fstream file;
    file.open("instances/file.txt", ios::out);
    file << vertices << endl;
    for (int i = 0; i < vertices; i++){
        for (int j = i; j < vertices; j++){
            if (matrix[i][j]) file << i+1 << " " << j+1 << endl;                    
        }                
    }

    file.close();
    return matrix;
}

int **read_file(string path) {
    fstream file;
    int begin, finish;

    file.open(path, ios::in);
    file >> vertices;
    int **matrix = create_matrix(vertices);
    while (file >> begin){
        file >> finish;
        matrix[begin-1][finish-1] = 1;
        matrix[finish-1][begin-1] = 1;
    }
    file.close();

    return matrix;
}

bool check_repeat(int **tab, int i, int j){
    if (tab[i][j]) return true;
    return false;
}

void DFS(int v, bool *visited){
    visited[v] = true;

    for(int i = 0; i < vertices; i++){
        if((!visited[i] && matrix[v][i] == 1)) DFS(i, visited);
    }
}

void graph_generator(int counter, int edges){
    int start, end;

    while (counter < edges){
        start = rand() % (vertices - 1) + 1;
        end = rand() % (vertices - start) + (start + 1);
        if (check_repeat(matrix, start - 1, end - 1)) continue;

        matrix[start - 1][end - 1] = 1;
        matrix[end - 1][start - 1] = 1;
        counter++;
    }
}

int max(int *tab, int size){
    int max = tab[0];
    for (int i = 1; i < size; i++) if (tab[i] > max) max = tab[i];
    return max;
}

int min(int *tab, int size){
    int min = tab[0];
    for (int i = 1; i < size; i++) if (tab[i] < min) min = tab[i];
    return min;
}

void print_matrix_2d(int **tab, int rows, int cols){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            cout << tab[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int start(){
    int source;
    cout << "Generate graph: 0" << endl;
    cout << "Read from file: 1" << endl;
    cout << "Give chosen number: "; cin >> source;
    cout << endl;

    switch (source) {
        case 0:
            matrix = generator();
            break;
        case 1:
            system("cls");
            cout << "queen6.txt:         1" << endl;
            cout << "miles250.txt:       2" << endl;
            cout << "gc1000_300013.txt:  3" << endl;
            cout << "gc500.txt:          4" << endl;
            cout << "le450_5a.txt:       5" << endl;
            cout << "file.txt:           6" << endl;
            cout << "Give chosen number: "; cin >> source;
            cout << endl;
            switch (source){
                case 1:
                    matrix = read_file("instances/queen6.txt");
                    break;
                case 2:
                    matrix = read_file("instances/miles250.txt");
                    break;
                case 3:
                    matrix = read_file("instances/gc1000_300013.txt");
                    break;
                case 4:
                    matrix = read_file("instances/gc500.txt");
                    break;
                case 5:
                    matrix = read_file("instances/le450_5a.txt");
                    break;
                case 6:
                    matrix = read_file("instances/file.txt");
                    break;                
            }            
            break;
    }
    return source;
}