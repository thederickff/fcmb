## Futronic Cwsq Mindtct Bozorth3 (FCMB)

This project was done to make the life easy for those whom has a futronic device but didn't find a free SDK, or isn't able to pay something like $1000 to get one from Futronic company.

This program communicates with a Futronic device, writes the read finger into a bitmap and extracts its minutiae into a .xyt file.
You can use the included software **Bozorth3** to calculate minutiae scores using .xyt files.

This project uses three softwares of NBIS (NIST Biometric Image Software (National Institute of Standards and Technology)), **Cwsq** (compress a bitmap file into a wsq), **Mindtct** (extracts fingerprint minutiae), and **Bozorth3** (Matches fingerprints minutiae).

Currently, it only makes connection with fs80 and fs88 scanners, but you can try with other Futronic's devices, good lucky!

### Usage
<code>fcmb &lt;directory&gt; &lt;name&gt;</code><br/>

It'll request a finger, then a bitmap image (name.bmp) and a minutiae map file (name.xyt) will be generated on the directory you informed so that you can visualize the finger scanned and use its minutiae with Bozorth3 according with your needs.

## Contributing
Clone the repository, then you gonna need a futronic' scanner, the three programs mentioned above compiled to your platform (See [nbis](https://github.com/lessandro/nbis)), and then you'll be ready for development.
