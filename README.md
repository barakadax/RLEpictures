# RLEpictures

RLE format, save, open & create pictures with CLI commanded.<br>
Now works on linux and windows (rewritten and tested in Ubuntu 20.04.4)<br>
To compile with GCC: gcc Struct.h Main.c Initializer.h Initializer.c InternalLogic.h InternalLogic.c ReadWriteFunctions.h ReadWriteFunctions.c CreateDrawing.h CreateDrawing.c -lm -o MAIN<br>
To run: ./MAIN<br>
Example:<br>
<img src="rle_example.png" title="Example" alt="Sample of create_romb"><br>
Command list:<br>
open_rle file_path<br>
open_txt file_path<br>
save_rle file_path<br>
save_txt file_path<br>
create_square size regular/invert<br>
create_triangle size regular/invert<br>
create_romb size regular/invert<br>
print<br>
exit<br>
help
