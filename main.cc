#include <iostream>
#include <unistd.h>

#include "GL/freeglut.h"
#include "GL/gl.h"

// array size
const int n = 130;

// maximum recorded steps
const int max_steps = 10000;

int array[n] ;
int array_steps[max_steps][n];

int step = 0;

void print_array(int array[], int n){
    for (int i = 0; i < n; i++)
    {
        std::cout << array[i] << "  ";
    }
    std::cout << std::endl;
        
}

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

void draw_array(){

    // black background      
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

            usleep(1e+2);

            glFlush(); 
        }
    
    }
    
}

int main(int argc, char **argv){

    for (int i = 0; i < n; i++)
    {
        array[i] = n-i;
    }


    //selection_sort(array, n);
    //bubble_sort(array, n);
    //insertion_sort(array, n);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(1200, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL - Creating a triangle");
    glutDisplayFunc(draw_array);
    glutMainLoop();
}

// g++ main.cc -lglut -lGL -o main