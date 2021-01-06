/*
 * wgrep - uses a naive string search algo, which is still linear in the
 * length of string to be searched (times length of reference string),
 * although will usually be faster do to quick mismatches.

 * If we wanted to be fancy we could use Knuth-Morris_pratt or
 * Boyer-Moore (which is used in actual GNU grep), but this is a warmup
 *
 * Per Skiena (p. 685) this will actually be quite efficient in most cases
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 8192

enum rmode{from_file, from_stdin};

int naive_search(char *search, char *ref);

int main(int argc, char **argv) {
  FILE *fp;
  char buf[MAXLINE];

  if (argc < 2) {
    fprintf(stdout, "wgrep: searchterm [file ...]\n");
    exit(1);
  }

  char *ref = argv[1];

  if (argc == 2) {
    // reading from stdin
    fp = stdin;
    while (fgets(buf, MAXLINE, fp) != NULL) {
      if (naive_search(buf, ref)) {
        fprintf(stdout, "%s", buf);
      }
    }
  } else {
    // iterate over files and perform search
    for (int i = 2; i < argc; i++) {
      if ((fp = fopen(argv[i], "r")) == NULL) {
        fprintf(stdout, "wgrep: cannot open file\n");
        exit(1);
      }

      char *linebuf = NULL;
      size_t linesize = 0;
      while (getline(&linebuf, &linesize, fp) > 0) {
        if (naive_search(linebuf, ref)) {
          fprintf(stdout, "%s", linebuf);
        }
      }

      if (fclose(fp) != 0) {
        fprintf(stderr, "error closing the file\n");
        exit(1);
      }
    }
  }

  return 0;
}

// returns 1 if there exists a match else 0
// seeing if ref is in search
int naive_search(char *search, char *ref) {
  // I'm sure there are ways to do this that avoid using strlen but it's fine
  int reflen = strlen(ref);
  int si = 0, ri = 0;
  while (search[si] != '\0') {
    while (search[si + ri] == ref[ri]) {
      if (ri == reflen - 1)
        return 1;

      if (search[si + ri] == '\0')
        return 0;

      ri++;
    }
    si++;
    ri = 0;
  }
  return 0;
}
