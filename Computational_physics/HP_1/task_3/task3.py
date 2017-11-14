import matplotlib.pyplot as plt
import numpy as np
def main():
    delta_t = 0.1

    ht_fft_f2_psi0 = []
    with open('task_3/task3_data_fft_f_2_psi_0.txt', 'r') as textfile:
        for line in textfile:
            line = line.split(',')
            ht_fft_f2_psi0.append(float(line[0]) + 1j*float(line[1]))

    ht_fft_f1_psi0 = []
    with open('task_3/task3_data_fft_f_1_psi_0.txt', 'r') as textfile:
        for line in textfile:
            line = line.split(',')
            ht_fft_f1_psi0.append(float(line[0]) + 1j*float(line[1]))

    ht_fft_f1_psi_pi2 = []
    with open('task_3/task3_data_fft_f_1_psi_pi2.txt', 'r') as textfile:
        for line in textfile:
            line = line.split(',')
            ht_fft_f1_psi_pi2.append(float(line[0]) + 1j*float(line[1]))

    dt = 0.1
    fs = 1/dt
    N = len(ht_fft_f2_psi0)
    f = np.linspace(-0.5, 0.5, N)*fs

    # According to parsevals theorem the integral of the signal squared is equal
    # to the integral of the power spectrum. The intregral is approximately
    # the same for the two frequencies (boundaries can have effect).

    fig = plt.figure()
    ax_PSD = fig.add_subplot(111)
    ax_PSD.set_title("Power spectrum")
    ax_PSD.plot(f, np.abs(ht_fft_f2_psi0), label = 'f(t) = cos((2/(2*pi))*2*pi*t)')
    ax_PSD.plot(f, np.abs(ht_fft_f1_psi0), label = 'f(t) = cos((1/(2*pi))*2*pi*t)')
    ax_PSD.plot(f, np.abs(ht_fft_f1_psi_pi2), label = 'f(t) = cos((1/(2*pi))*2*pi*t+ pi/2)')
    ax_PSD.grid(b=True, which='major', color='k', linestyle='-')
    ax_PSD.grid(b=True, which='minor', color='k', linestyle='-', alpha=0.2)
    ax_PSD.minorticks_on()
    ax_PSD.set_xlabel('Frequency')
    ax_PSD.set_ylabel('Amplitude^2')
    ax_PSD.legend(loc=1)
    plt.show()

if __name__ == '__main__':
    main()
