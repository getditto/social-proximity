//
//  DITCollection.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 22/01/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#import <Foundation/Foundation.h>

@class DITAttachment;
@class DITAttachmentFetcher;
@class DITAttachmentFetchEvent;
@class DITAttachmentToken;
@class DITPendingCursorOperation;
@class DITPendingIDSpecificOperation;

NS_ASSUME_NONNULL_BEGIN

/**
 A reference to a collection in a `DITStore`.

 This is the entrypoint for inserting documents into a collection, as well as
 querying a collection.
 */
@interface DITCollection : NSObject

/**
 The name of the collection.
 */
@property (nonatomic, readonly) NSString *name;

/**
 Inserts a new document into the collection and returns its ID.

 @param content The new document to insert.
 @param error On input, a pointer to an error object. If an error occurs, this pointer
 is set to an actual error object containing the error information. You may specify nil for this
 parameter if you do not want the error information.

 @return The ID of the inserted document, or `nil` if insertion failed.
 */
- (nullable NSString *)insert:(NSDictionary<NSString *, id> *)content
                        error:(NSError *_Nullable *)error;

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
                        error:(NSError *_Nullable *)error;

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
                        error:(NSError *_Nullable *)error;

/**
 Inserts a new document into the collection and returns its ID.

 @param content The new document to insert.
 @param id The ID to use for the document. If `NULL` then DittoSyncKit will automatically assign an ID.
 @param isDefault Whether or not the data being inserted should be treated as default data or
 not. Set this to `true` if you want to set a default value that you expect to be overwritten by
 other devices in the network. The default value is `false`.
 @param error On input, a pointer to an error object. If an error occurs, this pointer
 is set to an actual error object containing the error information. You may specify nil for this
 parameter if you do not want the error information.

 @return The ID of the inserted document, or `nil` if insertion failed.
 */
- (nullable NSString *)insert:(NSDictionary<NSString *, id> *)content
                       withID:(nullable NSString *)id
                    isDefault:(BOOL)isDefault
                        error:(NSError *_Nullable *)error;

/**
 Generates a `DITPendingIDSpecificOperation` with the provided document ID.

 The returned object can be used to find and return the document or you can
 chain a call to `observe`, `observeLocal`, or `subscribe` if you want to get
 updates about the document over time. It can also be used to update, remove
 or evict the document.

 @param docID The ID of the document.

 @return A `DITPendingIDSpecificOperation` that you can chain function calls to either get the
 document immediately or get updates about it over time.
 */
- (DITPendingIDSpecificOperation *)findByID:(NSString *)docID;

/**
 Generates a `DITPendingCursorOperation` using the provided query.

 The returned object can be used to find and return the documents or you can
 chain a call to `observe`, `observeLocal`, or `subscribe` if you want to get
 updates about the list of matching documents over time. It can also be used
 to update, remove or evict the matching documents.

 @param query The query to run against the collection.

 @return A `DITPendingCursorOperation` that you can chain function calls to chain further
 query-related function calls.
 */
- (DITPendingCursorOperation *)find:(NSString *)query;

/**
 Generates a `DITPendingCursorOperation` that relates to all documents in the
 collection.

 The returned object can be used to find and return all of the documents in
 the collection or you can chain a call to `observe`, `observeLocal`, or
 `subscribe` if you want to get  updates about the documents over time. It
 can also be used to update, remove or evict the documents.

 @return A `DITPendingCursorOperation` that you can chain function calls to chain further
 query-related function calls.
 */
- (DITPendingCursorOperation *)findAll;

/**
 Creates a new attachment, which can then be inserted into a document.

 The file residing at the provided path will be copied into DittoSyncKit's store. The `DITAttachment`
 object that is returned is what you can then use to insert an attachment into a document.

 You can provide metadata about the attachment, which will be replicated to
 other peers alongside the file attachment.

 Below is a snippet to how you can use the `newAttachment` functionality to insert an
 attachment into a document.

 ```
 if let attachment = collection.insert.newAttachment("/path/to/my/file.pdf") {
     let docID = try! collection.insert(["attachment": attachment, "other": "string"])
 }
 ```

 @param path The path to the file that you want to create an attachment with.
 @param metadata Metadata relating to the attachment.

 @return A `DITAttachment` object, which can be used to insert the attachment into a document.
 */
- (nullable DITAttachment *)newAttachment:(NSString *)path
                                 metadata:(nullable NSDictionary<NSString *, NSString *> *)metadata;

/**
 Trigger an attachment to be downloaded locally to the device and observe its
 progress as it does so.

 When you encounter a document that contains an attachment the attachment
 will not automatically be downloaded along with the document. You trigger an
 attachment to be downloaded locally to a device by calling this method. It
 will report event relating to the attachment fetch attempt as it tries to
 download it. Assuming it succeeds in downloading the attachment it wall call
 the `onFetchEvent` block with a completed fetch event object, which will hold
 a reference to the attachment.

 @param token The `DITAttachmentToken` relevant to the attachment that you
 wish to download and observe.
 @param onFetchEvent A block that will be called when there is a update to the status of the attachment fetch attempt.

 @return A `DITAttachmentFetcher` object, which must be kept alive for the fetch request to proceed
 and for you to be notified about the attachment's fetch status changes. If the attachment fetcher
 could not be created then `nil` will be returned. This can happen if, for example, an invalid
 attachment token was provided.
 */
- (nullable DITAttachmentFetcher *)fetchAttachment:(DITAttachmentToken *)token
                                      onFetchEvent:(void (^)(DITAttachmentFetchEvent *))onFetchEvent;

@end

NS_ASSUME_NONNULL_END
