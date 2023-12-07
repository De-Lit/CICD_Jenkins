#include "my_grep.h"

int main(int argc, char **argv) {
  pars pars = {0};
  if (!Parser(argc, argv, &pars)) {
    Opener(argc, argv, pars);
  }
  return 0;
}

int Parser(int argc, char **argv, pars *p) {
  if (argc > 1) {
    int opt = '\0';
    while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
      switch (opt) {
        case 'e':
          if (!p->e) {
            strcat(p->e_str, optarg);
          } else {
            strcat(p->e_str, "|\0");
            strcat(p->e_str, optarg);
          }
          p->e = 1;
          break;
        case 'i':
          p->i = 1;
          break;
        case 'v':
          p->v = 1;
          p->o = 0;
          break;
        case 'c':
          p->c = 1;
          break;
        case 'l':
          p->l = 1;
          break;
        case 'n':
          p->n = 1;
          break;
        case 'h':
          p->h = 1;
          break;
        case 's':
          p->s = 1;
          break;
        case 'f':
          p->f = 1;
          p->f_str = optarg;
          break;
        case 'o':
          if (!p->v) {
            p->o = 1;
          }
          break;
        default:
          p->err = opt;
          p->err_value = optopt;
      }
    }
  } else {
    printf("using: my_grep [options] template [file_name]\n");
    p->err = 1;
  }
  return p->err ? 1 : 0;
}

void Opener(int argc, char **argv, pars p) {
  int f_str = optind;
  FILE *mf = my_NULL;
  if (!p.e && !p.f) {
    f_str++;
  }
  regex_t regex = {0};
  if (!MakeRegex(&regex, argv[optind], p)) {
    for (int i = 0; (f_str + i) < argc; i++) {
      mf = fopen(argv[f_str + i], "r");
      if (!mf) {
        if (!p.s) {
          printf("my_grep: %s: No such file or directory\n", argv[f_str + i]);
        }
      } else {
        Print(mf, &regex, p, argc, argv[f_str + i], f_str);
        fclose(mf);
        mf = my_NULL;
      }
    }
  }
  regfree(&regex);
}

int MakeRegex(regex_t *r, char *argv, pars p) {
  int regflag = Flag_i(p);
  int flag_f_err = 0;
  int flag_o = p.o ? 0 : REG_NOSUB;
  if (p.e) {
    regcomp(r, p.e_str, regflag | flag_o | REG_EXTENDED);
  } else if (p.f) {
    char c_char = '\0';
    char c_str[2] = {'\0'};
    char f_buff[1024] = {'\0'};
    FILE *mf = fopen(p.f_str, "r");
    if (!mf) {
      if (!p.s) {
        printf("my_grep: %s: No such file or directory\n", p.f_str);
        flag_f_err = 1;
      }
    } else {
      while ((c_char = getc(mf)) != EOF) {
        c_str[0] = c_char;
        c_str[1] = '\0';
        strcat(f_buff, c_str);
      }
      regcomp(r, f_buff, regflag | flag_o | REG_EXTENDED);
      fclose(mf);
    }
  } else {
    regcomp(r, argv, regflag | flag_o | REG_EXTENDED);
  }
  return flag_f_err ? -1 : 0;
}

void Print(FILE *mf, regex_t *r, pars p, int argc, char *argv, int f_str) {
  int num_str = 0;
  int eq_str = 0;
  char buff[1024] = {'\0'};
  char buff_o[1024] = {'\0'};
  int flag_l_ok = 0;
  int flag_n_ok = 0;
  int flag_h_ok = 0;
  size_t nmatch = 1;
  regmatch_t pmatch[1] = {0};
  while (fgets(buff, 1024, mf) != my_NULL && !p.err && !flag_l_ok) {
    num_str++;
    flag_n_ok = 0;
    flag_h_ok = 0;
    int success = regexec(r, buff, nmatch, pmatch, 0);
    Flag_v(&success, p);
    if (!success) {
      eq_str++;
      do {
        if (p.l) {  // Flag "-l"
          flag_l_ok = 1;
          break;
        }
        if (!p.c && !p.h && (argc - f_str - 1) && !flag_h_ok) {  // !Flag "-h"
          printf("%s:", argv);
          flag_h_ok = 1;
        }
        if (!p.c && p.n && !flag_n_ok) {  // Flag "-n"
          printf("%d:", num_str);
          flag_n_ok = 1;
        }
        if (!p.c && p.o) {  // Flag "-o"
          strncpy(buff_o, &buff[pmatch[0].rm_so],
                  pmatch[0].rm_eo - pmatch[0].rm_so);
          strcat(buff_o, "\n\0");
          printf("%s", buff_o);
          memset(buff_o, '\0', strlen(buff_o));
        }
        if (!p.c && !p.o) {
          printf("%s", buff);
          if (buff[strlen(buff) - 1] != '\n') {
            printf("\n");
          }
        }
        if (p.o) {
          strcpy(buff_o, &buff[pmatch[0].rm_eo]);
          success = regexec(r, buff_o, nmatch, pmatch, 0);
          memset(buff, '\0', strlen(buff_o));
          strcat(buff, buff_o);
          memset(buff_o, '\0', strlen(buff_o));
        }
      } while (!success && p.o);
    }
    memset(buff, '\0', strlen(buff));
  }
  if (p.c) {  // Flag "-c"
    if (!p.h && (argc - f_str - 1)) {
      printf("%s:", argv);
    }
    printf("%d\n", eq_str);
  }
  if (p.l && flag_l_ok) {
    printf("%s\n", argv);
  }
}

void Flag_v(int *s, pars p) {
  if (p.v && !p.o) {
    *s = !*s;
  }
}

int Flag_i(pars p) {
  int s = 0;
  if (p.i) s = REG_ICASE;
  return s;
}
