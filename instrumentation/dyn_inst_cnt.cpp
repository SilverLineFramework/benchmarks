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
      Module* current_module = F.getParent();
      char name[] = "cnt";
      StringRef global_strref(name);
      Type* int64_type = Type::getInt64Ty(current_module->getContext());

      // Get a value 0, 1
      Constant* zero = ConstantInt::get(int64_type, 0);
      Constant* one = ConstantInt::get(int64_type, 1);
      
      GlobalVariable* global_cnt;
      // Create global variable reference
      if ((global_cnt = current_module->getNamedGlobal(global_strref)) == nullptr) {
        Constant* constant = current_module->getOrInsertGlobal(global_strref, int64_type, [&] {
          return new GlobalVariable(*current_module, int64_type, false, GlobalVariable::ExternalLinkage, zero, global_strref);
        });
        global_cnt = dyn_cast<GlobalVariable>(constant);
        global_cnt->setVisibility(GlobalValue::HiddenVisibility);
      }

      for (auto &B : F) {
	      unsigned inst_cnt = B.getInstList().size();

	      Instruction *first = B.getFirstNonPHI();
	      LoadInst *LD = new LoadInst(global_cnt, ".ict.ld.", first);
	      BinaryOperator *BO = BinaryOperator::Create(Instruction::Add, LD,
				    ConstantInt::get(Type::getInt64Ty(F.getParent()->getContext()),
						     inst_cnt) , ".ict.add.", first);

	      StoreInst *ST = new StoreInst(BO, global_cnt, first);
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
