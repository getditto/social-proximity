//
//  DITDocument.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 29/01/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#import <Foundation/Foundation.h>

@class DITDocumentPath;

NS_ASSUME_NONNULL_BEGIN

/**
 A document belonging to a `DittoCollection` with an inner value.
 */
@interface DITDocument : NSObject

/**
 The ID of the document.
 */
@property (nonatomic, readonly) NSString *id;

/**
 The document's inner value.
 */
@property (nonatomic, readonly) NSDictionary<NSString *, id> *value;

/**
 Used to specify a path to a key in the document that you can subscript further to access a
 nested key in the document.

 @param key The initial part of the path needed to get to the key in the document you wish to get
 the value of.

 @return A `DITDocumentPath` object with the provided key incorporated into the document path.
 */
- (DITDocumentPath *)objectForKeyedSubscript:(NSString *)key;

@end

NS_ASSUME_NONNULL_END
