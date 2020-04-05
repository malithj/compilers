# LLVM Pass to Inline Functions 

## Instructions to use
1. Download the github repository to your place of choosing. 
2. Create a symbolic link from the llvm-project directory to the module.
	```bash
		:~$ ln -s /path_to_folder/FunctionInline /path_to_folder/llvm-project/llvm/lib
	```
3. Add the following code snippet to `lib/CMakeLists.txt`.
	```cpp
		add_subdirectory(FunctionInline)
	```
4. Navigate to the top build directory and use your make command (gmake/make).
	```bash
		:~$ make
	```
