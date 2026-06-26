# Saffron programming language
## Introduction
The Saffron programming language is a dynamically-typed, functional, object-oriented language. 

## Installation
Installation only available for UNIX/POSIX systems. Either build from source or download binaries directly (beta). Both ways work fine; however, building from source using `make build` creates an additional copy of `saffron` inside the directory you were in during installation.
### Building from source (POSIX)
#### Requirements
- GCC C++ compiler (at least C++20)
- Make system set up

Run the following commands:
```bash
git clone "https://github.com/zyrikl/saffron"
make build     # You may need to enter your
               # password, don't worry, we
               # are just moving the executable
               # file to the /usr/local/bin
               # section. 
```
Alternatively, for those who are more wary:
```bash
git clone "https://github.com/zyrikl/saffron"
make                            # build the executable
sudo cp ./saffron /usr/local/bin    # copy it over
sudo chmod +x /usr/local/bin/saffron    # finish the job
```

## License
See the license in the `LICENSE` file (wow did not know that).

## Plans
- spices package manager