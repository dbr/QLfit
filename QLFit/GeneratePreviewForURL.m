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


BOOL whatsamajig(NSGraphicsContext* context, NSArray* points)
{
    // Switch to a nice clean context for drawing
    [NSGraphicsContext saveGraphicsState];
    [NSGraphicsContext setCurrentContext:context];
    
    // Set the line width for a single NSBezierPath object.
    NSBezierPath* thePath = [NSBezierPath bezierPath];
    [thePath setLineWidth:1.0];

    
    float x_min = 400;
    float x_max = -400;
    float y_min = 400;
    float y_max = -400;
    for(NSArray* p in points)
    {
        double x = [[p objectAtIndex:1] doubleValue];
        double y = [[p objectAtIndex:0] doubleValue];
        if(x < x_min)
            x_min = x;
        if(x > x_max)
            x_max = x;
        
        if(y < y_min)
            y_min = y;
        if(y > y_max)
            y_max = y;
    }
    
    NSLog(@"\nx min/max %f %f\ny min/max %f %f", x_min, x_max, y_min, y_max);
    
    double ratio_x = 1;
    double ratio_y = 1;
    if((x_max - x_min) > (y_max - y_min))
    {
        // X is wider
        ratio_x = 1.0;
        ratio_y = (y_max - y_min) / (x_max - x_min);
        NSLog(@"X is wider");
    }
    else
    {
        // Y is wider
        ratio_x = (x_max - x_min) / (y_max - y_min);
        ratio_y = 1.0;
        NSLog(@"Y is wider");
    }
    
    NSLog(@"Ratio x: %f", ratio_x);
    NSLog(@"Ratio y: %f", ratio_y);

    int i = 0;
    for(NSArray* p in points)
    {
        double x = [[p objectAtIndex:1] doubleValue];
        double y = [[p objectAtIndex:0] doubleValue];

        // Normalise to 0-1
        x = ((x-x_min) / (x_max-x_min));
        y = ((y-y_min) / (y_max-y_min));

        // Correct aspect ratio from 1-0 normalisation (otherwise a
        // long rectangle course woudl end up a square, as we fit it)
        x = ratio_x*x;
        y = ratio_y*y;

        // Recentre after aspect ratio fix
        x = x + ((1-ratio_x)/2);
        y = y + ((1-ratio_y)/2);

        // Fix lat-long 2:1 ratio
        x = x / 2.0;
        x = x + 0.25;

        // Border
        x = x * 0.99;
        y = y * 0.99;


        // Scale for screenspace pixel
        x = x * 256;
        y = y * 256;

        NSPoint p = NSMakePoint(x, y);
        //NSLog(@"%f %f", p.x, p.y);
            
        if(i==0)
            [thePath moveToPoint: p];

        [thePath lineToPoint: p];
        ++i;
    }
    
    /*
    [thePath setLineWidth:1.0]; // Has no effect.
    [thePath moveToPoint:NSMakePoint(10.0, 10.0)];
    [thePath lineToPoint:NSMakePoint(246.0, 10.0)];
    [thePath setLineWidth:3.0];
    [thePath lineToPoint:NSMakePoint(246.0, 246.0)];
    [thePath lineToPoint:NSMakePoint(10.0, 10.0)];
     */

    
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
     
    NSArray *points = get_points_from_fitfile(urlurlurl);

    NSSize canvasSize = NSSizeFromCGSize(CGSizeMake(256.0, 256.0));
    
    CGContextRef cgContext = QLPreviewRequestCreateContext(preview, *(CGSize *)&canvasSize, false, NULL);
    
    if(cgContext) {
        NSGraphicsContext *context = [NSGraphicsContext graphicsContextWithGraphicsPort:(void *)cgContext flipped:YES];
        if(context) {
            whatsamajig(context, points);
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
