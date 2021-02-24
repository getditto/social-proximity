//
//  DITPendingIDSpecificOperation.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 29/01/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <DittoSyncKit/DITSignalNext.h>

@class DITDocument;
@class DITLiveQuery;
@class DITMutableDocument;
@class DITSingleDocumentLiveQueryEvent;
@class DITSubscription;
@class DITUpdateResult;

NS_ASSUME_NONNULL_BEGIN

/**
 These objects are returned when using `findByID` functionality on `DITCollection`s.

 You can either call `exec` on the  object to get an immediate return value, or you can establish
 either a live query or a subscription, which both work over time.

 A live query, established by calling `observe`, will notify you every time there's an update to the
 document with the ID you provided in the preceding `findByID` call.

 A subscription, established by calling `subscribe`, will act as a signal to other peers that you
 would like to receive updates from them about the document with the ID you provided in the
 preceding `findByID` call.

 Calling `observe` will generate both a subscription and a live query at the same time.

 If you'd like to only observe local changes then you can call `observeLocal`.

 If you want to observe changes in such a way that you can signal when you're ready for the live
 query to deliver a new update then you can call `observeWithNextSignal` or
 `observeLocalWithNextSignal`.

 Update and remove functionality is also exposed through this object.
 */
@interface DITPendingIDSpecificOperation : NSObject

/**
 Execute the find operation to return the document with the matching ID.

 @return The `DITDocument` with the ID provided in the `findByID` call or `nil` if the document was
 not found.
 */
- (DITDocument *_Nullable)exec;

/**
 Remove the document with the matching ID.

 @return `true` if the document was found and removed. `false` if the document wasn't found and
 therefore wasn't removed.
 */
- (BOOL)remove;

/**
 Evict the document with the matching ID.

 @return `true` if the document was found and evicted. `false` if the document wasn't found and
 therefore wasn't evicted.
 */
- (BOOL)evict;

/**
 Update the document with the matching ID.

 @param block A block that gets called with the document matching the ID. If found, the document is
 a `DITMutableDocument`, so you can call update-related functions on it. If the document is not
 found then the value provided to the block will be `nil`.

 @return A list of `DITUpdateResult`s that describe the updates that were performed on the document.
 */
- (NSArray<DITUpdateResult *> *)updateWithBlock:(void (^)(DITMutableDocument *_Nullable))block;

/**
 Enables you to subscribe to changes that occur in relation to a document remotely.

 Having a subscription acts as a signal to other peers that you are interested in receiving updates
 when local or remote changes are made to the relevant document.

 The returned `DITSubscription` object must be kept in scope for as long as you want to keep
 receiving updates.

 @return A `DITSubscription` object that must be kept in scope for as long as you want to keep
 receiving updates for the document.
 */
- (DITSubscription *)subscribe;

/**
 Enables you to listen for changes that occur in relation to a document locally and remotely.

 The `eventHandler` block will be called when local or remote changes are made to the document
 referenced by the `findByID` call that precedes the call to `observe`.

 The returned `DITLiveQuery` object must be kept in scope for as long as you want the provided
 `eventHandler` to be called when an update occurs.

 @param eventHandler A block that will be called every time there is a transaction committed to the
 store that involves a modification to the document with the relevant ID in the collection that
 `observe` was called on.

 @return A `DITLiveQuery` object that must be kept in scope for as long as you want to keep
 receiving updates.
 */
- (DITLiveQuery *)observe:(void (^)(DITDocument *_Nullable,
                                    DITSingleDocumentLiveQueryEvent *))eventHandler;

/**
 Enables you to listen for changes that occur in relation to a document locally and remotely.

 The `eventHandler` block will be called when local or remote changes are made to the document
 referenced by the `findByID` call that precedes the call to `observe`.

 The returned `DITLiveQuery` object must be kept in scope for as long as you want the provided
 `eventHandler` to be called when an update occurs.

 @param dispatchQueue The dispatch queue that will be used to deliver live query updates. Defaults
 to the main queue.
 @param eventHandler A block that will be called every time there is a transaction committed to the
 store that involves a modification to the document with the relevant ID in the collection that
 `observe` was called on.

 @return A `DITLiveQuery` object that must be kept in scope for as long as you want to keep
 receiving updates.
 */
- (DITLiveQuery *)observeWithDeliveryQueue:(dispatch_queue_t)dispatchQueue
                              eventHandler:
                                  (void (^)(DITDocument *_Nullable,
                                            DITSingleDocumentLiveQueryEvent *))eventHandler;

/**
 Enables you to listen for changes that occur in relation to a document locally and remotely, and to
 signal when you are ready for the live query to deliver the next event.

 This won't subscribe to receive changes made remotely by others and so it will only fire updates
 when a local change is made. If you want to receive remotely performed updates as well then use
 `observe` or also call `subscribe` separately, using another `findByID` call that references the
 same document ID.

 The returned `DITLiveQuery` object must be kept in scope for as long as you want the provided
 `eventHandler` to be called when an update occurs.

 @param eventHandler A block that will be called every time there is a transaction committed to the
 store that involves a modification to the document with the relevant ID in the collection that
 `observeWithNextSignalAndDeliveryQueue` was called on.

 @return A `DITLiveQuery` object that must be kept in scope for as long as you want to keep
 receiving updates.
 */
- (DITLiveQuery *)observeWithNextSignal:(void (^)(DITDocument *_Nullable,
                                                  DITSingleDocumentLiveQueryEvent *,
                                                  DittoSignalNextBlock))eventHandler;

