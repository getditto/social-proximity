//
//  DITScopedWriteTransaction.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 03/02/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#import <Foundation/Foundation.h>

@class DITWriteTransactionPendingCursorOperation;
@class DITWriteTransactionPendingIDSpecificOperation;

NS_ASSUME_NONNULL_BEGIN

/**
 Exposes functionality that allows you to perform multiple operations on the store within a single
 write transaction.

 A `DITScopedWriteTransaction` is scoped to a specific collection, obtained by calling `scoped` on a
 `DITWriteTransaction`.
 */
@interface DITScopedWriteTransaction : NSObject

/**
 The name of the collection that the scoped write transaction is scoped to.
 */
@property (nonatomic, readonly) NSString *collectionName;

/**
 Inserts a new document into the collection and returns its ID.

 @param content The new document to insert.
 @param error On input, a pointer to an error object. If an error occurs, this pointer
 is set to an actual error object containing the error information. You may specify nil for this
 parameter if you do not want the error information.

 @return The ID of the inserted document, or `nil` if insertion failed.
 */
- (nullable NSString *)insert:(NSDictionary<NSString *, id> *)content
                        error:(NSError *_Nullable __autoreleasing *)error;

/**
 Inserts a new document into the collection and returns its ID.

 @param content The new document to insert.
 @param id The ID to use for the document. If `NULL` then DittoSyncKit will automatically assign an ID.
 @param error On input, a pointer to an error object. If an error occurs, this pointer
 is set to an actual error object containing the error information. You may specify nil for this
 parameter if you do not want the error information.

 @return The ID of the inserted document, or `nil` if insertion failed.
 */
- (nullable NSString *)insert:(NSDictionary<NSString *, id> *)content
                       withID:(nullable NSString *)id
                        error:(NSError *_Nullable __autoreleasing *)error;

/**
 Inserts a new document into the collection and returns its ID.

 @param content The new document to insert.

 @param isDefault Whether or not the data being inserted should be treated as default data or
 not. Set this to `true` if you want to set a default value that you expect to be overwritten by
 other devices in the network. The default value is `false`.
 @param error On input, a pointer to an error object. If an error occurs, this pointer
 is set to an actual error object containing the error information. You may specify nil for this
 parameter if you do not want the error information.

 @return The ID of the inserted document, or `nil` if insertion failed.
 */
- (nullable NSString *)insert:(NSDictionary<NSString *, id> *)content
                    isDefault:(BOOL)isDefault
                        error:(NSError *_Nullable __autoreleasing *)error;

/**
 Insert a document into the scoped collection.

 @param content The document to insert.
 @param id The ID to use for the document. If `NULL` then DittoSyncKit will automatically assign an ID.
 @param isDefault Represents whether or not the data being inserted should be treated as default
 data or not. Set this to `true` if you want to set a default value that you expect to be
 overwritten by other devices in the network. The default value is `false`.

 @return The ID of the inserted document.
 */
- (nullable NSString *)insert:(NSDictionary<NSString *, id> *)content
                       withID:(nullable NSString *)id
                    isDefault:(BOOL)isDefault
                        error:(NSError *_Nullable __autoreleasing *)error;

/**
 Generates a `DITWriteTransactionPendingIDSpecificOperation` with the provided document ID that can
 be used to update, remove, or evict the document.

 @param docID The ID of the document.

 @return A `DITWriteTransactionPendingIDSpecificOperation` that you can chain function calls to to
 update, remove, or evict the document.
 */
- (DITWriteTransactionPendingIDSpecificOperation *)findByID:(NSString *)docID;

/**
 Generates a `DITWriteTransactionPendingCursorOperation` with the provided query that can be used to
 update, remove, or evict documents.

 @param query The query to run against the collection.

 @return A `DITWriteTransactionPendingCursorOperation` that you can use to chain further
 query-related function calls to update, remove, or evict the documents.
 */
- (DITWriteTransactionPendingCursorOperation *)find:(NSString *)query;

/**
 Generates a `DITWriteTransactionPendingCursorOperation` that can be used to update, remove or evict
 documents.

 @return A `DITWriteTransactionPendingCursorOperation` that you can use to chain further
 query-related function calls to update, remove, or evict the documents.
 */
- (DITWriteTransactionPendingCursorOperation *)findAll;

@end

NS_ASSUME_NONNULL_END
