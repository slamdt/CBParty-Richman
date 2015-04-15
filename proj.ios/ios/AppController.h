//
//  DoTaBattleAppController.h
//  DoTaBattle
//
//  Created by yuyu on 15-3-18.
//  Copyright __MyCompanyName__ 2015年. All rights reserved.
//

@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
}

@property (nonatomic, retain) UIWindow *window;
@property (nonatomic, retain) RootViewController *viewController;

@end

