#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include <iostream>
/*
int main() {
    int a = 10; //done
    float b=10.0; //done
    char c= "a"; //done
    double d= 1e8;
   //unsigned int x=32221123;
    int *y = &a; 
   // int *arr; 
   // int arr[32]={0}; 
    bool check = true; //done; 

    return a;
}

define i32 @main() {
entry:
  %a = alloca i32
  store i32 10, %a;
  %b = alloca i32 
  store i32 10.0, %b
  %c = alloca i8
  store i8 a, %c 
  %d = alloca i64
  store i32 1e8, %d
  %y = alloca i32 
  store i32 &a, %y
  %check = alloca i8
  store i8 1, %check
  br label ret; 

ret:
i32 %0
}
*/


///in general the store has two argumnet as val and ptr so which value is stored in which ptr space, becuase ptr define the addressspace where that has been saved. 
int main(){

	llvm::LLVMContext Context; 
	llvm::Module *mymodule = new llvm::Module("MyModule", Context);
	
	//general format is Type::getInt<N>Ty(Context) for the integer type 
	//define * single values types* oe the aggregate type as per required in side the Context ;
	//i.below are the iN type 
	llvm::Type *I32 = llvm::Type::getInt32Ty(Context);
	llvm::Type *I8 = llvm::Type::getInt8Ty(Context);
	llvm::Type *VoidTy = llvm::Type::getVoidTy(Context); 
	llvm::Type *F32 = llvm::Type::getFloatTy(Context);
	llvm::Type *F64 = llvm::Type::getDoubleTy(Context); 
	llvm::Type *ptr = llvm::PointerType::getUnqual(Context); 
	llvm::Type *bool_ty = llvm::Type::getInt1Ty(Context); 

	
	//now define the function main with the no attributes for now 
	std::vector<llvm::Type *>args; 
	llvm::FunctionType *fun_ty = llvm::FunctionType::get(I32,args,false); 
	llvm::Function *fun_main = llvm::Function::Create(fun_ty,llvm::Function::ExternalLinkage,"main", mymodule); 
	fun_main->addFnAttr(llvm::Attribute::NoUnwind);
	//now generate the basic block for the named as eneter because there is no if statment there in whole snippet 
	//now same to create the BB
	llvm::BasicBlock *BB = llvm::BasicBlock::Create(Context, "entry", fun_main); 
	
	llvm::IRBuilder<>ir(Context); 

	//now start with the basic block 
	ir.SetInsertPoint(BB);
	
	//now start wuth the instructions
	llvm::Value *i0= ir.CreateAlloca(I32, nullptr, "i0"); 
	llvm::Value *const10 = llvm::ConstantInt::get(I32, 10); 
	ir.CreateStore(const10, i0); //a=10 done;
	llvm::Value *i1= ir.CreateAlloca(F64, nullptr, "i1"); 
	llvm::Value *float_10 = llvm::ConstantInt::get(F32, 10.0); 
	ir.CreateStore(float_10, i1); //b=10.0 donel
	llvm::Value *i2= ir.CreateAlloca(I8, nullptr, "i2"); 
	llvm::Value *char_a = llvm::ConstantInt::get(I8, 'a');
	ir.CreateStore(char_a, i2); //char c = 'a' done 
	llvm::Value *i3 = ir.CreateAlloca(bool_ty, nullptr, "i3"); 
	llvm::Value *check_bool = llvm::ConstantInt::get(bool_ty, 1);
	ir.CreateStore(check_bool, i3); //check=true done 
	llvm::Value *i4 = ir.CreateAlloca(I32, nullptr, "i4"); 
	llvm::Value *unsign_int = llvm::ConstantInt::get(I32, 32221123, false);
	ir.CreateStore(unsign_int, i4);
	
	mymodule->print(llvm::outs(), nullptr);


	return 0;
}
	
	



