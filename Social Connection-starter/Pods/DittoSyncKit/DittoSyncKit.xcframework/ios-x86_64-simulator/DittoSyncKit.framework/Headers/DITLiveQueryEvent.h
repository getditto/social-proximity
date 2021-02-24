//
//  DITLiveQueryEvent.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 31/01/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#import <Foundation/Foundation.h>

@class DITDocument;
@class DITLiveQueryMove;

NS_ASSUME_NONNULL_BEGIN

/**
 Describes events delivered by a `DITLiveQuery`.

 Only the first event in a live query's lifetime will have the `isInitial`
 `BOOL` set to `true`. The first event will return empty arrays for all values
 because there can't be any modifications to the set of matching documents for a
 live query if it's the first time event handler is being called.
 */
@interface DITLiveQueryEvent : NSObject

/**
  Whether or not this is the initial event being delivered.
 */
@property (nonatomic, readonly) BOOL isInitial;

/**
 The documents that previously matched the query, before the latest event.
 */
@property (nonatomic, readonly) NSArray<DITDocument *> *oldDocuments;

/**
 The indexes in the array of matching documents that accompany this event, which relate to a
 document that was not in the previous most recent list of matching documents.
 */
@property (nonatomic, readonly) NSArray<NSNumber *> *insertions;

/**
 The indexes in the array `oldDocument`, which relate to a document that was in the previous most
 recent list of matching documents but is no longer a matching document.
 */
@property (nonatomic, readonly) NSArray<NSNumber *> *deletions;

/**
 The indexes in the array of matching documents that accompany this event, which relate to a
 document that has been updated since the previous live query event.
 */
@property (nonatomic, readonly) NSArray<NSNumber *> *updates;

/**
 Objects that describe how documents' positions in the list of matching documents have changed since
 the previous live query event.
 */
@property (nonatomic, readonly) NSArray<DITLiveQueryMove *> *moves;

@end

NS_ASSUME_NONNULL_END
