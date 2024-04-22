import csv
from sklearn.datasets import make_blobs
import numpy as np

bounds = 50


def generate_points(n, k):
    X, _ = make_blobs(n_samples=n, n_features=3, centers=k, center_box=(-bounds, bounds), cluster_std=2, shuffle=True)
    return X


def save_to_csv(points_list, filename):
    with open(filename, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        for point in points_list:
            writer.writerow(point)


if __name__ == "__main__":
    dataset = [100, 1000, 10000, 100000, 1000000, 10000000]
    cen = np.arange(3, 51)
    for i in dataset:
        for k in cen:
            points = generate_points(i, k)
            save_to_csv(points, "input/dataset_" + str(i) + "_" + str(k) + ".csv")
            print("input/dataset_" + str(i) + "_" + str(k) + ".csv")
