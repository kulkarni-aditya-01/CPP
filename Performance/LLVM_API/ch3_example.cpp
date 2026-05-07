#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h" 
#include "llvm/IR/IRBuilder.h" 
#include "llvm/Support/raw_ostream.h"
#include <iostream> 



int main(){
	
	//first create the instance of the Context so our module live inside it 
	llvm::LLVMContext Context ;

	//now instance the moduel so we can manipulate the IR ;
	llvm::Module *myModule = new llvm::Module("myModule", Context); 

	//now we have the the list of the types "void , int" 
	llvm :: Type *i32type = llvm::Type:: getInt32Ty(Context) ;
      	llvm :: Type *voidtype = llvm::Type:: getVoidTy(Context); 

	//now we have to insert the extern function such as 
	//extern int baz() ;
	//extern void bar(int) ;
	std:: vector<llvm::Type *>Args_bar = {i32type} ;
	llvm :: FunctionType *baz_ty = llvm::FunctionType:: get(voidtype, {}, false);
	llvm :: FunctionType *bar_ty = llvm::FunctionType:: get(voidtype, Args_bar, false); 
	
	//now we jave just decalre it now we have to insert into the module
	llvm :: Function *baz_f = llvm:: Function:: Create(baz_ty, llvm::Function::ExternalLinkage, "baz", myModule); 
	llvm :: Function *bar_f = llvm:: Function:: Create(bar_ty, llvm::Function::ExternalLinkage, "bar", myModule); 
	//here we have done with the function of the first two now we have ti do the foo and the body of it 
	
	std:: vector<llvm::Type *> Args_foo = {i32type, i32type}; 
	llvm::FunctionType *foo_ty = llvm::FunctionType::get(voidtype, Args_foo, false); 
	llvm:: Function *foo_f = llvm::Function:: Create(foo_ty, llvm::Function::InternalLinkage, "foo", myModule); 

	//Now we have to define the body for it such as a BB, PHINode,......
	llvm::BasicBlock *bb = llvm::BasicBlock::Create(Context, "BB", foo_f);
	llvm::BasicBlock *bb2 = llvm::BasicBlock::Create(Context, "BB2", foo_f);
	llvm::BasicBlock *bb3 = llvm::BasicBlock::Create(Context, "BB3", foo_f); 

	//use the IRBuilder for the build in the basic blcck and its instructions in it 
	llvm::IRBuilder ir(bb); 

	llvm::Value *i= ir.CreateAlloca(i32type);
	llvm::Value *i1= ir.CreateAlloca(i32type); 
	llvm::Value *i2 = ir.CreateAlloca(i32tpe); 
	//this have loaded the argument from the fuinction now store in local SSA form 
	llvm::Value *arg0 = foo_f->getArg(0);
	llvm::Value *arg1 = foo_f->getArg(1); 
	// store a in i and b in i1; 
	ir.CreateStore(arg0, i);
	ir.CreateStore(arg1, i1); 
	
	//now load the values for the final addition 
	llvm::Value *i3 = ir.CreateLoad(i32type, i);
	llvm::Value *i4 = ir.CreateLoad(i32type, i1); 
	//now add the add instruction ;
	llvm::Value *i5 = ir.CreateAdd(i, i1); 
	//now store the var = a+b as i2 = i+i1; 
	ir.CreateStore(i5, i2) ;

	//now the if block which as condition as var == 255 ;
	llvm::Value *const255 = llvm::ConstantInt::get(i32type, 255) ;
	llvm::Value *i6 = ir.CreateICmpEQ(i5, const255);

	//now check the branch where to go ; 
	ir.CreateCondBr(i6, bb2, bb3); 
	
	//now lets inside the if condtion 
	ir.SetInsertPoint(bb2); 
	llvm::Value *i7 = ir.CreateLoad(i32type, i2); 
	
	//now call to the bar(var) function 
	ir.CreateCall(bar_ty, bar_f, {i7});
	
	//now call baz and store it in the llvm ;
	llvm::Value *i8 = ir.CreateCall(baz_ty, baz_f); 
	ir.CreateStore(i8, i3); 

	//now there is no phi node due to no common element after if block
	//now create the next block so if will not correct then there is the next block so now
	ir.CreateBr(bb3);
	//insert the start point in it ;
	ir.SetInsertPoint(bb3);
	llvm::Value *i9 = ir.CreateLoad(i32type, i3); 
	//call the bar on it now 
	ir.CreateCall(bar_ty, bar_f, {i9}); 
	//now terminate it 
	
	ir.CreateRetVoid(); 
	myModule->print(llvm::errs(), nullptr); 
	return 0; 
}

