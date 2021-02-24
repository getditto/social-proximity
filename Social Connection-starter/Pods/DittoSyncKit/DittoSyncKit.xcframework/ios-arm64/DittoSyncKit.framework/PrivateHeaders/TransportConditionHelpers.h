//
//  TransportConditionHelpers.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 29/01/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <DittoSyncKit/DITTransportCondition.h>

#import "dittoffi.h"

NS_ASSUME_NONNULL_BEGIN

@interface TransportConditionHelpers : NSObject

+ (enum DITTransportCondition)DITTransportConditionFromTransportCondition:
    (TransportCondition_t)transportCondition;
+ (NSString *)transportConditionDescription:(enum DITTransportCondition)DITTransportCondition;
+ (enum DITConditionSource)DITConditionSourceFromConditionSource:
    (ConditionSource_t)conditionSource;
+ (NSString *)conditionSourceDescription:(enum DITConditionSource)conditionSource;

@end

NS_ASSUME_NONNULL_END
