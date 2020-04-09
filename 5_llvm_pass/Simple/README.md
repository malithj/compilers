# LLVM Pass to Inline Functions 

# Create a Simple LLVM pass
### Development Instructions
Build:

    $ cd compilers/5_llvm_pass
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ cd ..

Run:

    $ clang -S -emit-llvm -Xclang -disable-O0-optnone foo.c
    $ opt -load build/Simple/libSimplePass.* -fsimple -S foo.ll
    
The `-Xclang -disable-O0-optnone` flag ensures that Clang will allow later optimizations even when initially compiling without any. 

### Deployment Instructions (Integration with LLVM)
1. Download the github repository to your place of choosing. 
2. Create a symbolic link from the llvm-project directory to the module.
	```bash
		:~$ ln -s /path_to_folder/Simple /path_to_folder/llvm-project/llvm/lib/Transforms
	```
3. Add the following code snippet to `lib/CMakeLists.txt`.
	```cpp
		add_subdirectory(Simple)
	```
4. Navigate to the top build directory (in your llvm project) and use your make command (gmake/make).
	```bash
		:~$ make
	```
