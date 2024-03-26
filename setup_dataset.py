import csv
from sklearn.datasets import make_blobs

bounds = 50


def generate_points(n):
    X, _ = make_blobs(n_samples=n, n_features=3, centers=3, center_box=(-bounds, bounds), cluster_std=2, shuffle=True)
    return X


def save_to_csv(points_list, filename):
    with open(filename, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        for point in points_list:
            writer.writerow(point)


if __name__ == "__main__":
    dataset = [100, 1000, 10000, 100000, 1000000, 10000000]
    for i in dataset:
        points = generate_points(i)
        save_to_csv(points, "input/dataset_" + str(i) + ".csv")
