#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <random>

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
        centroids[i].actualCentroid = i;
    }
    return centroids;
}

vector<Point> randomCentroid(int k, int dimension, vector<Point> &data) {

    vector<Point> centroids(k);

    vector<int> indexes(k);
    std::random_device rand_dev;
    std::mt19937 gen(rand_dev());
    std::uniform_int_distribution<> distrib(0, data.size() - 1);

    int r;
    for (int i = 0; i < k; i++) {
        while(true) {
            r = distrib(gen);
            if(std::find(indexes.begin(), indexes.end(), r) == indexes.end())
                break;
        }
        indexes.push_back(r);
        for (int j = 0; j < dimension; j++)
            centroids[i].coordinate.push_back(data[r].coordinate[j]);
    }
    return centroids;
}
// #pragma omp simd
double euclideanDistance(Point p1, Point p2) {
    double dist = 0;
    for (int i = 0; i < p1.coordinate.size(); i++)
        dist += pow((p2.coordinate[i] - p1.coordinate[i]), 2);
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

void writeResult(const string &len, const string &k, int n, double time,
                 const string &filename) {
    std::ofstream file(filename, std::ios::app);
    file << len + " " + k + " " + std::to_string(n) + " " + std::to_string(time) << std::endl;
    file.close();
}

void writeCSV(const vector<Point> &data, const string &filename) {
    ofstream file(filename);
    file << "X";
    file << ",";
    file << "Y";
    file << ",";
    file << "Z";
    file << ",";
    file << "Actual";
    file << endl;
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