import pandas as pd
import matplotlib.pyplot as plt


def speedup():
    pass


def single_plot(dim):
    df = pd.read_csv('output/clusters/sequential_4_' + str(dim) + '.csv', delimiter=',')
    x = df.iloc[:, 0]
    y = df.iloc[:, 1]
    z = df.iloc[:, 2]
    centroid = df.iloc[:, 3]
    unique_values = sorted(df.iloc[:, 3].unique())

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    colors = ["blue", "red", "green", "purple", "brown", "pink", "black"]
    for i in range(len(df)):
        ax.scatter(x[i], y[i], z[i], color=colors[unique_values.index(centroid[i])])

    ax.set_xlabel('X Label')
    ax.set_ylabel('Y Label')
    ax.set_zlabel('Z Label')
    ax.set_title('3D Scatter Plot')
    plt.savefig('plot/scatter_plot.png')


if __name__ == "__main__":
    speedup()
    single_plot(100)
