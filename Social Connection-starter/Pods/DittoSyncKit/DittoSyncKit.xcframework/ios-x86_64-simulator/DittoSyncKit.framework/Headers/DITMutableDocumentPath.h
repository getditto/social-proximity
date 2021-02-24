//
//  DITMutableDocumentPath.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 03/02/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#import <Foundation/Foundation.h>

@class DITAttachmentToken;

NS_ASSUME_NONNULL_BEGIN

/**
 Provides an interface to specify a path to a key in a document that you can then call various
 update functions on. You obtain a `DITMutableDocumentPath` by subscripting a
 `DITMutableDocument` and you can then further subscript a `DITMutbaleDocumentPath` to further
 specify the key of the document that you want to update.
 */
@interface DITMutableDocumentPath : NSObject

/**
 Used to specify a path to a key in the document that you can subscript further to access a
 nested key in the document and eventually perform an update operation on.

 @param key The next part of the path needed to get to the key in the document you wish to
 update.

 @return A `DITMutableDocumentPath` with the provided key incorporated into the path.
 */
- (DITMutableDocumentPath *)objectForKeyedSubscript:(NSString *)key;

/**
 Used to specify an index in the array at the preceding key-path specified through the
 subscripting defined previously. You can subscript the return value further to access a further
 nested key in the document and eventually perform an update operation.

 @param index The index of the array that you wish to access in the key previously specified with
 the preceding subscripting.

 @return A `DITMutableDocumentPath` with the provided index incorporated into the path.
 */
- (DITMutableDocumentPath *)objectAtIndexedSubscript:(NSUInteger)index;

/**
 Returns the value at the previously specified key in the document as an `NSString` if possible,
 otherwise the return value will be `nil`.
 */
@property (nonatomic, readonly, nullable) NSString *string;

/**
 Returns the value at the previously specified key in the document as an `NSString`. If the key
 was invalid the return value will be an empty string.
 */
@property (nonatomic, readonly) NSString *stringValue;

/**
 Returns the value at the previously specified key in the document as a `BOOL` if possible,
 otherwise the return value will be `nil`.
 */
@property (nonatomic, readonly, nullable) BOOL *boolean;

/**
 Returns the value at the previously specified key in the document as a `BOOL`. If the key was
 invalid the return value will be `false`.
 */
@property (nonatomic, readonly) BOOL booleanValue;

/**
 Returns the value at the previously specified key in the document as an `NSInteger` if possible,
 otherwise the return value will be 0.
 */
@property (nonatomic, readonly) NSInteger integerValue;

/**
 Returns the value at the previously specified key in the document as an `NSNumber` if possible,
 otherwise the return value will be `nil`.
 */
@property (nonatomic, readonly, nullable) NSNumber *number;

/**
 Returns the value at the previously specified key in the document as an `NSNumber`. If the key
 was invalid the return value will be an `NSNumber` with a value of 0.
 */
@property (nonatomic, readonly) NSNumber *numberValue;

/**
 Returns the value at the previously specified key in the document as an `NSArray` if possible,
 otherwise the return value will be `nil`.
 */
@property (nonatomic, readonly, nullable) NSArray *array;

/**
 Returns the value at the previously specified key in the document as an `NSArray`. If the key
 was invalid the return value will be an empty array.
 */
@property (nonatomic, readonly) NSArray *arrayValue;

/**
 Returns the value at the previously specified key in the document as an `NSDictionary` if
 possible, otherwise the return value will be `nil`.
 */
@property (nonatomic, readonly, nullable) NSDictionary<NSString *, id> *dictionary;

/**
 Returns the value at the previously specified key in the document as an `NSDictionary`. If the
 key was invalid the return value will be an empty dictionary.
 */
@property (nonatomic, readonly) NSDictionary<NSString *, id> *dictionaryValue;

/**
 Returns the value at the previously specified key in the document as a `DITAttachmentToken` if
 possible, otherwise the return value will be `nil`.
 */
@property (nonatomic, readonly, nullable) DITAttachmentToken *attachmentToken;

/**
 Set a value at the document's key defined by the preceding subscripting.

 @param value The value to set at the subscripting-defined document key.
 @param isDefault Represents whether or not the value should be set as a default value. Set this to
 `true` if you want to set a default value that you expect to be overwritten by other devices in the
 network. The default value is `false`.
 */
- (void)set:(id)value isDefault:(BOOL)isDefault;

/**
 Set a value at the document's key defined by the preceding subscripting.

 @param value The value to set at the subscripting-defined document key.
 */
- (void)set:(id)value;

/**
 Remove a value at the document's key defined by the preceding subscripting. If
 removing an index from an array, any subsequent indexes will be shifted left to
 fill the gap.
 */
- (void)remove;

/**
 Replace a value at the document's key defined by the preceding subscripting with a counter.

 @param isDefault Represents whether or not the value is being replaced with a counter that should
 serve as a default value. Set this to `true` if you want to set a default value that you expect to
 be overwritten by other devices in the network. The default value is `false`.
 */
- (void)replaceWithCounterAsDefault:(BOOL)isDefault;

/**
 Replace a value at the document's key defined by the preceding subscripting with a counter.
 */
- (void)replaceWithCounter;

/**
 Increment a counter at the document's key defined by the preceding subscripting. This will only
 succeed if the value at the subscripting-defined key is a counter.

 @param amount The amount to increment the counter by. This can be a positive or a negative value.
 */
- (void)increment:(double)amount;

/**
 Push a value on to the end of an array at the document's key defined by the preceding subscripting.
 This will only succeed if the value at the subscripting-defined key is an array.

 @param value The value to push on to the array.
 */
- (void)push:(id)value;

/**
 Pop a value off the end of an array at the document's key defined by the preceding subscripting.
 This will only succeed if the value at the subscripting-defined key is an array.

 @return The value popped off from the end of the array.
 */
- (nullable id)pop;

/**
 Inserts a value into an array at the index defined by the preceding subscripting.
 This will only succeed if the value at the subscripting-defined key is an index into an array.

 @param value The value to insert into the array.
 */
- (void)insert:(id)value;

@end

NS_ASSUME_NONNULL_END
