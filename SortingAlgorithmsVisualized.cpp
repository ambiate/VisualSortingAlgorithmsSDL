/*
Author: Jonathan Drouillard
Assignment Title: Sorting Visualizarion
Assignment Description: Implement Selection Sort Insertion Sort,
Heap Sort, Quick Sort, Merge Sort.
Due Date: 3/30/12
Date Created: 3/24/12
Date Last Modified: 3/30/12
*/

#include <iostream>
#include "SDL/SDL.h"
#include "graphic.h"
#include <vector>
#include <algorithm>
using namespace std;

void fill(int data[]);
void display(int data[], int s);
void BubbleSort(int data[],int s,graphic);

//************************************************************
// description: Perform the selection sort on an array.      *
// return: void                                              *
// pre: Array contains data, size is accurate.               *
// post: Sorted array.                                       *
//                                                           *
//************************************************************
void SelectionSort(int data[],int s,graphic);

//************************************************************
// description: Perform the insertion sort on an array.      *
// return: void                                              *
// pre: Array contains data, size is accurate.               *
// post: Sorted array.                                       *
//                                                           *
//************************************************************
void InsertionSort(int data[],int s,graphic);

//************************************************************
// description: Perform the bottom up heap approach.         *
// return: void                                              *
// pre: Array contains data, size is accurate.               *
// post: Transforms array into a heap.                       *
//                                                           *
//************************************************************
void HeapBottomUp(int data[], int s, graphic screen);

//************************************************************
// description: Perform the heap sort on an array.           *
// return: void                                              *
// pre: Array contains data, size is accurate.               *
// post: Sorted array.                                       *
//                                                           *
//************************************************************
void HeapSort(int data[], int s, graphic);

//************************************************************
// description: Brute force search s1 for pattern s2.        *
// return: void                                              *
// pre: Array contains data, size is accurate.               *
// post: Sorted array.                                       *
//                                                           *
//************************************************************
int Partition(int data[], int l, int r, graphic screen);

//************************************************************
// description: Perform the quick sort on an array.          *
// return: void                                              *
// pre: Array contains data, size is accurate.               *
// post: Sorted array.                                       *
//                                                           *
//************************************************************
void QuickSort(int data[],int,int,graphic);

//************************************************************
// description: Perform the merge sort on an array.          *
// return: void                                              *
// pre: Array contains data, size is accurate.               *
// post: Sorted array.                                       *
//                                                           *
//************************************************************
void MergeSort(int data[],int s, int e, graphic);



int main(int argc, char *argv[])
{
  bool    done = false;
  char    c;
  graphic screen;
  
  int data[COL];
  
  while(!done){
	    SDL_Delay(DELAY);
	    // Poll for events, and handle the ones we care about.
	    while (SDL_PollEvent(&event)) 
	    {
	      switch (event.type) 
	      {
		      case SDL_KEYDOWN:
		    	
		    	c = toupper(event.key.keysym.sym);
		    	if(c == 'R'){
		    		fill(data);
		    		screen.display(data,COL);
		    	}
		    	if(c == 'X') done = true;
		    	if(c == 'B') BubbleSort(data,COL,screen);
		    	if(c == 'S') SelectionSort(data, COL, screen);
                if(c == 'I') InsertionSort(data, COL, screen);
                if(c == 'H') HeapSort(data, COL, screen);
                if(c == 'M') MergeSort(data, 0, COL-1, screen);
                if(c == 'Q') QuickSort(data, 0, COL-1, screen);
                if(c == 'D') screen.display(data,COL);
		        break;
		      case SDL_KEYUP:
		        // If escape is pressed, return (and thus, quit)
		        if (event.key.keysym.sym == SDLK_ESCAPE)
		          done = true;
		        break;
		        
		      case SDL_QUIT:
		        done = true;;
	      }
	    }
}

  return 0;
}


void fill(int data[]){
	for(int i = 0; i < COL; i++)
		data[i] = rand()%ROW;
}

void BubbleSort(int data[],int s,graphic screen){
	  for(int i = 0; i < s-1; i++){
		  for(int j = 0; j < s - i - 1; j++){
			  if(data[j] > data[j+1]){
				  swap(data[j],data[j+1]);
			  }
              screen.display(data,s);
		  }
	  }
	
}

//done
void SelectionSort(int data[], int s, graphic screen) {
    //loop through the array
    for(int i = 0; i < s-1; i++) {
        //set current to the minimum
        int min = i;
        //loop through and find the smallest value
        for(int j = i+1; j < s; j++) {
            //set the new min if found
            if(data[j] < data[min])
                min = j;
            //continue looking for a new min
        }
        //preserve stability
        if(min != i)
            swap(data[i], data[min]);
        screen.display(data,s);
    }
}

void InsertionSort(int data[], int s, graphic screen) {
    //loop through the array
    for(int i = 0; i < s; i++) {
        //archive current data
        int v = data[i];
        int j = i-1;
        //check if it needs to be moved
        while(j >= 0 && data[j] > v) {
            //move if necessary
            data[j+1] = data[j];
            j = j-1;
            screen.display(data,s);
        }
        //place in archived data
        data[j+1] = v;
    }
}

void HeapBottomUp(int data[], int s, graphic screen) {
    int i, j, k, v;

    //Loop through the array
    for(i = 1; (i<s) && (k=i); i++) {
        //archive current data of interest
        v = data[i];
        //get a parental node
        j = (i-1)/2;
        //seek the proper spot for this node
        while(data[j] < v && k) {
            //old swaparoo
            data[k] = data[j];
            k = j;
            //next parental node
            j = (k-1)/2;
            screen.display(data,s);
        }
        //use old archive
        data[k] = v;
    }
}

void HeapSort(int data[], int s, graphic screen) {
    //backwards loop through the array
    for(int i = s-1; i; i--) {
        //swap root and last node
        swap(data[i], data[0]);
        //try to bring it back to the root,
        //or find a proper home for it
        HeapBottomUp(data, i, screen);
        screen.display(data,s);
    }
}

//Hoare's
int Partition(int data[], int l, int r, graphic screen) {
    //locates a decent place to split an array

    //select a pivot
    int p = data[l];
    int i = l;
    int j = r+1;
    do {
        i+=1;
        j-=1;
        //grow a portion of the array til the pivot data
        while(data[i] < p)
            i += 1;
        //grow another potion of the array til the pivot data
        while(data[j] > p)
            j -= 1;
        //swap so you can grow the portions again
        swap(data[i], data[j]);
        screen.display(data,r);
    //until i >= j
    } while(i < j);
    //correct our mishaps from the previous iteration
    swap(data[i], data[j]);
    swap(data[l], data[j]);
    return j;
}

void QuickSort(int data[],int l, int r, graphic screen) {
    //base
    if(l < r) {
        //find a split position
        int s = Partition(data, l, r, screen);
        screen.display(data,r);
        //divide into sub array
        QuickSort(data, l, (s-1), screen);
        screen.display(data,r);
        //divide into sub array
        QuickSort(data, (s+1), r, screen);
        screen.display(data,r);
    }
}

void MergeSort(int data[], int b, int s, graphic screen) {
    //base
    if (s-1<=b)
        return;
    //merge a portion of the array
    MergeSort( data, b, (b+s)/2, screen );
    //merge another portion of the array
    MergeSort( data, (b+s)/2, s, screen );
    screen.display(data,s);
    //perform the merge
    inplace_merge( data+b, data+(b+s)/2, data+s );
    screen.display(data,s);
}