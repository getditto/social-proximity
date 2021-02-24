//
//  DITSubscription.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 30/01/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#import <Foundation/Foundation.h>

@class DittoHandleWrapper;

NS_ASSUME_NONNULL_BEGIN

/**
 Used to subscribe to receive updates from remote peers about matching documents.

 While `DITSubscription` objects remain in scope they ensure that documents in the collection
 specified and that match the query provided will try to be kept up-to-date with the latest changes
 from remote peers.
 */
@interface DITSubscription : NSObject

/**
 The query that the subscription is based on.
 */
@property (nonatomic, readonly) NSString *query;

/**
 The name of the collection that the subscription is based on.
 */
@property (nonatomic, readonly) NSString *collectionName;

@end

NS_ASSUME_NONNULL_END
