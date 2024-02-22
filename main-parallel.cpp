#include <iostream>
#include <cstdlib>
#include <vector>
#include <omp.h>
#include "commonFunction.cpp"
#include <string>

using namespace std;

vector<Point> kMeans(vector<Point>& data, int k, int maxIterations, int threads) {

    vector<Point> centroids = randomCentroid(k,data);

    for (int iter = 0; iter < maxIterations; ++iter) {

        vector<Point> newCentroids(k, {0, 0, 0});
        vector<int> counts(k, 0);

        #pragma omp parallel num_threads(threads)
        {
            vector<int> tmp_cluster_cardinality(k, 0);
            vector<Point> tmp_newCentroids(k, {0, 0, 0});

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
                data[i].actualCentroid = clusterIdx;
                tmp_newCentroids[clusterIdx].x += data[i].x;
                tmp_newCentroids[clusterIdx].y += data[i].y;
                tmp_newCentroids[clusterIdx].z += data[i].z;
                tmp_cluster_cardinality[clusterIdx]++;
            }

            #pragma omp critical
            {
                for (int i = 0; i < k; i++) {
                    newCentroids[i].x += tmp_newCentroids[i].x;
                    newCentroids[i].y += tmp_newCentroids[i].y;
                    newCentroids[i].z += tmp_newCentroids[i].z;
                    counts[i] += tmp_cluster_cardinality[i];
                }
            }

        }

        for (size_t i = 0; i < newCentroids.size(); ++i) {
            newCentroids[i].x = newCentroids[i].x / counts[i];
            newCentroids[i].y = newCentroids[i].y / counts[i];
            newCentroids[i].z = newCentroids[i].z / counts[i];
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

//TODO profiling python, relation, presentation, General dimension and vectorization with omp

int main() {
    string file_name = "1000";
    int k = 3;
    int threads = 16;
    int maxIterations = 100;

    vector<Point> data = loadDataset("../input/dataset_"+file_name+".csv");

    double dtime = omp_get_wtime();
    vector<Point> centroids  = kMeans(data,k,maxIterations,threads);
    dtime = omp_get_wtime() - dtime;
    cout << "Execution time: " << dtime << " seconds" << endl;

    writeCSV(centroids, "../output/centroids/parallel_"+to_string(k)+"_"+to_string(data.size())+"_"+to_string(threads)+".csv");
    writeCSV(data, "../output/clusters/parallel_"+to_string(k)+"_"+to_string(data.size())+"_"+to_string(threads)+".csv");

    return 0;
}