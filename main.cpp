#include <iostream>
#include <unistd.h>
#include <cstring>

#include "GL/freeglut.h"
#include "GL/gl.h"

// array size
const int n = 200;

// array range
const int max_number = 1000;

// maximum recorded steps
const int max_steps = 10*n*n;

// array to sort 
int array[n] ;

// array_steps (max_steps, n) to record sorting steps
int array_steps[max_steps][n];

int step = 0;

// print array to console
void print_array(int array[], int n){
    for (int i = 0; i < n; i++)
    {
        std::cout << array[i] << "  ";
    }
    std::cout << std::endl;
        
}

// get max of array
int maximum(int array[], int n){
    int max = array[0];

    for (int i = 0; i < n; i++)
    {
        if (max < array[i]){
            max = array[i];
        }
    }

    return max;
    
}

// get min of array
int minimum(int array[], int n){
    int min = array[0];

    for (int i = 0; i < n; i++)
    {
        if (min > array[i]){
            min = array[i];
        }
    }

    return min;
    
}


// bubble sort algorithm
void bubble_sort(int array[], int n){
    int temp;

    for (int i = 0; i < n-1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (array[j] > array[j + 1]){
                temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;

                for (int k = 0; k < n; k++)
                {
                    array_steps[step][k] = array[k];
                }

                step = step + 1;                

            }
        }
        
    }
    
}

// selection sort algorithm
void selection_sort(int array[], int n){
    int min_idx; 
    int temp;

    for (int i = 0; i < n-1; i++) {
        min_idx = i; 

        for (int j = i+1; j < n; j++){
            if (array[j] < array[min_idx]){
                min_idx = j; 
            }
        }

        temp = array[i];
        array[i] = array[min_idx];
        array[min_idx] = temp;

        for (int k = 0; k < n; k++)
        {
            array_steps[step][k] = array[k];
        }
        step = step + 1;  

    }
}

// insertion sort algorithm
void insertion_sort(int array[], int n){
    int key;
    int j;

    for (int i = 1; i < n; i++)
    {
        key = array[i];
        j = i - 1;

        while (j >= 0 && array[j] > key)
        {
            array[j + 1] = array[j];
            j = j - 1;

            for (int k = 0; k < n; k++)
            {
                array_steps[step][k] = array[k];
            }
            step = step + 1; 

        }

        array[j + 1] = key;
        for (int k = 0; k < n; k++)
        {
            array_steps[step][k] = array[k];
        }
        step = step + 1; 
           
    } 
    
}

// merge helper function
void merge(int array[], int l, int m, int r){
    int nl, nr;
    nl = m-l+1; 
    nr = r-m;

    int larr[nl], rarr[nr];

    for(int i = 0; i<nl; i++){
        larr[i] = array[l+i];
    }

    for (int j = 0; j < nr; j++)
    {
        rarr[j] = array[m+1+j];
    }
    
    int i = 0;
    int j = 0;
    int k = l;

    while(i < nl && j<nr) {
        if(larr[i] <= rarr[j]) {
            array[k] = larr[i];
            i++;
        } else {
            array[k] = rarr[j];
            j++;
        }

        for (int kk = 0; kk < n; kk++)
        {
            array_steps[step][kk] = array[kk];
        }
        step = step + 1; 

        k++;
    }

    while(i<nl) { 
        array[k] = larr[i];

        for (int kk = 0; kk < n; kk++)
        {
            array_steps[step][kk] = array[kk];
        }
        step = step + 1; 


        i++; 
        k++;
    }

    while(j<nr) {
        array[k] = rarr[j];
        
        for (int kk = 0; kk < n; kk++)
        {
            array_steps[step][kk] = array[kk];
        }
        step = step + 1; 


        j++; 
        k++;
    }

}

// merge sort algorithm
void merge_sort(int array[], int l, int r) {
    int m;

    if(l < r) {
        int m = l+(r-l)/2;
        merge_sort(array, l, m);
        merge_sort(array, m+1, r);
        merge(array, l, m, r);
    }
}

