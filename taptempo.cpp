#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>


static int fd = -1;
pthread_cond_t  cond  = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
volatile bool bTap = false;
static const long default_period_ns = 41666667; /* 60bpm, 24 ticks/beat => 1/24 */
volatile long period_ns = default_period_ns;

void tick() {
  static const char clockTick = 0xf8;
  ssize_t nb = 0;

  if ((nb = write(fd, &clockTick, 1)) == -1) {
    perror("Failed to write");
  }
}

#define ONE_SECOND 1000000000 /* 1 second => 1e9 nanosec */
#define TICKSBYBEAT 24 /* 1 tempo tap => 24 ticks */

long getPeriod(const struct timespec *ta, const struct timespec *tb) {
  long delta =   tb->tv_nsec - ta->tv_nsec
               + (tb->tv_sec - ta->tv_sec) * ONE_SECOND;

  return delta / TICKSBYBEAT;
}

void *getTap(void*) {

  // set stdin unbuffered
  struct termios term,old;
  tcgetattr(STDIN_FILENO, &old);
  term = old;
  term.c_lflag &= ~ICANON & ~ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &term);
  struct timespec ta,tb;

  clock_gettime(CLOCK_REALTIME,&ta);

  while (true) {
    char c = getchar();
    if(c == 'q') {
      break;
    };

    clock_gettime(CLOCK_REALTIME,&tb);

    pthread_mutex_lock(&mutex);
    period_ns = getPeriod(&ta,&tb);
    bTap = true;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);

    ta = tb;
  };

  tcsetattr(STDIN_FILENO, TCSANOW, &old);
  return NULL;
}

int main(void) {

  fd = open("/dev/midi1", O_WRONLY);
  pthread_t thread;
  struct timespec ts;

  pthread_create(&thread,NULL,&getTap,NULL);

  while (true) {
    int res = 0;
    pthread_mutex_lock(&mutex);

    while(!bTap) {
      clock_gettime(CLOCK_REALTIME,&ts);

      ts.tv_sec  += period_ns / ONE_SECOND;
      ts.tv_nsec += period_ns % ONE_SECOND;
      if(ts.tv_nsec > ONE_SECOND) {
        ts.tv_sec++;
        ts.tv_nsec -= ONE_SECOND;
      }

      res = pthread_cond_timedwait(&cond,&mutex,&ts);
      if(res == ETIMEDOUT) break;
    }
    tick();
    bTap = false;
    pthread_mutex_unlock(&mutex);
  }

  return 0;
}
