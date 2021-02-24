//
//  DITMutableDocument.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 31/01/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#import <Foundation/Foundation.h>

@class DITMutableDocumentPath;

NS_ASSUME_NONNULL_BEGIN

/**
 A representation of a `DITDocument` that provices access to an update API through a subscripting
 API that specifies the key in the document to be updated.

 A `DITMutableDocument` object is used as part of update operations for a document. It provides
 access to updating a document through a subscript-based API. A subscript operation returns a
 `DITMutableDocumentPath` that you can then use to chain further subscript operations to in order to
 access nested values in a document. Once you've defined the path to a key in a document that you'd
 like to update, by using subscripts, then you can use the functionality defined on
 `DITMutableDocumentPath` to perform the desired document update(s).

 Note that objects of this type should only be used within the scope of the update closure that they
 are provided in.
 */
@interface DITMutableDocument : NSObject

/**
 The ID of the document.
 */
@property (nonatomic, readonly) NSString *id;

/**
 The document's inner value.
 */
@property (nonatomic, readonly) NSDictionary<NSString *, id> *value;

/**
 Used to specify a path to a key in the document that you can subscript further to access a nested
 key in the document or perform an update operation on it immediately.

 @param key The initial part of the path needed to get to the key in the document you wish to
 update.

 @return A `DittoMutableDocumentPath` object with the provided key incorporated into the
 path.
 */
- (DITMutableDocumentPath *)objectForKeyedSubscript:(NSString *)key;

@end

NS_ASSUME_NONNULL_END
