//
//  DITSingleDocumentLiveQueryEvent.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 31/01/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#import <Foundation/Foundation.h>

@class DITDocument;

NS_ASSUME_NONNULL_BEGIN

/**
 Provides information about a live query event relating to a single document live query.
 */
@interface DITSingleDocumentLiveQueryEvent : NSObject

/**
 Whether or not the event is the initial event delivered as part of an `observe` or `observeLocal`
 call.
 */
@property (nonatomic, readonly) BOOL isInitial;

/**
 The old representation of the document with the relveant document ID.
 */
@property (nonatomic, readonly, nullable) DITDocument *oldDocument;

@end

NS_ASSUME_NONNULL_END
