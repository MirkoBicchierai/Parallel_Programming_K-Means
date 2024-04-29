import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


def speedup():
    pass


def single_plot(dim):
    for iter in range(10):
        df = pd.read_csv('tmp/sequential_data_I_' + str(iter) + '_K_10_1000.csv', delimiter=',')
        df2 = pd.read_csv('tmp/sequential_cen_I_' + str(iter) + '_K_10_1000.csv', delimiter=',')
        print(iter)
        print(df2)
        x = df.iloc[:, 0]
        y = df.iloc[:, 1]
        z = df.iloc[:, 2]
        x_cen = df2.iloc[:, 0]
        y_cen = df2.iloc[:, 1]
        z_cen = df2.iloc[:, 2]
        centroid = df.iloc[:, 3]
        unique_values = sorted(df.iloc[:, 3].unique())

        fig = plt.figure()
        ax = fig.add_subplot(111, projection='3d')
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
        c = np.zeros(10)
        for i in range(len(df)):
            c[unique_values.index(centroid[i])] = c[unique_values.index(centroid[i])] + 1
            ax.scatter(x[i], y[i], z[i], color=colors[unique_values.index(centroid[i])])


        for i in range(len(df2)):
            ax.scatter(x_cen[i], y_cen[i], z_cen[i], color=colors[i], marker='x', s=100)

        ax.set_xlabel('X Label')
        ax.set_ylabel('Y Label')
        ax.set_zlabel('Z Label')
        ax.set_title('3D Scatter Plot')
        plt.savefig('plot/scatter_plot_' + str(iter) + '.png')


if __name__ == "__main__":
    speedup()
    single_plot(100)
