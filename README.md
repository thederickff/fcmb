## Futronic Cwsq Mindtct Bozorth3 (FCMB)

This program was done to facilitate the life of those whom has a futronic device but didn't find a SDK, or is not able to pay $1000 dollars to get one from Futronic company.

It program communicates with a Futronic device, writes the reading finger into a bitmap and extracts its minutiae into a .xyt file. You can use the included software **Bozorth3** to compare .xyt files.

This project uses three softwares of NIST (National Institute of Standards and Technology), **Cwsq** (compress a bitmap file into a wsq), **Mindtct** (extracts fingerprint minutiae), and **Bozorth3** (Matches fingerprints minutiae).

Currently, it only makes connection with a fs80 scanner, but you can try with others futronics devices, tell me if it works.

### Usage
<code>fcmb [directory] [name]</code><br/>
