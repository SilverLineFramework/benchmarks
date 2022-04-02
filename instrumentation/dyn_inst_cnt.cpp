#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Analysis/ValueTracking.h"
#include "llvm/Analysis/LoopPass.h"
#include "llvm/Transforms/Utils/ValueMapper.h"
#include "llvm/Transforms/Utils/Cloning.h"

using namespace llvm;
using namespace std;

namespace {
  class DynInstCnt : public FunctionPass {

  public:
    static char ID;

    DynInstCnt() : FunctionPass(ID) { }
			
    virtual bool runOnFunction(Function &F) {

      GlobalVariable *cntr = F.getParent()->getGlobalVariable("cnt");

      for (auto &B : F) {
	unsigned inst_cnt = B.getInstList().size();

	Instruction *first = B.getFirstNonPHI();
	LoadInst *LD = new LoadInst(cntr, ".ict.ld.", first);
	BinaryOperator *BO = BinaryOperator::Create(Instruction::Add, LD,
				    ConstantInt::get(Type::getInt64Ty(F.getParent()->getContext()),
						     inst_cnt) , ".ict.add.", first);

	StoreInst *ST = new StoreInst(BO, cntr, first);
      }

      return true;
    }

    virtual void getAnalysisUsage(AnalysisUsage& AU) const {
      AU.setPreservesCFG();
    }

  private:
  };

  char DynInstCnt::ID = 0;
  RegisterPass<DynInstCnt> X("dyn-inst-cnt",
			     "15745 Dynamic Inst Cnt");
}
