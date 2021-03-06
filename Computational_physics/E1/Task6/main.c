/*
E1_main.c

Created by AL on 2013-10-24.
Further developed by Martin Gren on 2014-10-20.
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "func.h"
#include "fft_func.h"
#define PI 3.141592653589
#define nbr_of_timesteps 32767 /* nbr_of_timesteps+1 = power of 2, for best speed */
#define nbr_of_particles 3 /* The number of particles is 3 */

/* Main program */
int main()
{
	/* Declartion of variables */
	double timestep;
	int i,j;
	double timestep_sq,current_time;
	double m;
	double kappa;

	/* declare file variable */
	FILE *file;
	FILE *file_energy;
	FILE *file_ps;

	/* displacement, velocity and acceleration */
	double q[nbr_of_particles];
	double v[nbr_of_particles];
	double a[nbr_of_particles];


	/* Allocating memory for large vectors */
	/* displacements for writing to file */
	double *q_1 = malloc((nbr_of_timesteps+1) * sizeof (double));
	double *q_2 = malloc((nbr_of_timesteps+1) * sizeof (double));
	double *q_3 = malloc((nbr_of_timesteps+1) * sizeof (double));

	double *potential_energy = malloc((nbr_of_timesteps+1) * sizeof (double));
	double *kinetic_energy = malloc((nbr_of_timesteps+1) * sizeof (double));
	double *total_energy = malloc((nbr_of_timesteps+1) * sizeof (double));
	double *powspec_data = malloc((nbr_of_timesteps+1) * sizeof (double));
	double *freq = malloc((nbr_of_timesteps+1) * sizeof (double));
	double *q_all = malloc((nbr_of_timesteps+1) * sizeof (double));
	/* Set variables */
	timestep = 0.01;
	m = 1.0;
	kappa = 1.0;
	timestep_sq = timestep * timestep;



	/* Initial conditions */
	/* Set initial displacements and velocites */
	q[0] = 0.1;
	v[0] = 0;

	for (i = 1; i < nbr_of_particles; i++) {
		q[i] = 0;
		v[i] = 0;
	}
	q_1[0] = q[0];
	q_2[0] = q[1];
	q_3[0] = q[2];

	/* Calculate initial accelerations based on initial displacements */
	calc_acc(a, q, m, kappa, nbr_of_particles);

	/* timesteps according to velocity Verlet algorithm */
	for (i = 1; i < nbr_of_timesteps + 1; i++) {
		/* v(t+dt/2) */
		for (j = 0; j < nbr_of_particles; j++) {
		    v[j] += timestep * 0.5 * a[j];
		}

		/* q(t+dt) */
		for (j = 0; j < nbr_of_particles; j++) {
		    q[j] += timestep * v[j];
		}
		potential_energy[i] = calc_pe(q, kappa, nbr_of_particles);
		kinetic_energy[i] = calc_ke(v, nbr_of_particles, m);
		total_energy[i] = potential_energy[i] + kinetic_energy[i];
		/* a(t+dt) */
		calc_acc(a, q, m, kappa, nbr_of_particles);

		/* v(t+dt) */
		for (j = 0; j < nbr_of_particles; j++) {
		    v[j] += timestep * 0.5 * a[j];
		}

		/* Save the displacement of the three atoms */
		q_1[i] = q[0];
		q_2[i] = q[1];
		q_3[i] = q[2];
		q_all[i] = q_1[i] + q_2[i] + q_3[i];
	}
	powerspectrum(q_3, powspec_data, nbr_of_timesteps+1);
	powerspectrum_shift(powspec_data,nbr_of_timesteps+1);
	fft_freq_shift(freq, timestep, nbr_of_timesteps+1);
	/* Print displacement data to output file */
	file = fopen("disp.dat","w");
	file_energy = fopen("energy.dat", "w");
	file_ps = fopen("powerspectrum.dat", "w");

	for (i = 0; i < nbr_of_timesteps + 1; i++) {
		current_time = i * timestep;
		fprintf(file, "%.4f \t %e \t %e \t %e", current_time, q_1[i], q_2[i], q_3[i] );
		fprintf(file, "\n");

		fprintf(file_energy, "%.4f \t %e \t %e \t %e \n", current_time, total_energy[i], potential_energy[i], kinetic_energy[i]);

		fprintf(file_ps, "%e \t %e \n", freq[i], powspec_data[i]);
	}
	fclose(file);

	/* Free allocated memory */
	free(q_1); q_1 = NULL;
	free(q_2); q_2 = NULL;
	free(q_3); q_3 = NULL;
	return 0;
}
