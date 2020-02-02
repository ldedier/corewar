# Corewar

virtual machine arena program and others

## Summary

Core War is a 1984 programming game created by D. G. Jones and A. K. Dewdney in which two or more battle programs (called "warriors") compete for control of a virtual computer. These battle programs are written in an abstract assembly language called Redcode.

* For more informations about Corewar: [its wikipedia page](https://en.wikipedia.org/wiki/24_Game)

# The virtual machine

![oops something went wrong, try to check on https://raw.githubusercontent.com/ldedier/corewar/master/vm_dir/resources/corewar.gif](https://raw.githubusercontent.com/ldedier/corewar/master/vm_dir/resources/corewar.gif)

## Description

This is the arena where cores fight against each other,
The last player receiving a life through the live instruction (opcode 0x1) wins the game

## Usage

**./corewar**  `[-c]` `[-dump nb]` `[-a]` `[-n nb]` `[-v]` `[-w ip host]` **<core1.cor>** `[core2.cor][core3.cor][core4.cor]`

* -v : graphic mode
* -w ip host : connect to the server
* -c : color mode
* -dump nb : Dumps memory after nb cycles then exits
* -n nb	: Attributes number nb to next player
* -a : prints output of each aff instructions

# The assembly compiler

![oops something went wrong, try to check on https://raw.githubusercontent.com/ldedier/corewar/master/asm_dir/resources/asm.gif](https://raw.githubusercontent.com/ldedier/corewar/master/asm_dir/resources/asm.gif)

## Description

This is the program compiling the .s to its matching .cor binary

## Usage

**./asm** **<sourcefile.s>**

# The .cor decompiler

![oops something went wrong, try to check on https://raw.githubusercontent.com/ldedier/corewar/master/decompiler_dir/resources/disass.gif](https://raw.githubusercontent.com/ldedier/corewar/master/decompiler_dir/resources/disass.gif)

## Description

This program disassemble the .cor to its matching .s assembly file

## Usage

**./decompiler** `[-l]` **<core1.cor>**

* -l : try to generates labels when references can be deducted

# The arena server

![oops something went wrong, try to check on https://raw.githubusercontent.com/ldedier/corewar/master/server_dir/resources/server.gif](https://raw.githubusercontent.com/ldedier/corewar/master/server_dir/resources/server.gif)

## Description

This program stores .cor's inside its pseudo database and has its own corewar arena
It attributes a rank to each one of them considering their wins and defeats.

When launching the **corewar** program with -w **IP** **Port** to that server, one can download and upload .cor's from and to the server, as well as looking at their given scores.

### The scoring algorithm 

* compute number of victories of all cores in the server database
* for each core A: for each .cor B that A wins against, add to the score of A the number of victories of B + 1

## Usage

**./scorewar** **<port>**
