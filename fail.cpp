#include "rose.h"

#include <iostream>
#include <sstream>

int main(int argc, char **argv) {
  SgProject *project = frontend(argc, argv);
  int cnt = 0;

  auto files = project->get_files();
  std::for_each(std::begin(files), std::end(files), [&cnt](auto &sgFile) {
    auto sgSrcFile = isSgSourceFile(sgFile);
    if (sgSrcFile == nullptr) {
      return;
    }
    std::stringstream str;
    std::ofstream code;
    Unparser_Opt o;
    SgUnparse_Info info;
    // info.set_current_source_file(sgSrcFile);
    Unparser u(&str, "dummy.c", o);
    u.unparseFile(sgSrcFile, info, sgSrcFile->get_globalScope());

    code.open("Output" + std::to_string(cnt++) + ".c");
    code << str.str();
    code.close();
  });

  return 0;
}
