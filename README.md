# krusgen
[![The GPL license](https://img.shields.io/badge/license-GPL-blue.svg?style=flat-square)](http://opensource.org/licenses/GPL-3.0)
[![Travis CI](https://img.shields.io/travis/mazaczysko/krusgen/master.svg?style=flat-square)](https://travis-ci.org/mazaczysko/krusgen)

[Krusgen on Launchpad...](https://launchpad.net/krusgen)

`krusgen` is a command line maze generator.

## Installing krusgen

- Add PPA to your system - `sudo add-apt-repository ppa:mazaczysko/krusgen`
- Update software list - `sudo apt-get update`
- Install `krusgen` package - `sudo apt-get install krusgen`

## Usage
`krusgen [OPTIONS]`


Generates a maze of given size, using Kruskal's algorithm.
`Krusgen` can also export the maze into text (`-t`)  or bmp (`-b`) file, if none of the options is used, maze is exported to `stdout` as text.

Supported options:

- `-h` / `--help` - show help message

- `-x` <`positive, odd number`> - define map width, if not used, width is set automatically to 31

- `-y` <`positive, odd number`> - define map height, if not used, height is set automatically to 31

- `-f` / `--frame` - add borders to maze

- `-s` / `--seed` <`seed`> - set random generator's seed

- `-v` / `--version` - displays krusgen version

- `-t` / `--txt` <`filename`> - export maze as text to given filename

- `-b` / `--bmp` <`filename`> - export maze as bitmap (BMP2 format) to given filename

- `-w` / `--wall` <`hex color`> - define wall color in bitmap

- `-a` / `--air` <`hex color`> - define air color in bitmap

- `-W` / `--wallchar` <`character`> - define wall character

- `-A` / `--airchar` <`character`> - define air character
