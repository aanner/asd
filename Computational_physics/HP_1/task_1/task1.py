import matplotlib.pyplot as plt
import numpy as np
def main():
    delta_t = 0.1

    h_t1 = []
    with open('task_1/task11_data.txt', 'r') as textfile:
        for line in textfile:
            h_t1.append(float(line))

    h_t2 = []
    with open('task_1/task12_data.txt', 'r') as textfile:
        for line in textfile:
            h_t2.append(float(line))

    h_t3 = []
    with open('task_1/task13_data.txt', 'r') as textfile:
        for line in textfile:
            h_t3.append(float(line))

    n = len(h_t1)
    t_tot = n*delta_t
    t = np.linspace(0, 1, n)*t_tot
    fig = plt.figure()

    ax = fig.add_subplot(111)
    ax.plot(t, h_t1, label = 'f(t) = cos(2t)')
    ax.plot(t, h_t2, label = 'f(t) = cos(t)')
    ax.plot(t, h_t3, label = 'f(t) = cos(t + pi/2) = sin(t)')
    ax.legend(loc=1)

    plt.show()

if __name__ == '__main__':
    main()
