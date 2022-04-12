# FdF
FdF offers to visualize “iron wire” meshing in 3D. Using MinilibX graphic library.

### Example:
<img width="1000" alt="image" src="https://user-images.githubusercontent.com/52178013/161597136-3fc5f38c-e145-4200-9e9b-785ecd06e2c9.png">

# How to use
### How to install MinilibX
[MinilibX for Mac](https://github.com/erikpeik/FdF/files/8411854/minilibx_mms_20191025_beta.zip)

[MinilibX for Linux](https://github.com/42Paris/minilibx-linux)
- Download MinilibX from links above
- Run Makefile and then copy two files:
  - libmlx.a in /usr/local/lib
  - mlx.h in /usr/local/include
### How to use FdF
- First clone repo: `git clone https://github.com/erikpeik/FdF.git`
- In the folder run `make`, it should compaile if MinilibX is installed correctly.
- You will have executable named `fdf`. 
- For example you can run `./fdf eval_tests/42.fdf`. 
- There is also other maps to try.
