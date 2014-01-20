#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <alloca.h>
#include <errno.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

  int fd = open("/dev/midi1", 0);

  size_t bufSize = 256;
  void *buf = alloca(bufSize);

  while(true) {
    ssize_t nbRead = 0;
    if((nbRead = read(fd,buf,bufSize)) == -1) {
      cerr << "Failed to read, " << strerror(errno) << endl;
      return EXIT_FAILURE;
    }

    unsigned char *bufStr = (unsigned char*) buf;

    for(int idx = 0; idx < nbRead; idx++) {
      cout << hex << (int) bufStr[idx] << " ";
    }

    cout << flush;
  }

}
