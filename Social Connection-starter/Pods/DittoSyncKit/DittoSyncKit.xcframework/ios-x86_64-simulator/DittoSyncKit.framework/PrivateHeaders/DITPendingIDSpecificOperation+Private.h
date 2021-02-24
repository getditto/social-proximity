//
//  DITPendingIDSpecificOperation+Private.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 31/01/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#import "dittoffi.h"

@class DittoHandleWrapper;
@class DocumentHandleWrapper;
@class DITDocument;
@class DITLiveQuery;
@class DITSingleDocumentLiveQueryEvent;
@class DITSubscription;

NS_ASSUME_NONNULL_BEGIN

@interface DITPendingIDSpecificOperation ()
@property (nonatomic, readonly) DittoHandleWrapper *dittoHandleWrapper;
@property (nonatomic, readonly) NSString *documentID;
@property (nonatomic, readonly) NSString *collectionName;
@property (nonatomic, readonly) NSString *query;

- (instancetype)initWithDocumentID:(NSString *)documentID
                    collectionName:(NSString *)collectionName
                dittoHandleWrapper:(DittoHandleWrapper *)dittoHandleWrapper;

// MARK: Observe (internal for ObjC)

- (DITLiveQuery *)observeWithSubscription:(nullable DITSubscription *)subscription
                            deliveryQueue:(dispatch_queue_t)deliveryQueue
                             availability:(LiveQueryAvailability_t)availability
                             eventHandler:
                                 (void (^)(DITDocument *_Nullable,
                                           DITSingleDocumentLiveQueryEvent *, void(^_Nullable)(void)))eventHandler;

// MARK: Observe (internal for Swift)

- (DITLiveQuery *)observeWithDeliveryQueue:(dispatch_queue_t)dispatchQueue
           eventHandlerUsingDocumentHandle:(void (^)(BOOL,
                                                     DocumentHandleWrapper *_Nullable,
                                                     DocumentHandleWrapper *_Nullable))eventHandlerUsingDocumentHandle;

- (DITLiveQuery *)observeLocalWithDeliveryQueue:(dispatch_queue_t)dispatchQueue
                eventHandlerUsingDocumentHandle:
                    (void (^)(BOOL,
                              DocumentHandleWrapper *_Nullable,
                              DocumentHandleWrapper *_Nullable))eventHandlerUsingDocumentHandle;

- (DITLiveQuery *)observeWithNextSignalAndDeliveryQueue:(dispatch_queue_t)dispatchQueue
                        eventHandlerUsingDocumentHandle:
                       (void (^)(BOOL,
                                 DocumentHandleWrapper *_Nullable,
                                 DocumentHandleWrapper *_Nullable,
                                 void (^_Nullable)(void)))eventHandlerUsingDocumentHandle NS_SWIFT_NAME(observeWithNextSignal(deliveryQueue:eventHandlerUsingDocumentHandle:));

- (DITLiveQuery *)observeLocalWithNextSignalAndDeliveryQueue:(dispatch_queue_t)dispatchQueue
                eventHandlerUsingDocumentHandle:
                    (void (^)(BOOL,
                              DocumentHandleWrapper *_Nullable,
                              DocumentHandleWrapper *_Nullable,
                              void (^_Nullable)(void)))eventHandlerUsingDocumentHandle NS_SWIFT_NAME(observeLocalWithNextSignal(deliveryQueue:eventHandlerUsingDocumentHandle:));

- (DITLiveQuery *)observeWithSubscription:(nullable DITSubscription *)subscription
                                    deliveryQueue:(dispatch_queue_t)dispatchQueue
                                     availability:(LiveQueryAvailability_t)availability
                  eventHandlerUsingDocumentHandle:(void (^)(BOOL,
                                                            DocumentHandleWrapper *_Nullable,
                                                            DocumentHandleWrapper *_Nullable,
                                                            void (^_Nullable)(void)))eventHandlerUsingDocumentHandle;

// MARK: Other internal

- (void)updateUsingData:(NSData *)data;
- (nullable DocumentHandleWrapper *)execReturningDocumentHandle;
@end

NS_ASSUME_NONNULL_END
