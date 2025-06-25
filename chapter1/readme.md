# Script File Type Detection

## Description

This program detect the type of files based on the magic numbers  
from the file's header.

It takes as input:
-  the path to a [json file](https://www.garykessler.net/software/index.html#filesigs) that contains the list of the magic number of each file type.
- the path to a file/directory that needs to be checked
  - if it's a directory, it will recursively parse it and verify each file from that directory
- (optional) a depth - in case of a directory is given as input, the recursiv search will be limited to this depth

## Usage

```bash
stfd.exe -s <path_to_file_type_map> -i <path_to_input_file> [-d <depth>]
Options:
  -i, --input <path>       Specify the input file path
  -s, --sigs <file>        Specify the file type map file/directory
  -d, --depth <depth>      Specify the search depth (when input path is a directory)
  -h, --help               Show this help message
```

## Example

```bash
.\bin\stfd.exe -s .\script-file-type-detection\resources\file_sigs.json -i chapter1 -d 4
```

## Dependencies

- a C++ compiler

## Note

- this program was developed on Windows and it was not tested on Linux

## [Results](./results.md)
