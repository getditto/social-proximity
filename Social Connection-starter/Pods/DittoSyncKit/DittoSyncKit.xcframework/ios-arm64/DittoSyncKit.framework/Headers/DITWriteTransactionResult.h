//
//  DITWriteTransactionResult.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 22/01/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#import <Foundation/Foundation.h>

@class DITWriteTransactionResultInserted;
@class DITWriteTransactionResultRemoved;
@class DITWriteTransactionResultEvicted;
@class DITWriteTransactionResultUpdated;

/**
 The types of write transaction results.
 */
typedef NS_ENUM(NSUInteger, DITWriteTransactionResultType) {
    DITWriteTransactionResultTypeInserted = 0,
    DITWriteTransactionResultTypeRemoved,
    DITWriteTransactionResultTypeEvicted,
    DITWriteTransactionResultTypeUpdated,
};

NS_ASSUME_NONNULL_BEGIN

/**
 Provides information about the result of an operation on a document that was part of a write
 transaction.

 The write transaction result can be one of the following types:
   * `inserted`
   * `removed`
   * `evicted`
   * `updated`
 */
@interface DITWriteTransactionResult : NSObject

/**
 The ID of the document involved in the operation.
 */
@property (nonatomic, readonly) NSString *docID;

/**
 The name of the collection that the operation took place in.
 */
@property (nonatomic, readonly) NSString *collectionName;

/**
 The type of write transaction result.

 Check this value before using one of `asInserted`, `asRemoved`, `asEvicted`, or `asUpdated` to
 ensure that you get the correct richer write transaction result object.
 */
@property (nonatomic, readonly) DITWriteTransactionResultType type;

/**
 Get the update result's value as a `DITWriteTransactionResultInserted`, if it is of that type.

 @return A `DITWriteTransactionResultInserted` if the value is of that type, otherwise `nil`.
 */
- (nullable DITWriteTransactionResultInserted *)asInserted;

/**
 Get the update result's value as a `DITWriteTransactionResultRemoved`, if it is of that type.

 @return A `DITWriteTransactionResultRemoved` if the value is of that type, otherwise `nil`.
 */
- (nullable DITWriteTransactionResultRemoved *)asRemoved;

/**
 Get the update result's value as a `DITWriteTransactionResultEvicted`, if it is of that type.

 @return A `DITWriteTransactionResultEvicted` if the value is of that type, otherwise `nil`.
 */
- (nullable DITWriteTransactionResultEvicted *)asEvicted;

/**
 Get the update result's value as a `DITWriteTransactionResultUpdated`, if it is of that type.

 @return A `DITWriteTransactionResultUpdated` if the value is of that type, otherwise `nil`.
 */
- (nullable DITWriteTransactionResultUpdated *)asUpdated;

@end

/**
 Represents the write transaction result that will be the value of a `DittoWriteTransactionResult`
 when its `type` is `inserted` and `asInserted` is called on it.
 */
@interface DITWriteTransactionResultInserted : DITWriteTransactionResult
@end

/**
 Represents the write transaction result that will be the value of a `DittoWriteTransactionResult`
 when its `type` is `removed` and `asRemoved` is called on it.
 */
@interface DITWriteTransactionResultRemoved : DITWriteTransactionResult
@end

/**
 Represents the write transaction result that will be the value of a `DittoWriteTransactionResult`
 when its `type` is `evicted` and `asEvicted` is called on it.
 */
@interface DITWriteTransactionResultEvicted : DITWriteTransactionResult
@end

/**
 Represents the write transaction result that will be the value of a `DittoWriteTransactionResult`
 when its `type` is `updated` and `asUpdated` is called on it.
 */
@interface DITWriteTransactionResultUpdated : DITWriteTransactionResult
@end

NS_ASSUME_NONNULL_END
