#ifndef CICDGITLAB_SIMPLEBASHUTILS_GREP_MYGREP_H_
#define CICDGITLAB_SIMPLEBASHUTILS_GREP_MYGREP_H_

#include <getopt.h>
#include <regex.h>
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
  int e;
  char e_str[1024];
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  char *f_str;
  int o;
  int err;
  int err_value;
} pars;

int Parser(int, char **, pars *);

void Opener(int, char **, pars);

void Print(FILE *, regex_t *, pars, int, char *, int);

int MakeRegex(regex_t *, char *, pars);

void Flag_v(int *, pars);

int Flag_i(pars);

#endif  // CICDGITLAB_SIMPLEBASHUTILS_GREP_MYGREP_H_
