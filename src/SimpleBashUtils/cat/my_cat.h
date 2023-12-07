#ifndef CICDGITLAB_SIMPLEBASHUTILS_CAT_MYCAT_H_
#define CICDGITLAB_SIMPLEBASHUTILS_CAT_MYCAT_H_

#include <stdio.h>
#include <string.h>

#define my_size_t unsigned long long
#define my_NULL (void *)0

#if defined(__linux__)
#define FLAG 1
#elif defined(__APPLE__) || defined(__MACH__)
#define FLAG 2
#endif

typedef struct {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
  int E;
  int T;
  int err;
  int err_value;
} pars;

int FindPath(int, char **);
int Print(FILE *, pars);
int Parser(int, char **, pars *);
void Flag_b(char, char, pars);
void Flag_e(char *, pars);
void Flag_n(char, char, pars);
void Flag_s(FILE *, char *, char, pars);
void Flag_t(char *, pars);
void Flag_v(char *, pars);

#endif  // CICDGITLAB_SIMPLEBASHUTILS_CAT_MYCAT_H_
