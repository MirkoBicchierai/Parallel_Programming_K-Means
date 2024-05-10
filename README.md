# Parallel Programming, K-Means

This project aims to implement a clustering algorithm in C++, offering both a sequential version and a parallel version that runs on a processor using the OpenMP library.

CPU of the machine used for testing:

- 11th Gen Intel(R) Core(TM) i7-11800H @ 2.30GHz (Mobile)
- Thread per core:  2
- Core per socket:  8

# Speed-up results for the clustering algorithm:

<h3>Speed-up plots for all cluster sizes tested:</h3>

<table>
 <tr>
    <td><img src="SpeedUp/SpeedUp clustering_K3.png"></td>
    <td><img src="SpeedUp/SpeedUp clustering_K5.png"></td>
    <td><img src="SpeedUp/SpeedUp clustering_K10.png"></td>
 </tr>
 <tr>
    <td><img src="SpeedUp/SpeedUp clustering_K15.png"></td>
    <td><img src="SpeedUp/SpeedUp clustering_K20.png"></td>
    <td><img src="SpeedUp/SpeedUp clustering_K25.png"></td>
 </tr>
 <tr>
    <td><img src="SpeedUp/SpeedUp clustering_K30.png"></td>
    <td><img src="SpeedUp/SpeedUp clustering_K40.png"></td>
    <td><img src="SpeedUp/SpeedUp clustering_K50.png"></td>
 </tr>
</table>

<h3>Speed-up plots for all datasets used:</h3>

<table>
 <tr>
    <td><img src="SpeedUp/SpeedUp clustering_N100.png"></td>
    <td><img src="SpeedUp/SpeedUp clustering_N1000.png"></td>
 </tr>
 <tr>
    <td><img src="SpeedUp/SpeedUp clustering_N10000.png"></td>
    <td><img src="SpeedUp/SpeedUp clustering_N100000.png"></td>
 </tr>
 <tr>
    <td><img src="SpeedUp/SpeedUp clustering_N1000000.png"></td>
    <td><img src="SpeedUp/SpeedUp clustering_N10000000.png"></td>
 </tr>
</table>

# Speed-up results for the kmeans initialization:

<h3>Speed-up plots for all cluster sizes tested:</h3>

<table>
 <tr>
    <td><img src="SpeedUp/SpeedUp KMeans Initialization_K3.png"></td>
    <td><img src="SpeedUp/SpeedUp KMeans Initialization_K5.png"></td>
    <td><img src="SpeedUp/SpeedUp KMeans Initialization_K10.png"></td>
 </tr>
 <tr>
    <td><img src="SpeedUp/SpeedUp KMeans Initialization_K15.png"></td>
    <td><img src="SpeedUp/SpeedUp KMeans Initialization_K20.png"></td>
    <td><img src="SpeedUp/SpeedUp KMeans Initialization_K25.png"></td>
 </tr>
 <tr>
    <td><img src="SpeedUp/SpeedUp KMeans Initialization_K30.png"></td>
    <td><img src="SpeedUp/SpeedUp KMeans Initialization_K40.png"></td>
    <td><img src="SpeedUp/SpeedUp KMeans Initialization_K50.png"></td>
 </tr>
</table>

<h3>Speed-up plots for all datasets used:</h3>

<table>
 <tr>
    <td><img src="SpeedUp/SpeedUp KMeans Initialization_N100.png"></td>
    <td><img src="SpeedUp/SpeedUp KMeans Initialization_N1000.png"></td>
 </tr>
 <tr>
    <td><img src="SpeedUp/SpeedUp KMeans Initialization_N10000.png"></td>
    <td><img src="SpeedUp/SpeedUp KMeans Initialization_N100000.png"></td>
 </tr>
 <tr>
    <td><img src="SpeedUp/SpeedUp KMeans Initialization_N1000000.png"></td>
    <td><img src="SpeedUp/SpeedUp KMeans Initialization_N10000000.png"></td>
 </tr>
</table>

# How to use

<h3>First Step (Folder setup and generate datasets):</h3>

In the main project folder, create the following system directories:

    input/
    output/clusters/
    output/centroids/

Then execute setup_dataset.py, which will generate datasets in the 'input' directory. This script creates datasets for N=100, 1,000, 10,000, 100,000, 1,000,000, and 10,000,000. For each dataset, it also prepares versions for cluster sizes K=3, 5, 10, 15, 20, 25, 30, 40, and 50.

<h3>Second Step (Run the algorithm):</h3>

Then compile and run `main-parallel.cpp` to run the parallel version and `main-sequential.cpp` for the sequential version of the algorithm.
Please note that the sequential version requires a significant amount of time to execute all tests, depending on your machine's hardware capabilities. For my tests, it took approximately 50-60 hours.

At the end of the execution, all timing data will be saved in the 'Times' directory.

<h3>Third Step (Speed-Up plot):</h3>

Execute the speed_up.py script to generate the Speed Up plots. These plots will be saved in the 'SpeedUp' folder.

