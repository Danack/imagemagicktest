//GetImageProperty

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <wand/MagickWand.h>
    
 
void ThrowWandException(MagickWand *wand) {
    char *description; 
    ExceptionType severity; 
    description = MagickGetException(wand, &severity); 
    (void) fprintf(stderr,"%s %s %lu %s\n",GetMagickModule(),description); 
    description=(char *) MagickRelinquishMemory(description); 
    exit(-1); 
}
 

int main(int argc,char **argv) {
    MagickWand *magick_wand;
    MagickBooleanType status;
    const char *result;

	char filename[2048];
	memset(filename, 0, 2048);

//    ImageInfo *image_info;
//    Image *image;
	char *value;
    char *key = "temporary-path";

    MagickWandGenesis();
     
    GetPathTemplate(filename);
	printf("filename is %s\n", filename);

    value = GetImageRegistry(StringRegistryType, key, NULL);

    printf("Value is %s \n", value);
    status = SetImageRegistry(StringRegistryType, key, "/temp/fark", NULL);
    
    value = GetImageRegistry(StringRegistryType, key, NULL);
    printf("Value is %s\n", value);

	GetPathTemplate(filename);
	printf("filename is %s\n", filename);


//    image_info = AcquireImageInfo();
//

//    magick_wand = NewMagickWand();
//
//    status = MagickReadImage(magick_wand, "./images/mask.png");
//    image = GetImageFromMagickWand(magick_wand);
//    //result = InterpretImageProperties(image_info, image, "%@");
//    
//    ResetImagePropertyIterator(image);
//    
//    while((property = GetNextImageProperty(image))) {
//        result = GetImageProperty(image, property);
//        printf("Property: %s value: %s\n", property, result);
//    }

    
    

    //printf("Result is: %s", result);

 //   image_info=DestroyImageInfo(image_info);
 
    MagickWandTerminus();
    
    return 0;
}

