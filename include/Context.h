#pragma once

#include "ModuleLoader.h"

#include "llvm/IR/Module.h"

#include <map>
#include <set>
#include <string>
#include <vector>

namespace llvm {

class Function;

}

namespace mull {

class Context {
public:
  typedef std::vector<std::unique_ptr<MullModule>> ModuleArrayType;
  typedef ModuleArrayType::iterator iterator;

private:
  ModuleArrayType Modules;
  std::map<std::string, llvm::Function *> FunctionsRegistry;
  std::map<std::string, MullModule *> moduleNameRegistry;
  std::map<llvm::Module *, MullModule *> moduleRegistry;

public:
  void addModule(std::unique_ptr<MullModule> module);

  std::vector<llvm::Function *> getStaticConstructors();
  std::vector<llvm::Function *> getStaticConstructors(std::set<llvm::Module *> modules);

  MullModule *moduleWithIdentifier(const std::string &identifier);
  MullModule *moduleWithIdentifier(const std::string &identifier) const;

  MullModule *mullModuleForLLVMModule(llvm::Module *module);

  ModuleArrayType &getModules() { return Modules; }
  llvm::Function *lookupDefinedFunction(llvm::StringRef FunctionName);
  iterator begin()  { return Modules.begin(); }
  iterator end()    { return Modules.end();   }
};

}
