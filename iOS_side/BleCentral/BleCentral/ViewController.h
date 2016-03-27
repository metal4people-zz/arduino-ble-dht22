//
//  ViewController.h
//  BleCentral
//
//  Copyright (c) 2016 Taras Sich. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "BLE.h"

@interface ViewController : UIViewController < BLEDelegate>
{
    BLE *bleShield;
    UIActivityIndicatorView *activityIndicator;
}

@property (nonatomic, weak) IBOutlet UILabel * temperature_label;
@property (nonatomic, weak) IBOutlet UILabel * humidity_label;
@end
