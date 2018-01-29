## FtrScanReader
Futronic Scanner Fingerprint Reader

This repository contains a example of how to use the ftrScanApi library.

Currently, it only makes connection with a fs80 scanner, read and writes a fingerprint to a bitmap image file.

### Building
There is a zip file with the compiled implementation of ftrScanAPI.h on the <code>res/</code> so you can use to link.

### Usage
<code>ftr_scanner new [filename]</code>

For example:<br/>
<code>ftr_scanner new test</code><br/>
If everything goes well, the scanner will request for a finger and it'll generate a <code>test.bmp</code> image of the finger scanned.
