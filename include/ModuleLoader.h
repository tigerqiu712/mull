#pragma once

#include "MullModule.h"

#include <string>
#include <vector>

namespace llvm {
  class LLVMContext;
  class Module;
}

namespace mull {

class ModuleLoader {
  llvm::LLVMContext &Ctx;

public:
  ModuleLoader(llvm::LLVMContext &C) : Ctx(C) {}
  virtual ~ModuleLoader() {}

  virtual std::unique_ptr<MullModule> loadModuleAtPath(const std::string &path);

  virtual std::vector<std::unique_ptr<MullModule>>
    loadModulesFromBitcodeFileList(const std::vector<std::string> &path);
};

}
