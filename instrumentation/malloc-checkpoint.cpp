// 15-745 Assignment 2: liveness.cpp
// Group: Nishanth Subramanian (nsubram2) and Arjun Ramesh (arjunr2)
////////////////////////////////////////////////////////////////////////////////

#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/IR/Constants.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/CallSite.h"
#include "llvm/IR/IRBuilder.h"
#include "Global.h"


using namespace llvm;
using namespace std;

namespace
{

	class MallocCheckpoint : public FunctionPass
	{
	public:
		static char ID;

		MallocCheckpoint() : FunctionPass(ID) {}

    void insertCheckpoint(Type* type, GlobalVariable* global_cnt, 
          Instruction* location, Value* checkpt_val) {
      IRBuilder<> Builder(location);
      LoadInst* li = Builder.CreateLoad(type, global_cnt, true, ".mem.ld");
      Value* checkpt_casted = Builder.CreateIntCast(checkpt_val, type, false, ".mem.bc");
      Value* add = Builder.CreateAdd(li, checkpt_casted, ".mem.add");
      StoreInst* si = Builder.CreateStore(add, global_cnt);
    }

		virtual bool runOnFunction(Function &F)
		{
      Module* M = F.getParent();
      Type* int64_type = Type::getInt64Ty(M->getContext());
      GlobalVariable* global_cnt = 
        create_int_global(int64_type, "runtime_malloc_ctr", M);

      for (auto &B : F) {
        for (auto &I : B) {
          if (CallInst *CI = dyn_cast<CallInst>(&I)) {
            Function* fun = CI->getCalledFunction();
            if (fun && fun->getName() == "malloc") {
              Value* malloc_size = CI->arg_begin()->get();
              outs() << "Found malloc call\n";
              outs() << "Detected size: " << *malloc_size << "\n";
              
              insertCheckpoint(int64_type, global_cnt, CI, malloc_size);
            }
          }
        }
      }

			// Did not modify the incoming Function.
			return true;
		}

		virtual void getAnalysisUsage(AnalysisUsage &AU) const
		{
			AU.setPreservesAll();
		}
	};

	char MallocCheckpoint::ID = 0;
	RegisterPass<MallocCheckpoint> X("malloc-checkpoint", "15745 MallocCheckpoint");
}
