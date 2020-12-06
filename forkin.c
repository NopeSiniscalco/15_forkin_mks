#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main()
{
	printf("(P-%d) Parent - START\n\n", getpid());
	int f1, f2, status;
	f1 = fork();
	if (f1) //Stop Child from forking
		f2 = fork();
	else
		f1 = 0;

	if (!(f1 && f2))
	{ //Either Child

		//Seed differently for the 2 childs
		if (f1)
			srand(time(NULL));
		else
			srand(time(NULL) * 2);

		int to_wait = (rand() % 9) + 2;
		printf("(C-%d) I'm Child %d - Waiting %ds\n", getpid(), getpid(), to_wait);

		sleep(to_wait);

		printf("(C-%d) I'm Child %d - Finished\n", getpid(), getpid());
		return to_wait;
	}
	//Only Parent:
	int child_exited;
	child_exited = wait(&status);
	//printf("Exit status:%d\n", WEXITSTATUS(status));

	printf("\nI'm Parent - %d - Child %d exited first after %ds\n\n", getpid(), child_exited, WEXITSTATUS(status));

	printf("Waiting for other child to exit as to not mess up terminal format\n");
	child_exited = wait(&status);
	printf("Other Child Exited - Goodbye\n");
	return 0;
}