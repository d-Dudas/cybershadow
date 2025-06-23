# Echoes from the Drive

## Extract files from the image

- To extract the files from image.iso, we can simply mount it and copy-paste the content
  - extracted:
    - data1.bin
    - data2.bin
    - data3.bin
    - data4.bin
    - data5.bin

In order to see what is each file, I will use the `file` command from WSL:

- data1.bin:   data
- data2.bin:   7-zip archive data, version 0.4
- data3.bin:   PE32+ executable for MS Windows 10.00 (GUI), x86-64, 8 sections
- data4.bin:   Microsoft Word 2007+
- data5.bin:   PC bitmap, Windows 3.x format, 1927 x 1080 x 24, image size 6246720, resolution 2835 x 2835 px/m, cbSize 6246774, bits offset 54

### data1.bin

- [brute force](./dexor.py) and save every decrypted version
- give each file to the `file` command and look for a relevant result
- there was a zip for key: 0x62 0x30
- there were two files:
  - data1.bin -> I'd tell you a joke about a buffer overflow... but you might not be able to handle it.%
  - data2.bin -> (meme) Do you know what the T stands for in model T? Aliens

### data2.bin

- since this is a 7zip archive, I can simply unzip it using `7z x data2.bin`
- we extracted another file "data1.bin", that is a ISO Media, MP4 Base Media v1 [ISO 14496-12:2003]
- let's rename it `mv data1.bin data.mp4` and we can enjoy the WTF news

### data3.bin

- this seems to be an executable, but when trying `binwalk -e data3.bin`, we can extract some images
  - 2C490/image.png
  - 40568/image.png
  - 786A8/image.png
  - 83328/image.png
  - 97400/image.png
  - A80B8/image.png
  - BC190/image.png
  - CE650/image.png

### data4.bin

- since this is a Microsoft Word 2007+ document, we can simply `cp data4.bin data4.docx` and open it, **BUT** we can also `binwalk -e data4.bin` and extract two folders:
  - 0 -> the actual Microsoft Word document
  - 9940 -> a Microsoft PowerPoint document

### data5.bin

- tried binwalk, no success
- tried steghide, no success
- tried zsteg:
  - text: *"We don't do late submissions... we do denial of service on deadlines."*
  - file: Targa image data - RGBA 1290 x 514 x 1 +259 +512 - 3-bit alpha "\001"
  - file: OpenPGP Public Key
  - file: Applesoft BASIC program data, first line number 138

## [Extracted files](./extracted_files.md)