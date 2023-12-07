#include "my_cat.h"

int main(int argc, char **argv) {
  pars pars = {0};
  Parser(argc, argv, &pars);
  if (!pars.err) {
    FILE *mf = my_NULL;
    if (!FindPath(argc, argv)) {
      Print(stdin, pars);
    } else {
      for (int i = 0; ++i < argc;) {
        if (argv[i][0]) {
          if (!strcmp(argv[i], "-")) {
            Print(stdin, pars);
          } else {
            mf = fopen(argv[i], "r");
            if (!mf) {
              printf("my_cat: %s: No such file or directory\n", argv[i]);
            } else {
              Print(mf, pars);
              fclose(mf);
              mf = my_NULL;
            }
          }
        }
      }
    }
  } else {
    printf("my_cat: illegal option -- %c\n", pars.err_value);
    printf("usage: my_cat [-benstuv] [file ...]\n");
  }
  return pars.err ? 1 : 0;
}

int FindPath(int argc, char **argv) {
  int rez = 0;
  for (int i = 0; ++i < argc;) {
    if (argv[i][0]) {
      rez = 1;
      break;
    }
  }
  return rez;
}

int Parser(int argc, char **argv, pars *p) {
  int count = 1;
  my_size_t i = 0;
  while (count < argc && !p->err) {
    if (argv[count][0] == '-' && argv[count][1] != '\0') {
      if (FLAG == 1) {
        if (!strcmp(argv[count], "--number-nonblank")) {
          memset(argv[count], '\0', strlen(argv[count]));
          strcat(argv[count], "-b");
        }
        if (!strcmp(argv[count], "--number")) {
          memset(argv[count], '\0', strlen(argv[count]));
          strcat(argv[count], "-n");
        }
        if (!strcmp(argv[count], "--squeeze-blank")) {
          memset(argv[count], '\0', strlen(argv[count]));
          strcat(argv[count], "-s");
        }
      }
      while (++i < strlen(argv[count]) && !p->err) {
        if (FLAG == 1) {
          switch (argv[count][i]) {
            case 'E':
              p->E = 1;
              argv[count][i] = 'e';
              break;
            case 'T':
              p->T = 1;
              argv[count][i] = 't';
              break;
          }
        }
        switch (argv[count][i]) {
          case 'b':
            p->b = 1;
            p->n = 0;
            break;
          case 'e':
            p->e = 1;
            p->v = 1;
            break;
          case 'n':
            if (!p->b) p->n = 1;
            break;
          case 's':
            p->s = 1;
            break;
          case 't':
            p->t = 1;
            p->v = 1;
            break;
          case 'v':
            p->v = 1;
            break;
          default:
            p->err = 1;
            p->err_value = argv[count][i];
        }
      }
      memset(argv[count], '\0', strlen(argv[count]));
      i = 0;
    }
    count++;
  }
  return p->err ? 1 : 0;
}

int Print(FILE *mf, pars p) {
  static char printChar = '\0';
  static char lastChar = EOF;
  if (FLAG == 2) {
    printChar = '\0';
    lastChar = EOF;
  }
  while ((printChar = getc(mf)) != EOF) {
    Flag_s(mf, &printChar, lastChar, p);
    Flag_b(printChar, lastChar, p);
    Flag_n(printChar, lastChar, p);
    Flag_t(&printChar, p);
    Flag_e(&printChar, p);
    if (printChar != EOF) {
      printf("%c", printChar);
    } else {
      break;
    }
    lastChar = printChar;
  }
  return 0;
}

void Flag_b(char c, char c_las, pars p) {
  static int count_b = 1;
  if (c_las == EOF) {
    count_b = 1;
  }
  if (p.b && c != '\n' && c != EOF && (c_las == '\n' || c_las == EOF)) {
    printf("%6d\t", count_b++);
  }
}

void Flag_e(char *c, pars p) {
  if (!p.E) {
    Flag_v(c, p);
  }
  if (p.e && *c == '\n') {
    printf("%c", '$');
  }
}

void Flag_n(char c, char c_las, pars p) {
  static int count_n = 1;
  if (c_las == EOF) {
    count_n = 1;
  }
  if (p.n && c != EOF && (c_las == '\n' || c_las == EOF)) {
    printf("%6d\t", count_n++);
  }
}

void Flag_s(FILE *mf, char *c, char c_las, pars p) {
  static int count_s = 0;

  if (p.s && *c == '\n' && count_s && (c_las == '\n' || c_las == EOF)) {
    while (*c == '\n' && *c != EOF) {
      *c = getc(mf);
    }
  } else {
    count_s = 0;
  }

  if (p.s && *c == '\n' && (c_las == '\n' || c_las == EOF)) {
    count_s = 1;
  }
}

void Flag_t(char *c, pars p) {
  if (!p.T) {
    Flag_v(c, p);
  }
  if (p.t && *c == '\t') {
    *c = 'I';
    printf("%c", '^');
  }
}

void Flag_v(char *c, pars p) {
  if (p.v) {
    if (*c >= 0 && *c < 32 && *c != 9 && *c != 10) {
      *c += 64;
      printf("%c", '^');
    }
    if (*c == 127) {
      *c = 63;
      printf("%c", '^');
    }
  }
}
