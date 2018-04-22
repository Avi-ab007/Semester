#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <linux/kd.h>
#include <sys/types.h>
#include <sys/ioctl.h>

#define ERROR -1

void main()
{
      int i;
  int fd;
  int beep = (125 << 16) + 1591; /* This is the default beep. */


      /* To be used as the fd in ioctl(). */
  if ((fd = open("/dev/console", O_NOCTTY)) == ERROR) {
     perror("open");
     exit(ERROR);
  }

  printf("w00w00!\n\n");

      for (i = 0; i <= 25; i++) { 
          if ((ioctl(fd, KDMKTONE, beep)) == ERROR) {
	         perror("ioctl");
         close(fd);
         exit(ERROR);
      }

          beep += 50;
          usleep(150000);
  }

      /* Turn off the tone now. */
      if ((ioctl(fd, KDMKTONE, 0)) == ERROR) {
     perror("ioctl");
     close(fd);
     exit(ERROR);
      }

  close(fd);
}