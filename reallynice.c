#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#define usage "Usage: reallynice nicelevel command [args...]"


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
  
  
  argv++;
  char *Nice = *argv++;
  FILE *Seriously = fopen("/proc/self/autogroup","w");
  fputs(Nice,Seriously);
  fclose(Seriously);
  nice(atoi(Nice));
  
  setuid(prev_user);
	setgid(prev_group);
  execvp(*argv,argv);
  
  stdout = stderr;
  puts("failed to execute command!");
  return errno;
}