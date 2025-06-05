/*
 * SHBS - Single Header Build System, primary for SULEKO project
 * Repository - https://github.com/Suleiman0212/shbs
 * License: MIT
 * Copyright (c) 2025 Kirimov Suleiman <kirimov.suleiman@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// clang-format off

#define start$ int main() {
#define end$ return 0; }

#define Toolchain const char *
#define tool(path) path;

#define Flags const char *
#define flags(str) str;

#define Files const char **
#define files(...) (const char *[]) { __VA_ARGS__, NULL };

#define Dir const char *
#define dir(path) path;

#define mkdir(path) { \
  char cmd[256] = {0}; \
  snprintf(cmd, sizeof(cmd), "mkdir -p %s", path); \
  system(cmd); \
}

#define Const const char *
#define const(str) str;

#define BUFFER_SIZE 1024 * 4

#define build(toolchain, flags, files, outdir) { \
  for (int i = 0; files[i] != NULL; i++) { \
    const char *src = files[i]; \
    const char *basename = strrchr(src, '/'); \
    basename = basename ? basename + 1 : src; \
\
    char objname[256]; \
    snprintf(objname, sizeof(objname), "%s", basename); \
    char *dot = strrchr(objname, '.'); \
    if (dot) *dot = '\0'; \
\
    char outpath[512]; \
    snprintf(outpath, sizeof(outpath), "%s/%s.o", outdir, objname); \
\
    char cmd[BUFFER_SIZE]; \
    snprintf(cmd, sizeof(cmd), "%s %s -c %s -o %s", toolchain, flags, src, outpath); \
    printf("Compiling: %s\n", cmd); \
    system(cmd); \
  } \
}

#define link(toolchain, flags, files, outdir, bin) { \
  char cmd[BUFFER_SIZE] = {0}; \
  strcat(cmd, toolchain); \
  strcat(cmd, " "); \
  strcat(cmd, flags); \
  strcat(cmd, " "); \
\
  for (int i = 0; files[i] != NULL; i++) { \
    const char *src = files[i]; \
    const char *basename = strrchr(src, '/'); \
    basename = basename ? basename + 1 : src; \
\
    char objname[256]; \
    snprintf(objname, sizeof(objname), "%s", basename); \
    char *dot = strrchr(objname, '.'); \
    if (dot) *dot = '\0'; \
\
    char outpath[512]; \
    snprintf(outpath, sizeof(outpath), "%s/%s.o", outdir, objname); \
\
    strcat(cmd, outpath); \
    strcat(cmd, " "); \
  } \
\
  strcat(cmd, "-o "); \
  strcat(cmd, outdir); \
  strcat(cmd, "/"); \
  strcat(cmd, bin); \
\
  printf("Linking: %s\n", cmd); \
  system(cmd); \
}

#define run(command) system(command);
