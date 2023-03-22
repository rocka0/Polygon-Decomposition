# <center>CSF364: Design and Analysis of Algorithms</center>
### <center>Assignment 1: Decomposition of simple polygons into convex polygons</center>
####  <center>Ashwin Arun (2020A7PSH) </center>
#### <center>Kavyanjali Agnihotri (2020A7PS0185H) </center
#### <center>Tushar Brijesh Chenan (2020A7PS0253H) </center>

## Introduction

In this assignment, we were required to implement the research paper: [Algorithms for the decomposition of a polygon into convex polygons](https://doi.org/10.1016/S0377-2217%2899%2900033-8)

The paper primarily focuses on $2$ objectives:

1. Decomposing a given simple polygon into several non-overlapping convex polygons without the addition of any extra vertices.
2. Merging two or more convex polygons of the planar subdivision obtained above so as to reduce the number of convex polygons in the decomposition.

Our additional tasks were as follows:

1. Store the planar subdivision in a structure known as a [DCEL](https://en.wikipedia.org/wiki/Doubly_connected_edge_list) which allows us to effectively represent and query planar subdivisions.
2. Write a program to visualize the output of the algorithm, i.e, given a simple polygon, output the decomposition produced by the algorithm in a visually intuitive way.

## DCEL: The What and The How

Explain DCEL here

## Plotting the outputs

Explain plot.py here

## Writing a simple polygon generator

Explain gen.py here

## Findings and Analysis

 - Running time of algorithm $vs$ number of vertices ($n$) in the simple polygon.
	- For smaller $n$, do more trials and for larger $n$, do less trials 
 - Number of decompositions $vs$ number of vertices ($n$) in the simple polygon.
	- As a corollary, we also plot number of polygons reduced (merged) vs number of vertices ($n$) in the simple polygon.
 - Simple hand made test case to identify the effect of start point of algorithm on output.
 - One real life significant test case (Eg. India map as a simple polygon or anything else)

## Experimental Time Complexity
Based on the plots, we can see that the program runs in $$ \mathcal{O}(n^{2} \log n) $$
