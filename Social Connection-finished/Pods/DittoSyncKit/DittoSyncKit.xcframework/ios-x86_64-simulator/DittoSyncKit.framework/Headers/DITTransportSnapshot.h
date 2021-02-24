//
//  DITTransportSnapshot.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 06/02/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Provides information about a given transport at a point in time.
 */
@interface DITTransportSnapshot : NSObject
/**
 A description of the condition that the transport is in.
 */
@property (nonatomic, readonly) NSString *connection_type;

/**
 A list of the site IDs that are in a connecting state for the transport.
 */
@property (nonatomic, readonly) NSArray<NSNumber *> *connecting;

/**
 A list of the site IDs that are in a connected state for the transport.
 */
@property (nonatomic, readonly) NSArray<NSNumber *> *connected;

/**
 A list of the site IDs that are in a disconnecting state for the transport.
 */
@property (nonatomic, readonly) NSArray<NSNumber *> *disconnecting;

/**
 A list of the site IDs that are in a disconneccted state for the transport.
 */
@property (nonatomic, readonly) NSArray<NSNumber *> *disconnected;
@end

NS_ASSUME_NONNULL_END