/**
 Enables you to listen for changes that occur in relation to a document locally and remotely, and to
 signal when you are ready for the live query to deliver the next event.

 This won't subscribe to receive changes made remotely by others and so it will only fire updates
 when a local change is made. If you want to receive remotely performed updates as well then use
 `observe` or also call `subscribe` separately, using another `findByID` call that references the
 same document ID.

 The returned `DITLiveQuery` object must be kept in scope for as long as you want the provided
 `eventHandler` to be called when an update occurs.

 @param dispatchQueue The dispatch queue that will be used to deliver live query updates. Defaults
 to the main queue.
 @param eventHandler A block that will be called every time there is a transaction committed to the
 store that involves a modification to the document with the relevant ID in the collection that
 `observeWithNextSignalAndDeliveryQueue` was called on.

 @return A `DITLiveQuery` object that must be kept in scope for as long as you want to keep
 receiving updates.
 */
- (DITLiveQuery *)observeWithNextSignalAndDeliveryQueue:(dispatch_queue_t)dispatchQueue
                                           eventHandler:
                                       (void (^)(DITDocument *_Nullable,
                                                 DITSingleDocumentLiveQueryEvent *,
                                                 DittoSignalNextBlock))eventHandler;

/**
 Enables you to listen for changes that occur in relation to a document locally.

 This won't subscribe to receive changes made remotely by others and so it will only fire updates
 when a local change is made. If you want to receive remotely performed updates as well then use
 `observe` or also call `subscribe` separately, using another `findByID` call that references the
 same document ID.

 The returned `DITLiveQuery` object must be kept in scope for as long as you want the provided
 `eventHandler` to be called when an update occurs.

 @param eventHandler A block that will be called every time there is a transaction committed to the
 store that involves a modification to the document with the relevant ID in the collection that
 `observeLocal` was called on.

 @return A `DITLiveQuery` object that must be kept in scope for as long as you want to keep
 receiving updates.
 */
- (DITLiveQuery *)observeLocal:(void (^)(DITDocument *_Nullable,
                                         DITSingleDocumentLiveQueryEvent *))eventHandler;

/**
 Enables you to listen for changes that occur in relation to a document locally.

 This won't subscribe to receive changes made remotely by others and so it will only fire updates
 when a local change is made. If you want to receive remotely performed updates as well then use
 `observe` or also call `subscribe` separately, using another `findByID` call that references the
 same document ID.

 The returned `DITLiveQuery` object must be kept in scope for as long as you want the provided
 `eventHandler` to be called when an update occurs.

 @param dispatchQueue The dispatch queue that will be used to deliver live query updates. Defaults
 to the main queue.
 @param eventHandler A block that will be called every time there is a transaction committed to the
 store that involves a modification to the document with the relevant ID in the collection that
 `observeLocal` was called on.

 @return A `DITLiveQuery` object that must be kept in scope for as long as you want to keep
 receiving updates.
 */
- (DITLiveQuery *)observeLocalWithDeliveryQueue:(dispatch_queue_t)dispatchQueue
                                   eventHandler:
                                       (void (^)(DITDocument *_Nullable,
                                                 DITSingleDocumentLiveQueryEvent *))eventHandler;

/**
 Enables you to listen for changes that occur in relation to a document locally and to signal when you are
 ready for the live query to deliver the next event.

 This won't subscribe to receive changes made remotely by others and so it will only fire updates
 when a local change is made. If you want to receive remotely performed updates as well then use
 `observe` or also call `subscribe` separately, using another `findByID` call that references the
 same document ID.

 The returned `DITLiveQuery` object must be kept in scope for as long as you want the provided
 `eventHandler` to be called when an update occurs.

 @param eventHandler A block that will be called every time there is a transaction committed to the
 store that involves a modification to the document with the relevant ID in the collection that
 `observeLocalWithNextSignal` was called on.

 @return A `DITLiveQuery` object that must be kept in scope for as long as you want to keep
 receiving updates.
 */
- (DITLiveQuery *)observeLocalWithNextSignal:(dispatch_queue_t)dispatchQueue
                                eventHandler:
                                       (void (^)(DITDocument *_Nullable,
                                                 DITSingleDocumentLiveQueryEvent *,
                                                 DittoSignalNextBlock))eventHandler;

/**
 Enables you to listen for changes that occur in relation to a document locally and to signal when you are
 ready for the live query to deliver the next event.

 This won't subscribe to receive changes made remotely by others and so it will only fire updates
 when a local change is made. If you want to receive remotely performed updates as well then use
 `observe` or also call `subscribe` separately, using another `findByID` call that references the
 same document ID.

 The returned `DITLiveQuery` object must be kept in scope for as long as you want the provided
 `eventHandler` to be called when an update occurs.

 @param dispatchQueue The dispatch queue that will be used to deliver live query updates. Defaults
 to the main queue.
 @param eventHandler A block that will be called every time there is a transaction committed to the
 store that involves a modification to the document with the relevant ID in the collection that
 `observeLocalWithNextSignalAndDeliveryQueue` was called on.

 @return A `DITLiveQuery` object that must be kept in scope for as long as you want to keep
 receiving updates.
 */
- (DITLiveQuery *)observeLocalWithNextSignalAndDeliveryQueue:(dispatch_queue_t)dispatchQueue
                                                eventHandler:
                                       (void (^)(DITDocument *_Nullable,
                                                 DITSingleDocumentLiveQueryEvent *,
                                                 DittoSignalNextBlock))eventHandler;

@end

NS_ASSUME_NONNULL_END
