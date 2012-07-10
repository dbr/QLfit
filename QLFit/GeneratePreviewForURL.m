#include <CoreFoundation/CoreFoundation.h>
#include <CoreServices/CoreServices.h>
#include <QuickLook/QuickLook.h>

#import <AppKit/NSGraphics.h>
#import <AppKit/NSGraphicsContext.h>
#import <AppKit/NSBezierPath.h>
#import <Foundation/Foundation.h>

#include "stdio.h"
#include "string.h"

#include "fit_wrap.h"



OSStatus GeneratePreviewForURL(void *thisInterface, QLPreviewRequestRef preview, CFURLRef url, CFStringRef contentTypeUTI, CFDictionaryRef options);
void CancelPreviewGeneration(void *thisInterface, QLPreviewRequestRef preview);


BOOL whatsamajig(NSGraphicsContext* context)
{
    // Switch to a nice clean context for drawing
    [NSGraphicsContext saveGraphicsState];
    [NSGraphicsContext setCurrentContext:context];
    
    // Set the line width for a single NSBezierPath object.
    NSBezierPath* thePath = [NSBezierPath bezierPath];
    [thePath setLineWidth:1.0]; // Has no effect.
    [thePath moveToPoint:NSMakePoint(10.0, 10.0)];
    [thePath lineToPoint:NSMakePoint(246.0, 10.0)];
    [thePath setLineWidth:3.0];
    [thePath lineToPoint:NSMakePoint(246.0, 246.0)];
    [thePath lineToPoint:NSMakePoint(10.0, 10.0)];

    
    // Because the last value set is 3.0, all lines are drawn with
    // a width of 3.0, not just the second line.
    [thePath stroke];
    
    //This line sets the context back to what it was when we're done
    [NSGraphicsContext restoreGraphicsState];
    
    return YES;
}


OSStatus GeneratePreviewForURL(void *thisInterface, QLPreviewRequestRef preview, CFURLRef url, CFStringRef contentTypeUTI, CFDictionaryRef options)
{
    NSURL *urlurl = (NSURL*)url;
    NSString *urlstring = [urlurl path];
    const char *urlurlurl = [urlstring cStringUsingEncoding:NSASCIIStringEncoding];
     
    this_is_a_test(urlurlurl);
    
    NSSize canvasSize = NSSizeFromCGSize(CGSizeMake(256.0, 256.0));
    
    CGContextRef cgContext = QLPreviewRequestCreateContext(preview, *(CGSize *)&canvasSize, false, NULL);
    
    if(cgContext) {
        NSGraphicsContext *context = [NSGraphicsContext graphicsContextWithGraphicsPort:(void *)cgContext flipped:YES];
        if(context) {
            whatsamajig(context);
        }
        QLPreviewRequestFlushContext(preview, cgContext);
        CFRelease(cgContext);
    }
    return noErr;
}

void CancelPreviewGeneration(void *thisInterface, QLPreviewRequestRef preview)
{
    // Implement only if supported
}
