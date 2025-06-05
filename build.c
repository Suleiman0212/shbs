#include "build.h"

// clang-format off

start$
  Const bin = const("sumapp")

  Toolchain cc = tool("clang")
  Flags cflags = flags("-Wall -O2")
  Files csrc = files("src/main.c", "src/sum.c")

  Toolchain ld = tool("clang")
  Const ldflags = flags("")

  Dir outdir = dir("out")
  mkdir(outdir);

  build(cc, cflags, csrc, outdir)
  link(ld, ldflags, csrc, outdir, bin)
  run("./out/sumapp")

end$
