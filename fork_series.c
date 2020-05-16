#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

#include <errno.h>
#include <semaphore.h>

/*
 * Il programma crea un "albero genealogico di profondità 4
 * in cui ogni padre prima di incrementare *fork_counter aspetta che lo
 * faccia il figlio. I nodi dell'albero rappresentano i fork(), mentre gli archi
 * rappresentano le esecuzioni dei processi padre e figlio..
 * In questo modo a partire dalla radice e dopo ogni fork, andrò ad eseguire solo una
 * metà dell'albero alla volta (il figlio), mettendo l'altra metà in pausa (il padre),
 * garantendo un'accesso sequenziale a *fork_counter
 */



int *fork_counter;


void child_process();

void parent_process();



int main(void) {

	fork_counter = mmap(NULL, // NULL: è il kernel a scegliere l'indirizzo
			sizeof(int), // dimensione della memory map
			PROT_READ | PROT_WRITE, // memory map leggibile e scrivibile
			MAP_SHARED | MAP_ANONYMOUS, // memory map condivisibile con altri processi e senza file di appoggio
			-1, 0); // offset nel file

	if (fork_counter == NULL) {
		perror("fork_counter");
		exit(EXIT_FAILURE);
	}

	switch (fork()) {
	case 0:
		switch (fork()) {
		case 0:

			switch (fork()) {
			case 0:

				switch (fork()) {
				case 0:
					child_process();
					exit(EXIT_SUCCESS);
				case -1:
					perror("fork()");
					exit(EXIT_FAILURE);
				default:

					if (wait(NULL) == -1) {
						perror("wait error");
						exit(EXIT_FAILURE);
					}

					parent_process();
					exit(EXIT_SUCCESS);
				}

			case -1:
				perror("fork()");
				exit(EXIT_FAILURE);

			default:

				if (wait(NULL) == -1) {
					perror("wait error");
					exit(EXIT_FAILURE);
				}

				switch (fork()) {
				case 0:
					child_process();
					exit(EXIT_SUCCESS);
				case -1:
					perror("fork()");
					exit(EXIT_FAILURE);
				default:

					if (wait(NULL) == -1) {
						perror("wait error");
						exit(EXIT_FAILURE);
					}

					parent_process();
					exit(EXIT_SUCCESS);
				}
			}

		case -1:
			perror("fork()");
			exit(EXIT_FAILURE);

		default:

			if (wait(NULL) == -1) {
				perror("wait error");
				exit(EXIT_FAILURE);
			}

			switch (fork()) {
			case 0:

				switch (fork()) {
				case 0:
					child_process();
					exit(EXIT_SUCCESS);
				case -1:
					perror("fork()");
					exit(EXIT_FAILURE);
				default:

					if (wait(NULL) == -1) {
						perror("wait error");
						exit(EXIT_FAILURE);
					}

					parent_process();
					exit(EXIT_SUCCESS);
				}

			case -1:
				perror("fork()");
				exit(EXIT_FAILURE);

			default:

				if (wait(NULL) == -1) {
					perror("wait error");
					exit(EXIT_FAILURE);
				}

				switch (fork()) {
				case 0:
					child_process();
					exit(EXIT_SUCCESS);
				case -1:
					perror("fork()");
					exit(EXIT_FAILURE);
				default:

					if (wait(NULL) == -1) {
						perror("wait error");
						exit(EXIT_FAILURE);
					}

					parent_process();
					exit(EXIT_SUCCESS);
				}
			}
		}

	case -1:
		perror("fork()");
		exit(EXIT_FAILURE);

	default:

		if (wait(NULL) == -1) {
			perror("wait error");
			exit(EXIT_FAILURE);
		}

		switch (fork()) {
		case 0:

			switch (fork()) {
			case 0:

				switch (fork()) {
				case 0:
					child_process();
					exit(EXIT_SUCCESS);
				case -1:
					perror("fork()");
					exit(EXIT_FAILURE);
				default:

					if (wait(NULL) == -1) {
						perror("wait error");
						exit(EXIT_FAILURE);
					}

					parent_process();
					exit(EXIT_SUCCESS);
				}

			case -1:
				perror("fork()");
				exit(EXIT_FAILURE);

			default:

				if (wait(NULL) == -1) {
					perror("wait error");
					exit(EXIT_FAILURE);
				}

				switch (fork()) {
				case 0:
					child_process();
					exit(EXIT_SUCCESS);
				case -1:
					perror("fork()");
					exit(EXIT_FAILURE);
				default:

					if (wait(NULL) == -1) {
						perror("wait error");
						exit(EXIT_FAILURE);
					}

					parent_process();
					exit(EXIT_SUCCESS);
				}
			}

		case -1:
			perror("fork()");
			exit(EXIT_FAILURE);

		default:

			if (wait(NULL) == -1) {
				perror("wait error");
				exit(EXIT_FAILURE);
			}

			switch (fork()) {
			case 0:

				switch (fork()) {
				case 0:
					child_process();
					exit(EXIT_SUCCESS);
				case -1:
					perror("fork()");
					exit(EXIT_FAILURE);
				default:

					if (wait(NULL) == -1) {
						perror("wait error");
						exit(EXIT_FAILURE);
					}

					parent_process();
					exit(EXIT_SUCCESS);
				}

			case -1:
				perror("fork()");
				exit(EXIT_FAILURE);

			default:

				if (wait(NULL) == -1) {
					perror("wait error");
					exit(EXIT_FAILURE);
				}

				switch (fork()) {
				case 0:
					child_process();
					exit(EXIT_SUCCESS);
				case -1:
					perror("fork()");
					exit(EXIT_FAILURE);
				default:

					if (wait(NULL) == -1) {
						perror("wait error");
						exit(EXIT_FAILURE);
					}

					parent_process();
					printf("Sono il padre di tutti: numero di processi %d\n", (*fork_counter));
					exit(EXIT_SUCCESS);
				}
			}
		}
	} //ultimo dei fork
}//quello del main


void child_process() {
	(*fork_counter)++;
}

void parent_process() {
	(*fork_counter)++;
}



