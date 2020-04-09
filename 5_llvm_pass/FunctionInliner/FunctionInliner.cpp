#include "llvm/InitializePasses.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

#define DEBUG_TYPE "f-inline"

namespace {
  struct FunctionInliner : public FunctionPass {
    static char ID;
    FunctionInliner() : FunctionPass(ID) {
    	initializeFunctionInlinerPass(*PassRegistry::getPassRegistry());
    }

    void getAnalysisUsage(AnalysisUsage &AU) const override {
        AU.addRequired<LoopInfoWrapperPass>();
    }

    virtual bool runOnFunction(Function &F) {
      errs() << "I saw a function called " << F.getName() << "!\n";
      return false;
    }
  };
}

char FunctionInliner::ID = 0;

INITIALIZE_PASS_BEGIN(FunctionInliner, "finline", "Function Inlining", false, false)
INITIALIZE_PASS_DEPENDENCY(LoopInfoWrapperPass)
INITIALIZE_PASS_END(FunctionInliner, "finline", "Function Inlining", false, false)
Pass *createFunctionInlinerPass() { return new FunctionInliner(); }

