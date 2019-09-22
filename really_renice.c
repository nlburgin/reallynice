#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/resource.h>


#define usage "Usage: really_renice nicelevel pid..."

char buffer[512];

int main(int argc, char **argv){
  if (argc < 3){
    stdout = stderr;
    puts(usage);
    return 1;
  }
  
  const uid_t prev_user = getuid();
  const gid_t prev_group = getgid();
  setuid(0);	
  setgid(0);
  
  char *Nice = *++argv;
  long pid = atol(*++argv);
  sprintf(buffer,"/proc/%li/autogroup",pid);
  FILE *Seriously = fopen(buffer,"w");
  fputs(Nice,Seriously);
  fclose(Seriously);
  setpriority(PRIO_PROCESS,(id_t)pid,atoi(Nice));
  return errno;
}
