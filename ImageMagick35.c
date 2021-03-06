#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define IM7 

#ifdef IM7
#include <MagickWand/MagickWand.h>
#else
#include <wand/MagickWand.h>
#endif
 
int main(int argc,char **argv) {

    MagickWand *small_sample_wand;
    MagickWand *original_wand;
    MagickWand *comparison_wand;
    
    MagickWand *tmp_wand;
    int c;
    int x = 48;
    char filename[1024];
    
    MetricType metric = RootMeanSquaredErrorMetric;
    double similarity_threshold = 1.0;

    RectangleInfo best_match_offset;
    double similarity = -1;

    MagickWandGenesis(); 
    
    original_wand = NewMagickWand();
    
    MagickSetSize(original_wand, 640, 480);
    MagickReadImage(original_wand, "magick:logo");
    MagickAdaptiveResizeImage(original_wand, 100, 75);
    MagickSetImageAlphaChannel(original_wand, DeactivateAlphaChannel);

    small_sample_wand = CloneMagickWand(original_wand);

    MagickCropImage(small_sample_wand, 25, 25, 50, 50);
    MagickSetImageFormat(small_sample_wand, "png");
    MagickSetImagePage(small_sample_wand, 25, 25, 0, 0);
    MagickVignetteImage(small_sample_wand, 0.25, 0.75, 3, 3);

    comparison_wand = MagickSimilarityImage(
        original_wand,
        small_sample_wand,
#ifdef IM7
        metric,
        similarity_threshold,
#endif
        &best_match_offset, 
        &similarity
    );
 
    printf("Similarity is %f \n", similarity);

    MagickSetImageFormat(comparison_wand, "png");

#ifdef IM7
    MagickWriteImage(comparison_wand, "./IM35_7.png");
#else
    MagickWriteImage(comparison_wand, "./IM35_6.png");
#endif

    printf(
        "Width: %d Height: %d x: %d, y: %d\n",
        best_match_offset.width,
        best_match_offset.height,
        best_match_offset.x,
        best_match_offset.y
    );


    //For IM7 compiled from master output is:
    // Similarity is 0.764258 
    // Width: 25 Height: 25 x: 0, y: 0
    //
    // For IM6 compiled from head of the IM6 branch 
    // Similarity is 0.558027 
    // Width: 25 Height: 25 x: 50, y: 50

    

    MagickWandTerminus();
    return (0);
}

// Both were compiled with:
//
// ./configure --with-quantum-depth=16 \
//           --with-magick-plus-plus=no \
//           --without-perl \
//           --disable-static \
//           --exec-prefix=/usr/sbin \
//           --disable-hdri \
//           --disable-docs \
//           --disable-openmp 

