//
//  DITDittoSyncKitDelegate.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 10/02/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#import <DittoSyncKit/DITTransportCondition.h>

NS_ASSUME_NONNULL_BEGIN

/**
 An optional delegate object that can be used to get updates about events occurring that relate to
 the `DITDittoSyncKit` object that the delegate was tied to.
 */
@protocol DITDittoSyncKitDelegate <NSObject>

/**
 Called when the condition of one of the underlying transports that DITDittoSyncKit uses changes.

 @param condition The new condition of the transport.
 @param source The transport source.
 */
- (void)transportConditionChanged:(enum DITTransportCondition)condition
                     forSubsystem:(enum DITConditionSource)source;

@end

NS_ASSUME_NONNULL_END
