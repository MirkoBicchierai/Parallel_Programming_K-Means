import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


def read_file(path):
    with open(path, 'r') as file:
        vector_of_words = []
        for line in file:
            words = line.strip().split()
            vector_of_words.append(words)
    return vector_of_words


def plot_speed_up(t_s, t_p, title, ty):
    clusters = [3, 5, 10, 15, 20, 25, 30, 40, 50]
    data_length = ["100", "1000", "10000", "100000", "1000000", "10000000"]
    speed_up_x = []
    speed_up_y = []
    color_palette = ["#ff6347", "#4682b4", "#32cd32", "#ff8c00", "#9370db", "#3cb371", "#ffa500", "#40e0d0", "#ff69b4",
                     "#8a2be2", "#00ced1", "#daa520"]

    if ty:
        n = data_length[5]
        plt.title(title + " n=" + n)
        i = 0
        for k in clusters:
            line_seq = []
            for line in t_s:
                if int(line[1]) == k and line[0] == n:
                    line_seq = line
            speed_up_x.append(1)
            speed_up_y.append(1)
            for line in t_p:
                if int(line[1]) == k and line[0] == n:
                    speed_up_x.append(int(line[2]))
                    speed_up_y.append(float(line_seq[3]) / float(line[3]))
            plt.plot(speed_up_x, speed_up_y, label='k = ' + str(k), color=color_palette[i])
            speed_up_x = []
            speed_up_y = []
            i = i + 1
    else:
        k = clusters[8]
        plt.title(title + " k=" + str(k))
        i = 0
        for n in data_length:
            line_seq = []
            for line in t_s:
                if int(line[1]) == k and line[0] == n:
                    line_seq = line
                    print("SEQ:", line_seq)
            speed_up_x.append(1)
            speed_up_y.append(1)
            for line in t_p:
                if int(line[1]) == k and line[0] == n:
                    print(line)
                    speed_up_x.append(int(line[2]))
                    speed_up_y.append(float(line_seq[3]) / float(line[3]))
            plt.plot(speed_up_x, speed_up_y, label='n = ' + n, color=color_palette[i])
            speed_up_x = []
            speed_up_y = []
            i = i + 1

    plt.grid(True)
    plt.grid(which='both', linestyle='--', linewidth=0.5)

    plt.xlabel('Thread')
    plt.ylabel('Speed Up')
    plt.legend()
    if ty:
        plt.savefig('SpeedUp/' + title + "_N" + n + '.png')
    else:
        plt.savefig('SpeedUp/' + title + "_K" + str(k) + '.png')
    plt.close()


def speedup():
    time_seq = read_file("Times/Times_Kmeans_Sequential.txt")
    time_par = read_file("Times/Times_Kmeans_Parallel.txt")

    plot_speed_up(time_seq, time_par, "SpeedUp KMeans Initialization", True)
    plot_speed_up(time_seq, time_par, "SpeedUp KMeans Initialization", False)

    time_seq = read_file("Times/Times_Sequential.txt")
    time_par = read_file("Times/Times_Parallel.txt")

    plot_speed_up(time_seq, time_par, "SpeedUp clustering", True)
    plot_speed_up(time_seq, time_par, "SpeedUp clustering", False)





if __name__ == "__main__":
    speedup()
