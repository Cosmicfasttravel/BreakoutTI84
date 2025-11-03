### What this is
This is a fun, work-in-progress calculator game. Ensure you download the latest release for the most up-to-date bug fixes (Installation guide below).
## 
### Note about releases
- If you want the absolute latest release I would recommend checking below for the source code installation instructions
- The source code has the most up-to-date bug fixes, if you see an important bug on a previous release, chances are that its fixed in the source code
- Also note that I try to release as often as I can
##
### Gameplay:
- Note that this is not the final version, and it is subject to change.
- Note also that this is laggier than the release version
- This is not the latest release version
<img width="320" height="240" alt="apng1" src="https://github.com/user-attachments/assets/069000fb-8983-41d6-a378-42ea01df96e4" />

## Installation Instructions
### Prerequisites:
- Install CE C Libraries (Required)  
Download it here [Libraries](tiny.cc/clibs)
  
- Install a Shell (Required)  
Download it here: [arTIfiCE Shell](https://yvantt.github.io/arTIfiCE/)

### Installing the Program:
1. Download the latest .8xp file from the Releases page
2. Connect your TI-84 Plus CE to your computer
3. Open TI-Connect CE software
4. Transfer the .8xp file to your calculator
5. Launch the program through arTIfiCE or your preferred shell
Important: The program will not work if launched directly from the calculator's program menu—you must use a shell.

## Building from Source
### Prerequisites:
- Install the CE C/C++ Toolchain from the CE-Programming toolchain repository.  
Download it here [Toolchain](https://github.com/CE-Programming/toolchain)  
Read documentation [here](https://ce-programming.github.io/toolchain/index.html)  
- All of the other prerequisites from earlier. 

### Compilation Steps:
1. Open any ide
2. Run cedev.bat to open the toolchain terminal
3. Navigate to your project folder with `cd YOUR_FOLDER_NAME`
4. Then run `make`
5. The build process creates a .8xp file in the bin/ directory
6. Transfer the .8xp file to your calculator or emulator using TI-Connect CE

