#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

struct Point {
    vector<double> coordinate;
    int actualCentroid{};
};

vector<Point> allZerosCentroid(int k, int dimension) {
    vector<Point> centroids(k);
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < dimension; j++)
            centroids[i].coordinate.push_back(0);
    }
    return centroids;
}

vector<Point> randomCentroid(int k, int dimension, vector<Point> &data) {
    vector<Point> centroids(k);
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < dimension; j++)
            centroids[i].coordinate.push_back(data[rand() % data.size()].coordinate[j]);
    }
    return centroids;
}

double euclideanDistance(Point p1, Point p2) {
    double dist = 0;
    // #pragma omp simd
    for (int i = 0; i < p1.coordinate.size(); i++)
        dist += (p2.coordinate[i] - p1.coordinate[i]) *
                (p2.coordinate[i] - p1.coordinate[i]);//pow(p2.coordinate[i]-p1.coordinate[i],2);
    return sqrt(dist);
}

bool areEqual(const std::vector<Point> &vec1, const std::vector<Point> &vec2) {
    for (int j = 0; j < vec1.size(); j++) {
        for (int i = 0; i < vec1[j].coordinate.size(); i++) {
            if (vec1[j].coordinate[i] != vec2[j].coordinate[i]) {
                return false;
            }
        }
    }
    return true;
}

vector<Point> loadDataset(const string &path) {

    vector<Point> data;
    ifstream file(path);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string temp;
        Point p{};
        getline(ss, temp, ',');
        double x = stod(temp);
        p.coordinate.push_back(x);
        getline(ss, temp, ',');
        p.coordinate.push_back(stod(temp));
        getline(ss, temp, ',');
        p.coordinate.push_back(stod(temp));
        p.actualCentroid = -1;
        data.push_back(p);
    }

    return data;
}

void writeResult(const string &type, const string &len, const string &k, int n, double time,
                 const string &filename) {
    std::ofstream file(filename, std::ios::app);
    file << type + ": " + len + " " + k + " " + std::to_string(n) + " " + std::to_string(time) << std::endl;
    file.close();
}

void writeCSV(const vector<Point> &data, const string &filename) {
    ofstream file(filename);

    for (const auto &point: data) {
        for (double c: point.coordinate) {
            file << c;
            file << ",";
        }
        file << point.actualCentroid;
        file << endl;
    }
    file.close();
}