// partition helper function
int partition(int array[], int low, int high) 
{ 
    int pivot = array[high];   
    int i = (low - 1);   
    int temp;
   
    for (int j = low; j <= high- 1; j++) 
    { 
        if (array[j] <= pivot) 
        { 
            i++;   

            temp = array[i];
            array[i] = array[j];
            array[j] = temp;

            for (int kk = 0; kk < n; kk++)
            {
                array_steps[step][kk] = array[kk];
            }
            step = step + 1; 
        } 
    } 
    
    temp = array[i+1];
    array[i+1] = array[high];
    array[high] = temp;

    for (int kk = 0; kk < n; kk++)
    {
        array_steps[step][kk] = array[kk];
    }
    step = step + 1; 

    return (i + 1); 
} 

// quick sort algorithm
void quick_sort(int array[], int low, int high) 
{ 
    if (low < high) 
    { 
        int pivot = partition(array, low, high); 
   
        quick_sort(array, low, pivot - 1); 
        quick_sort(array, pivot + 1, high); 
    } 
} 

// counting sort algorithm
void count_sort(int array[], int n) {
    int max = maximum(array, n);
    int min = minimum(array, n);
    int range = max - min + 1;

    int count[range];
    int output[n];


    for (int i = 0; i < range; i++){
        count[i] = 0;
    }

    for (int i = 0; i < n; i++){
        count[array[i] - min] = count[array[i] - min] + 1;
    }


    for (int i = 1; i < range; i++){
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        output[count[array[i] - min] - 1] = array[i];
        count[array[i] - min]--;
    }

    for (int i = 0; i < n; i++){
        array[i] = output[i];

        for (int kk = 0; kk < n; kk++)
        {
            array_steps[step][kk] = array[kk];
        }
        step = step + 1; 
    }
}


// draw array sorting opengl function
void draw_array_sorting(){

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);

    int max = maximum(array, n);
    int min = minimum(array, n);

    float start_x;
    float start_y;

    float end_x;
    float end_y;

    for (int k = 1; k < step; k++)
    {

        for (int i = 0; i < n; i++)
        {
            int value = array_steps[k][i];
            int old_value = array_steps[k-1][i];

            glBegin(GL_LINES);
                glColor3f(0, 0, 0);

                start_x = -1.0 + 2 * ((float) i / (float) n);
                start_x = start_x * 0.95;
                start_y = -1.0;

                end_x = start_x;
                end_y = (float) (old_value - min) / (float) (max - min);
                end_y = end_y * 0.9;

                glVertex2f(start_x, start_y);
                glVertex2f(end_x, end_y);

            glEnd();
            
            glBegin(GL_LINES);
                glColor3f(1.0, 1.0, 1.0);

                start_x = -1.0 + 2 * ((float) i / (float) n);
                start_x = start_x * 0.95;
                start_y = -1.0;

                end_x = start_x;
                end_y = (float) (value - min) / (float) (max - min);
                end_y = end_y * 0.9;

                glVertex2f(start_x, start_y);
                glVertex2f(end_x, end_y);

            glEnd();
            glFlush();


        }
    
    }
    
}

int main(int argc, char **argv){

    if (argc == 1){
        return 1;
    }

    // init array with random values
    for (int i = 0; i < n; i++)
    {
        array[i] = rand()%max_number;
    }

    char * sorting_algorithm = argv[1];

    if (strcmp(sorting_algorithm, "bubble-sort") == 0){
        bubble_sort(array, n);
    }else if (strcmp(sorting_algorithm, "quick-sort") == 0){
        quick_sort(array, 0, n-1);
    }else if (strcmp(sorting_algorithm, "selection-sort") == 0){
        selection_sort(array, n);
    }else if (strcmp(sorting_algorithm, "insertion-sort") == 0){
        insertion_sort(array, n);
    }else if (strcmp(sorting_algorithm, "merge-sort") == 0){
        merge_sort(array, 0, n-1);
    }else if (strcmp(sorting_algorithm, "count-sort") == 0){
        count_sort(array, n);
    } else {
        return 1;
    }


    // opengl calls
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(sorting_algorithm);

    usleep(1e+5);
    
    glutDisplayFunc(draw_array_sorting);
    glutMainLoop();
}

// g++ main.cc -lglut -lGL -o main