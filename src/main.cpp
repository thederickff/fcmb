#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "ftrScanAPI.h"

#include "bitmap_write.h"

// Show the Message
void ShowMsg(unsigned long nErrCode)
{
    switch( nErrCode ) 
	{
    case 0:
        std::cout << "OK";
        break;
    case FTR_ERROR_EMPTY_FRAME:	// ERROR_EMPTY
        std::cout << "- Empty frame -\n";
        break;
    case FTR_ERROR_MOVABLE_FINGER:
        std::cout << "- Movable finger -\n";
        break;
    case FTR_ERROR_NO_FRAME:
        std::cout <<  "- No frame -\n";
        break;
    case FTR_ERROR_USER_CANCELED:
        std::cout << "- User canceled -\n";
        break;
    case FTR_ERROR_HARDWARE_INCOMPATIBLE:
        std::cout << "- Incompatible hardware -\n";
        break;
    case FTR_ERROR_FIRMWARE_INCOMPATIBLE:
        std::cout << "- Incompatible firmware -\n";
        break;
    case FTR_ERROR_INVALID_AUTHORIZATION_CODE:
        std::cout << "- Invalid authorization code -\n";
        break;
    default:
        std::cout << "Unknown return code - " << nErrCode << "\n";
	}
}

int main(int argc, char *argv[])
{
	if (argc < 3) {
		std::cerr << "Usage:" << std::endl;
		std::cerr << "dftr_scan [option] [file_name]\n" << std::endl;
		std::cerr << "Options:" << std::endl;
		std::cerr << "new\t\tCreate a new fingerprint" << std::endl;
		std::cerr << "compare\t\tCompare with a existing fingerprint\n" << std::endl;
		return 1;
	}
	std::string filename = argv[2];

	void *hDevice;
	FTRSCAN_IMAGE_SIZE ImageSize;
	unsigned char *pBuffer;
	int i;

	hDevice = ftrScanOpenDevice();
	if(hDevice == NULL)
	{
		std::cout << "Failed to open device!\n";
		return -1;
	} 

	if(!ftrScanGetImageSize(hDevice, &ImageSize))
	{
		std::cout << "Failed to get image size\n";
		ftrScanCloseDevice(hDevice);
		return -1;
	}
	else
	{
		std::cout << "Image size is " << ImageSize.nImageSize << "\n";
		pBuffer = (unsigned char *)malloc( ImageSize.nImageSize );
		std::cout << "Please put your finger on the scanner:\n";
		while(1)
		{
			if(ftrScanIsFingerPresent(hDevice, NULL))
				break;
			for(i=0; i<50; i++);	//sleep(1)
		}
		std::cout << "Capturing fingerprint ......\n";
		if(ftrScanGetFrame(hDevice, pBuffer, NULL) )
		{
			std::cout << "Done!\nWriting to file......\n";
			write_bmp_file(pBuffer, ImageSize.nWidth, ImageSize.nHeight, (filename + ".bmp").c_str());
		}
		else {
			std::cout << "Failed to get image:\n";
			ShowMsg(ftrScanGetLastError());
		}
			
		free(pBuffer);
	}

	ftrScanCloseDevice(hDevice);
	
	return 0;
}