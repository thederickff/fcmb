## Futronic Cwsq Mindtct Bozorth3 (FCMB)

This program was done to facilitate the life of those whom has a futronic device but didn't find a SDK, or is not able to pay $1000 dollars to get one from Futronic company.

This program communicates with a Futronic device, writes the read finger into a bitmap and extracts its minutiae into a .xyt file. 
You can use the included software **Bozorth3** to calculate minutiaes scores using .xyt files.

This project uses three softwares of NIST (National Institute of Standards and Technology), **Cwsq** (compress a bitmap file into a wsq), **Mindtct** (extracts fingerprint minutiae), and **Bozorth3** (Matches fingerprints minutiae).

Currently, it only makes connection with a fs80 scanner, but you can try with others futronics devices, tell me if it works.

### Usage
<code>fcmb [directory] [name]</code><br/>

It'll request a finger, then a bitmap image (name.bmp) and a minutiae map file (name.xyt) will generated on the directory you informed so you can visualize the finger scanned and use its minutiaes with Bozorth3 according with your needs.

## Contributing
This project was not implemented for linux and unix machines yet. So if you do that, please make a pull request.
