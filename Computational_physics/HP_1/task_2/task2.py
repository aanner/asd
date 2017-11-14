import matplotlib.pyplot as plt
import numpy as np
def main():
    delta_t = 0.1

    ht_fft = []
    with open('task_2/task2_data_fft.txt', 'r') as textfile:
        for line in textfile:
            line = line.split(',')
            ht_fft.append(float(line[0]) + 1j*float(line[1]))

    dt = 0.1
    fs = 1/dt
    N = len(ht_fft)
    f = np.linspace(0, 1, N)*fs
    P_n = np.abs(ht_fft)**2/N

    fig = plt.figure()

    ax_DFT = fig.add_subplot(211)
    ax_DFT.set_title("Discrete frourier transform")
    ax_DFT.plot(f, np.abs(ht_fft), label = 'f(t) = cos((2/(2*pi))*2*pi*t)')
    ax_DFT.grid(b=True, which='major', color='k', linestyle='-')
    ax_DFT.grid(b=True, which='minor', color='k', linestyle='-', alpha=0.2)
    ax_DFT.minorticks_on()
    ax_DFT.set_xlabel('Frequency')
    ax_DFT.set_ylabel('Amplitude')
    ax_DFT.legend(loc=1)

    ax_PSD = fig.add_subplot(212)
    ax_PSD.set_title("Power spectrum")
    ax_PSD.plot(f, P_n, label = 'f(t) = cos((2/(2*pi))*2*pi*t)')
    ax_PSD.grid(b=True, which='major', color='k', linestyle='-')
    ax_PSD.grid(b=True, which='minor', color='k', linestyle='-', alpha=0.2)
    ax_PSD.minorticks_on()
    ax_PSD.set_xlabel('Frequency')
    ax_PSD.set_ylabel('Amplitude^2')
    ax_PSD.legend(loc=1)

    plt.show()
if __name__ == '__main__':
    main()
