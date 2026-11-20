# Saffron programming language
## Introduction
The Saffron programming language is a dynamically-typed, functional, object-oriented language. 

## Installation
Installation only available for POSIX-compliant systems. Either build from source or download binaries directly (beta). Both ways work fine; however, building from source using `make build` creates an additional copy of `saffron` inside the directory you were in during installation.
### Building from source (POSIX)
#### Requirements
- GCC C++ compiler (at least C++20)
- Make system set up

Run the following commands:
```bash
git clone "https://github.com/zyrikl/saffron"
cd ./saffron
make build     # You may need to enter your
               # password, don't worry, we
               # are just moving the executable
               # file to the /usr/local/bin
               # section. 
```
Alternatively, for those who are more wary:
```bash
git clone "https://github.com/zyrikl/saffron"
cd ./saffron
make                            # build the executable
sudo cp ./saffron /usr/local/bin    # copy it over
sudo chmod +x /usr/local/bin/saffron    # finish the job
# Optionally run
rm -f ./saffron
# to get rid of the built executable
```

## License
See the license in the `LICENSE` file (wow did not know that). Or, read the license when selecting options in the Saffron executable.

## Plans
- spices package manager