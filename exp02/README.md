# MC504 - 2019s2
## Exp 02

### Build
To build the PATV (Physical Address Translation Viewer) just run make in the exp02
root directory. The executable "patv" will be generated.

### Running
To run PATV simply executes (e.g. `./patv`) the executable.

### Input
The input must be the process to have the pages translated. For correct output, running
as root is strongly recommended.

### Output
The output is the list of non present pages and the list of present pages (in RAM).
For a non present page, if it's in swap, "SWAPPED" will be printed after the virtual page value. 
