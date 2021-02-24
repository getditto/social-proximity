//
//  DITLogLevel.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 21/01/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#ifndef DITLogLevel_h
#define DITLogLevel_h

#import <Foundation/Foundation.h>

/**
 The log level types that DittoSyncKit supports.
 */
typedef NS_ENUM(NSUInteger, DITLogLevel) {
    DITLogLevelError = 1,
    DITLogLevelWarning = 2,
    DITLogLevelInfo = 3,
    DITLogLevelDebug = 4,
    DITLogLevelVerbose = 5,
};

#endif
