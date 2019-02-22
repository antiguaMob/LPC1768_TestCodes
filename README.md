# LPC1768

LPC1768 is a SoC which has an ARM Cortex M3 microprocessor in it. 

NOTE:
'_basic' is a folder which has the libraries of LPC1768 and all these files have to be present in the same folder as of the other code while burning it onto the chip.
Before running and burning each code do not forget to include all the files of '_basic' in the folder where you are going to run the Makefile to burn it.

Makefile:
The Makefile is a file which defines a set of tasks to be done by considering the files present in a certain folder mentioned in it. It is used to compile and execute a code.
The 'make' utility requires a file, 'Makefile' (or makefile), which defines set of tasks to be executed. You may use 'make' command to compile a program from source code. Most open source projects use make to compile a final executable binary, which can then be installed using the command 'make install'. 'make install' may require sudo permission to execute.

