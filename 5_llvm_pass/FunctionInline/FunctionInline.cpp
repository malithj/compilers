#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
using namespace llvm;

namespace {
  struct FunctionInlinePass : public FunctionPass {
    static char ID;
    FunctionInlinePass() : FunctionPass(ID) {}

    virtual bool runOnFunction(Function &F) {
      errs() << "I saw a function called " << F.getName() << "!\n";
      return false;
    }
  };
}

char FunctionInlinePass::ID = 0;

// Register the pass so `opt -skeleton` runs it.
static RegisterPass<FunctionInlinePass> X("finline", "a function inline pass");
