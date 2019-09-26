#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <string.h>


#define usage "Usage: really_renice nicelevel pid..."



char buffer[512];

int main(int argc, char **argv){
  setuid(0);	
	setgid(0);
  
  stdout = stderr;
  
  int status = 0;
  
  if (argc < 3){
    puts(usage);
    return EINVAL;
  }
  char *Nice = argv[1];
  long pid;
  FILE *Seriously;
#define errcheck if (errno != 0){ status = errno; printf("Failed for PID %li:%s\n",pid,strerror(status)); continue; }

  for (int i = 2; i < argc; i++){
    errno = 0;
    pid = atol(argv[i]);
    errcheck
    sprintf(buffer,"/proc/%li/autogroup",pid);
    errcheck
    Seriously = fopen(buffer,"w");
    errcheck
    fputs(Nice,Seriously);
    errcheck
    fclose(Seriously);
    errcheck
    setpriority(PRIO_PROCESS,(id_t)pid,atoi(Nice));
    errcheck
  }
  return status;
}