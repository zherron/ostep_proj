#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 8192

int main(int argc, char **argv) {
  FILE *fp;
  char buf[MAXLINE];

  if (argc < 2) {
    exit(0);
  }

  for (int i = 1; i < argc; i++) {
    if ((fp = fopen(argv[i], "r")) == NULL) {
      fprintf(stdout, "wcat: cannot open file\n");
      exit(1);
    }

    while (fgets(buf, MAXLINE, fp) != NULL) {
      fprintf(stdout, "%s", buf);
    }

    if (fclose(fp) != 0) {
      fprintf(stderr, "error closing the file\n");
      exit(1);
    }
  }
  return 0;
}
