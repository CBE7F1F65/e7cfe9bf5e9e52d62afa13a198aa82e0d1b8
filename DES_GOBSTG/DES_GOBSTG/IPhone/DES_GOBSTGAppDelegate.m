//
//  DES_GOBSTGAppDelegate.m
//  DES_GOBSTG
//
//  Created by h5nc on 10-10-11.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

#import "DES_GOBSTGAppDelegate.h"
#import "HGEGLView.h"
#include "MainApplicationFunctions.h"
#include "RootViewController.h"

@implementation DES_GOBSTGAppDelegate

@synthesize window;
@synthesize glView;

- (void)applicationDidFinishLaunching:(UIApplication *)application {
	[[NSFileManager defaultManager] changeCurrentDirectoryPath: [[NSBundle mainBundle] resourcePath]];
    
    self.window.rootViewController = [RootViewController new];
    self.window.rootViewController.view = glView;
    [self.window makeKeyAndVisible];

	Application_Init();
	glView.loopInterval = 0;
	Application_SetActive(true);
	[glView startLoop];
	
}


- (void)applicationWillResignActive:(UIApplication *)application {
	glView.loopInterval = -1;
	Application_SetActive(false);
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
	glView.loopInterval = -1;
	Application_SetActive(false);
}



- (void)applicationDidBecomeActive:(UIApplication *)application {
	glView.loopInterval = 0;
	Application_SetActive(true);
}
- (void)applicationWillEnterForeground:(UIApplication *)application {
	glView.loopInterval = 0;
	Application_SetActive(true);
}


- (void)dealloc {
	Application_Quit();
	[window release];
	[glView release];
	[super dealloc];
}

@end

const char * ResourceGetBaseDirectory()
{
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *basePath = ([paths count]>0) ? [paths objectAtIndex:0] : nil;
	return [basePath UTF8String];}

const char * ResourceGetAppDirectory()
{
	NSString *appPath = [[NSBundle mainBundle]resourcePath];
	return [appPath UTF8String];
}

