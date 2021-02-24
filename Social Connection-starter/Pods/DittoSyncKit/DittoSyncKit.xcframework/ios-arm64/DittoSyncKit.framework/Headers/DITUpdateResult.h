//
//  DITUpdateResult.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 31/01/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#import <Foundation/Foundation.h>

@class DITUpdateResultSet;
@class DITUpdateResultRemoved;
@class DITUpdateResultReplacedWithCounter;
@class DITUpdateResultIncremented;
@class DITUpdateResultPushed;
@class DITUpdateResultPopped;
@class DITUpdateResultInserted;

/**
 The types of update result.
 */
typedef NS_ENUM(NSUInteger, DITUpdateResultType) {
    DITUpdateResultTypeSet = 0,
    DITUpdateResultTypeRemoved,
    DITUpdateResultTypeReplacedWithCounter,
    DITUpdateResultTypeIncremented,
    DITUpdateResultTypePushed,
    DITUpdateResultTypePopped,
    DITUpdateResultTypeInserted,
};

NS_ASSUME_NONNULL_BEGIN

/**
 Provides information about a successful update operation on a document.

 The update result can be one of the following types:
   * `set`
   * `removed`
   * `replacedWithCounter`
   * `incremented`
   * `pushed`
   * `popped`
   * `inserted`
 */
@interface DITUpdateResult : NSObject

/**
 The update result's type.

 Check this value before using one of `asSet`, `asRemoved`, `asReplacedWithCounter`,
 `asIncremented`, `asPushed`, or `asPopped` to ensure that you get the correct richer update result
 object.
 */
@property (nonatomic, readonly) DITUpdateResultType type;

/**
 The ID of the document that was updated.
 */
@property (nonatomic, readonly) NSString *docID;

/**
 The path to the key in the document that was updated.
 */
@property (nonatomic, readonly) NSString *path;

/**
 Return the update result object as a `DITUpdateResultSet` object.

 @return A `DITUpdateResultSet` object or `nil` if the update result's type is not `set`.
 */
- (nullable DITUpdateResultSet *)asSet;

/**
 Return the update result object as a `DITUpdateResultRemoved` object.

 @return A `DITUpdateResultRemoved` object or `nil` if the update result's type is not `removed`.
 */
- (nullable DITUpdateResultRemoved *)asRemoved;

/**
 Return the update result object as a `DITUpdateResultReplacedWithCounter` object.

 @return A `DITUpdateResultReplacedWithCounter` object or `nil` if the update result's type is not
 `replacedWithCounter`.
 */
- (nullable DITUpdateResultReplacedWithCounter *)asReplacedWithCounter;

/**
 Return the update result object as a `DITUpdateResultIncremented` object.

 @return A `DITUpdateResultIncremented` object or `nil` if the update result's type is not
 `incremented`.
 */
- (nullable DITUpdateResultIncremented *)asIncremented;

/**
 Return the update result object as a `DITUpdateResultPushed` object.

 @return A `DITUpdateResultPushed` object or `nil` if the update result's type is not `pushed`.
 */
- (nullable DITUpdateResultPushed *)asPushed;

/**
 Return the update result object as a `DITUpdateResultPopped` object.

 @return A `DITUpdateResultPopped` object or `nil` if the update result's type is not `popped`.
 */
- (nullable DITUpdateResultPopped *)asPopped;

/**
 Return the update result object as a `DITUpdateResultInserted` object.

 @return A `DITUpdateResultInserted` object or `nil` if the update result's type is not `inserted`.
 */
- (nullable DITUpdateResultInserted *)asInserted;

@end

/**
 An update result when the update result's type is `set`.
 */
@interface DITUpdateResultSet : DITUpdateResult

/**
 The value that was set.
 */
@property (nonatomic, readonly, nullable) id value;

@end

/**
 An update result when the update result's type is `removed`.
 */
@interface DITUpdateResultRemoved : DITUpdateResult
@end

/**
 An update result when the update result's type is `replacedWithCounter`.
 */
@interface DITUpdateResultReplacedWithCounter : DITUpdateResult
@end

/**
 An update result when the update result's type is `incremented`.
 */
@interface DITUpdateResultIncremented : DITUpdateResult

/**
 The amount that the counter was incremented by.
 */
@property (nonatomic, readonly) double amount;

@end

/**
 An update result when the update result's type is `pushed`.
 */
@interface DITUpdateResultPushed : DITUpdateResult

/**
 The value that was pushed on to the array.
 */
@property (nonatomic, readonly, nullable) id value;

@end

/**
 An update result when the update result's type is `popped`.
 */
@interface DITUpdateResultPopped : DITUpdateResult

/**
 The value that was popped from the array.
 */
@property (nonatomic, readonly, nullable) id value;

@end

/**
 An update result when the update result's type is `inserted`.
 */
@interface DITUpdateResultInserted : DITUpdateResult

/**
 The value that was inserted into the array.
 */
@property (nonatomic, readonly, nullable) id value;

@end

NS_ASSUME_NONNULL_END
