//
//  DITDocumentPath.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 03/02/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#import <Foundation/Foundation.h>

@class DITAttachmentToken;

NS_ASSUME_NONNULL_BEGIN

/**
 Provides an interface to specify a path to a key in a document that you can then call a function
 on to get the value at the specified key as a specific type. You obtain a `DITDocumentPath` by
 subscripting a `DITDocument` and you can then further subscript a `DITDocumentPath` to further
 specify the key of the document that you want to get the value of.
 */
@interface DITDocumentPath : NSObject

/**
 Used to specify a path to a key in the document that you can subscript further to access a
 nested key in the document.

 @param key The next part of the path needed to get to the key in the document you wish to get
 the value of.

 @return The same `DITDocumentPath` object with the provided key incorporated into the document
 path.
 */
- (DITDocumentPath *)objectForKeyedSubscript:(NSString *)key;

/**
 Used to specify an index in the array at the preceding key-path specified through the
 subscripting defined previously. You can subscript the return value further to access a further
 nested key in the document.

 @param index The index of the array that you wish to access in the key previously specified with
 the preceding subscripting.

 @return The same `DITDocumentPath` object with the provided index incorporated into the document
 path.
 */
- (DITDocumentPath *)objectAtIndexedSubscript:(NSUInteger)index;

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
@end

NS_ASSUME_NONNULL_END
