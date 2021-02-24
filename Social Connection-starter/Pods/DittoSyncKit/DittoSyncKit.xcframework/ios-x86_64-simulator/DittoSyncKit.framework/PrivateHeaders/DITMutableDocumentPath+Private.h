//
//  DITMutableDocumentPath+Private.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 03/02/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#import <DittoSyncKit/DITMutableDocumentPath.h>

#import "dittoffi.h"

@class DITUpdateResult;

NS_ASSUME_NONNULL_BEGIN

struct Ditto_Document;

@interface DITMutableDocumentPath ()
@property (nonatomic, readonly, unsafe_unretained) CDocument_t *documentHandle;
@property (nonatomic, readonly) NSString *docID;
@property (nonatomic, readwrite) NSString *path;
@property (nonatomic, readonly) NSMutableArray<DITUpdateResult *> *results;

/**
 Constructs a new initial `DITMutableDocumentPath` for a document.

 @param documentHandle A pointer to the Rust `Ditto_Document`.
 @param documentID The ID of the `DITMutableDocument` to which this path corresponds.
 @param initialPath The key for the initial path into the document. This must
 always be a string key (i.e. a map key) rather than an array index as every
 top level `DITMutableDocument` is a map. The `initialPath` will be sanitized within
 the constructor.
 @param results A reference to the `results` property of the `DITMutableDocument`
 itself. Any modification to this property will modify the singular `results` object
 for the document. The reference semantics are by design so that update results are
 collected in one place in the event that mutations are performed by several different
 `DITMutableDocumentPath`s on the same `DITMutableDocument`.
 */
+ (instancetype)mutableDocumentPathWithDocumentHandle:(CDocument_t *)documentHandle
                                           documentID:(NSString *)documentID
                                          initialPath:(NSString *)initialPath
                                              results:(NSMutableArray *)results;

/**
 Constructs a new `DITMutableDocumentPath` from an existing `DITMutableDocumentPath`
 by appending another path component.

 @param documentPath The existing document path. All values will be copied except for
 the `results` property which references the `results` property of corresponding
 `DITMutableDocument`. The reference semantics are by design so that update results are
 collected in one place in the event that mutations are performed by several different
 `DITMutableDocumentPath`s on the same `DITMutableDocument`.
 @param component The path component to append. It should already be in sanitized form.
 */
+ (instancetype)mutableDocumentPathFrom:(DITMutableDocumentPath *)documentPath
                     appendingComponent:(NSString *)component;

#pragma mark - Swift Compatibility

// These versions of the document update functions exist so that the Swift SDK wrapper can call them
// and not have the update results be managed by the Objective-C side of things. This is because the
// Swift SDK's representation of update results wants to be able to work with `Any?` types, which
// don't work nicely with Objective-C.
- (void)setDataNoResultChanges:(nullable NSData *)data isDefault:(BOOL)isDefault;
- (void)replaceWithCounterNoResultChangesAsDefault:(BOOL)isDefault;
- (void)removeNoResultChanges;
- (void)incrementNoResultChanges:(double)amount;
- (void)pushDataNoResultChanges:(nullable NSData *)data;
- (nullable NSData *)popDataNoResultChanges;
- (void)insertNoResultChanges:(nullable NSData *)data;

@end

NS_ASSUME_NONNULL_END
