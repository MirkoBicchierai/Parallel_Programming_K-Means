#include <iostream>
#include <cstdlib>
#include <vector>
#include <chrono>
#include "commonFunction.cpp"

//Execution time: 14924 millisecond
//CENTROIDS:
//28.7896 51.6934
//15.3098 -80.3751
//17.9158 113.029
//38.7263 12.7813

using namespace std;

vector<Point> kMeans(const vector<Point>& data, int k, int maxIterations) {

    vector<Point> centroids(k, {0, 0});
    for (int i = 0; i < k; ++i) {
        centroids[i] = data[rand() % data.size()];
    }

    for (int iter = 0; iter < maxIterations; ++iter) {

        vector<Point> newCentroids(k, {0,0});
        vector<int> counts(k, 0);
        int threads = 16;
        #pragma omp parallel num_threads(threads)
        {
            vector<int> tmp_cluster_cardinality(k, 0);
            vector<Point> tmp_newCentroids(k, {0,0});

            #pragma omp for nowait schedule(static, data.size() / threads)
            for (int i = 0; i < data.size(); i++) {
                double minDistance = euclideanDistance(data[i], centroids[0]);
                int clusterIdx = 0;
                for (int j = 1; j < centroids.size(); j++) {
                    double distance = euclideanDistance(data[i], centroids[j]);
                    if (distance < minDistance) {
                        minDistance = distance;
                        clusterIdx = j;
                    }
                }
                tmp_newCentroids[clusterIdx].x += data[i].x;
                tmp_newCentroids[clusterIdx].y += data[i].y;
                tmp_cluster_cardinality[clusterIdx]++;
            }

            #pragma omp critical
            {
                for (int i = 0; i < k; i++) {
                    newCentroids[i].x += tmp_newCentroids[i].x;
                    newCentroids[i].y += tmp_newCentroids[i].y;
                    counts[i] += tmp_cluster_cardinality[i];
                }
            }

        }

        for (size_t i = 0; i < newCentroids.size(); ++i) {
            newCentroids[i].x = newCentroids[i].x / counts[i];
            newCentroids[i].y = newCentroids[i].y / counts[i];
        }

        /*
        if (areEqual(centroids, newCentroids)) {
            return centroids;
        }
        */
        centroids = newCentroids;
    }

    return centroids;
}

//TODO profiling python, exec time, relation, presentation

int main() {

    srand(17);
    int maxIterations = 100;
    int k = 4;
    vector<Point> data = loadDataset("/home/mirko/CLionProjects/Parallel-Programming/worldcities.csv");
    auto start = chrono::high_resolution_clock::now();
    vector<Point> centroids  = kMeans(data,k,maxIterations);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Execution time: " << duration.count() << " millisecond" << endl;

    cout<<"CENTROIDS:"<<endl;
    for(auto centroid:centroids)
        cout<<centroid.x<<" "<<centroid.y<<endl;

    return 0;
}