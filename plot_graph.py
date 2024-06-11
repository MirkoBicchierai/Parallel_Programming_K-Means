import pandas as pd
import matplotlib.pyplot as plt


def single_plot(n, k):
    df = pd.read_csv('output/clusters/parallel_' + str(k) + '_' + str(n) + '_16.csv', delimiter=',')
    df2 = pd.read_csv('output/centroids/parallel_' + str(k) + '_' + str(n) + '_16.csv', delimiter=',')

    x_point = df.iloc[:, 0]
    y_point = df.iloc[:, 1]
    z_point = df.iloc[:, 2]
    centroid_point = df.iloc[:, 3]

    x_cen = df2.iloc[:, 0]
    y_cen = df2.iloc[:, 1]
    z_cen = df2.iloc[:, 2]

    colors = [
        "#0000FF",  # Blue
        "#FF0000",  # Red
        "#008000",  # Green
        "#800080",  # Purple
        "#A52A2A",  # Brown
        "#FFC0CB",  # Pink
        "#000000",  # Black
        "#FFFF00",  # Yellow
        "#FFA500",  # Orange
        "#AFFAFF"  # White
    ]

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    fig.subplots_adjust(left=0.01, right=0.99, bottom=0.05, top=0.95)
    for i in range(len(df)):
        ax.scatter(x_point[i], y_point[i], z_point[i], color=colors[centroid_point[i]], alpha=0.15)

    for i in range(len(df2)):
        ax.scatter(x_cen[i], y_cen[i], z_cen[i], marker='x', s=100, color='black', alpha=1)

    ax.grid(True)

    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    ax.set_title('N = ' + str(n) + ', K = ' + str(k))
    plt.savefig('plots/plt_' + str(n) + '_' + str(k) + '.png')
    plt.savefig('plots/plt_' + str(n) + '_' + str(k) + '.pdf')


def plot_dataset(path):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    fig.subplots_adjust(left=0.01, right=0.99, bottom=0.01, top=0.99)

    df = pd.read_csv(path, delimiter=',')
    x_point = df.iloc[:, 0]
    y_point = df.iloc[:, 1]
    z_point = df.iloc[:, 2]
    ax.scatter(x_point, y_point, z_point, alpha=0.15)

    ax.grid(True)
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z ')
    plt.savefig('plots/plt_d.png')
    plt.savefig('plots/plt_d.pdf')


if __name__ == "__main__":
    single_plot(1000, 3)
    # plot_dataset("input/dataset_1000_5.csv")
