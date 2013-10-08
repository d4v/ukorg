#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

static int fd = -1;
pthread_cond_t  cond  = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
volatile bool bTap = false;

void tick() {
	static const char clockTick = 0xf8;
	ssize_t nb = 0;

	for(int idx = 0; idx < 24; idx++) {
		if ((nb = write(fd, &clockTick, 1)) == -1) {
			perror("Failed to write");
		}
	}

	printf(".");
}

void *getTap(void*) {

	// set stdin unbuffered
	struct termios term,old;
	tcgetattr(STDIN_FILENO, &old);
	term = old;
	term.c_lflag &= ~ICANON & ~ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);

	while (true) {
		char c = getchar();
		if(c == 'q') {
			break;
		};

		pthread_mutex_lock(&mutex);
		bTap = true;
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
	};

	tcsetattr(STDIN_FILENO, TCSANOW, &old);
	return NULL;
}

int main(void) {

	fd = open("/dev/midi1", O_WRONLY);
	int period_ms = 100; /* 100ms */
	pthread_t thread;

	pthread_create(&thread,NULL,&getTap,NULL);

	while (true) {
		pthread_mutex_lock(&mutex);
		while(!bTap) {
			pthread_cond_wait(&cond,&mutex);
		}
		tick();
		bTap = false;
		pthread_mutex_unlock(&mutex);
	}

	return 0;
}
