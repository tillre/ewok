#import "ImageLoader.h"

#import <UIKit/UIKit.h>
#import "Log.h"
#import "OpenGLUtil.h"


@implementation ImageLoader

+(ewok::Image*)loadImage:(NSString*)path
{
  CGBitmapInfo info;            // CGImage component layout info
  CGColorSpaceModel colormodel; // CGImage colormodel (RGB, CMYK, paletted, etc)

  CGImageRef image = [UIImage imageWithContentsOfFile: path].CGImage;
  if (!image) {
    LogError << "Error loading CGImage: " << [path UTF8String];
    return NULL;
  }
  
  // Parse CGImage info
  info       = CGImageGetBitmapInfo(image);		// CGImage may return pixels in RGBA, BGRA, or ARGB order
  colormodel = CGColorSpaceGetModel(CGImageGetColorSpace(image));
  size_t bpp = CGImageGetBitsPerPixel(image);
  if (bpp < 8 || bpp > 32 ||
      (colormodel != kCGColorSpaceModelMonochrome && colormodel != kCGColorSpaceModelRGB))
    {
      // This loader does not support all possible CGImage types, such as paletted images
      LogError << "CGImage is of wrong type: " << [path UTF8String];
      return NULL;
    }
  unsigned components = bpp>>3;
  unsigned rowBytes   = CGImageGetBytesPerRow(image);	// CGImage may pad rows
  unsigned rowPixels  = rowBytes / components;
  unsigned imgWide    = rowPixels; // CGImageGetWidth(image);
  unsigned imgHigh    = CGImageGetHeight(image);
  ewok::Image::Format format;

  // Choose OpenGL format
  switch(bpp) {
  default:
    Assert(0, "Unknown CGImage bpp");
  case 32: {
    switch(info & kCGBitmapAlphaInfoMask) {
    case kCGImageAlphaPremultipliedFirst:
    case kCGImageAlphaFirst:
    case kCGImageAlphaNoneSkipFirst:
      format = ewok::Image::BGRA; // GL_BGRA;
      break;
    default:
      format = ewok::Image::RGBA; //GL_RGBA;
    }
    break;
  }
  case 24:
    format = ewok::Image::RGB;
    break;
  case 16:
    format = ewok::Image::LUMINANCE_ALPHA;
    break;
  case 8:
    format = ewok::Image::LUMINANCE;
    break;
  }

  LogInfo << "Image format is: " << ewok::GLFormatName(format);

  // Get a pointer to the uncompressed image data.
  //
  // This allows access to the original (possibly unpremultiplied) data, but any manipulation
  // (such as scaling) has to be done manually. Contrast this with drawing the image
  // into a CGBitmapContext, which allows scaling, but always forces premultiplication.
    
  CFDataRef data = CGDataProviderCopyData(CGImageGetDataProvider(image));
  Assert(data, "Cannot get provider from image");

  size_t pixelsSize = CFDataGetLength(data);
  unsigned char *pixels = new unsigned char[pixelsSize];

  // create another copy...maybe this can be done better
  CFDataGetBytes(data, CFRangeMake(0, pixelsSize), pixels);
  Assert(pixels, "Pixels are NULL");

  CFRelease(data);
    
  // If the CGImage component layout isn't compatible with OpenGL, fix it.
  // On the device, CGImage will generally return BGRA or RGBA.
  // On the simulator, CGImage may return ARGB, depending on the file format.
  if (format == ewok::Image::BGRA) {
    uint32_t *p = (uint32_t *)pixels;
    int i, num = imgWide * imgHigh;
		
    if ((info & kCGBitmapByteOrderMask) != kCGBitmapByteOrder32Host) {
      LogWarn << "Fixing Image component layout!";
      // Convert from ARGB to BGRA
      for (i = 0; i < num; i++)
        p[i] = (p[i] << 24) | ((p[i] & 0xFF00) << 8) | ((p[i] >> 8) & 0xFF00) | (p[i] >> 24);
    }
  }

  ewok::Image *img = new ewok::Image();
  img->init(imgWide, imgHigh, pixels, pixelsSize, format);
  return img;
}



@end
