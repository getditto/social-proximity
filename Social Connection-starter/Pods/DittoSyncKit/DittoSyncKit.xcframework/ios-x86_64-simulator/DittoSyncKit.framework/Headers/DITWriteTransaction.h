//
//  DITWriteTransaction.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 22/01/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#import <Foundation/Foundation.h>

@class DITScopedWriteTransaction;

NS_ASSUME_NONNULL_BEGIN

/**
 Exposes functionality that allows you to perform multiple operations on the store within a single
 write transaction.

 You must use the `scoped` method to get collection-scoped access to the write transaction object,
 which will then allow you to perform insert, update, remove or evict operations using the write
 transaction.
 */
@interface DITWriteTransaction : NSObject

/**
 Creates a `DITScopedWriteTransaction` object that will ensure that operations called on it are all
 in the context of the collection name provided.

 You can create many `DITScopedWriteTransaction` objects per `DITWriteTransaction` object.

 @param collectionName The name of the collection that the write transaction object should be scoped
 to.

 @return A `DITScopedWriteTransaction` that is scoped to the specified collection.
 */
- (DITScopedWriteTransaction *)scopedToCollectionNamed:(NSString *)collectionName;

/**
 Returns a reference to a  `DITScopedWriteTransaction` object that will ensure that operations called on it are all
 in the context of the collection name provided.

 You can create many `DITScopedWriteTransaction` objects per `DITWriteTransaction` object.

 @param collectionName The name of the collection that the write transaction object should be scoped
 to.
 @return Returns a `DITScopedWriteTransaction`
 */
- (DITScopedWriteTransaction *)objectForKeyedSubscript:(NSString* )collectionName;

@end

NS_ASSUME_NONNULL_END
