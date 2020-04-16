#include "llvm/InitializePasses.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Analysis/InlineCost.h"
#include "llvm/Transforms/IPO/Inliner.h"
#include "llvm/IR/CallSite.h"
#include "llvm/Analysis/ProfileSummaryInfo.h"
#include "llvm/Analysis/TargetLibraryInfo.h"
#include "llvm/Analysis/TargetTransformInfo.h"

using namespace llvm;

#define DEBUG_TYPE "f-inline"
//#define MY_GET_INLINE_COST 1

namespace {
  class FunctionInliner : public LegacyInlinerBase {
    InlineParams Params;
    InlineCost *ICA;

  public:
    static char ID;
    FunctionInliner() : LegacyInlinerBase(ID), Params(llvm::getInlineParams()) {
    	initializeFunctionInlinerPass(*PassRegistry::getPassRegistry());
    }
	
    explicit FunctionInliner(InlineParams Params)
       : LegacyInlinerBase(ID), Params(std::move(Params)) {
     initializeFunctionInlinerPass(*PassRegistry::getPassRegistry());
    }

    #ifndef MY_GET_INLINE_COST
    InlineCost getInlineCost(CallSite CS) override {
        Function *Callee = CS.getCalledFunction();
        TargetTransformInfo &TTI = TTIWP->getTTI(*Callee);
 
        bool RemarksEnabled = false;
        const auto &BBs = CS.getCaller()->getBasicBlockList();
        if (!BBs.empty()) {
           auto DI = OptimizationRemark(DEBUG_TYPE, "", DebugLoc(), &BBs.front());
           if (DI.isEnabled())
               RemarksEnabled = true;
        }
        OptimizationRemarkEmitter ORE(CS.getCaller());
 
        std::function<AssumptionCache &(Function &)> GetAssumptionCache =
            [&](Function &F) -> AssumptionCache & {
                return ACT->getAssumptionCache(F);
        };
        return llvm::getInlineCost(
             cast<CallBase>(*CS.getInstruction()), Params, TTI, GetAssumptionCache,
             /*GetBFI=*/None, PSI, RemarksEnabled ? &ORE : nullptr);
    }
    #endif
    #ifdef MY_GET_INLINE_COST
    InlineCost getInlineCost(CallSite CS) {
        Function *Callee = CS.getCalledFunction();
        if (Callee && !Callee->isDeclaration() &&
          CS.hasFnAttr(Attribute::AlwaysInline) &&
          llvm::isInlineViable(*Callee))
            return llvm::InlineCost::getAlways("always inline attribute");
	return InlineCost::getNever("");
    }	
    #endif

    bool runOnSCC(CallGraphSCC &SCC) override;
    void getAnalysisUsage(AnalysisUsage &AU) const override;

 private:
    TargetTransformInfoWrapperPass *TTIWP;
  };
}

char FunctionInliner::ID = 0;

INITIALIZE_PASS_BEGIN(FunctionInliner, "finline", "Function Inlining", false, false)
INITIALIZE_PASS_DEPENDENCY(AssumptionCacheTracker)
INITIALIZE_PASS_DEPENDENCY(CallGraphWrapperPass)
INITIALIZE_PASS_DEPENDENCY(ProfileSummaryInfoWrapperPass)
INITIALIZE_PASS_DEPENDENCY(TargetTransformInfoWrapperPass)
INITIALIZE_PASS_DEPENDENCY(TargetLibraryInfoWrapperPass)
INITIALIZE_PASS_END(FunctionInliner, "finline", "Function Inlining", false, false)
Pass *createFunctionInlinerPass() { return new FunctionInliner(); }

bool FunctionInliner::runOnSCC(CallGraphSCC &SCC) {
   TTIWP = &getAnalysis<TargetTransformInfoWrapperPass>();
   return LegacyInlinerBase::runOnSCC(SCC);
}

void FunctionInliner::getAnalysisUsage(AnalysisUsage &AU) const {
   AU.addRequired<TargetTransformInfoWrapperPass>();
   LegacyInlinerBase::getAnalysisUsage(AU);
}
