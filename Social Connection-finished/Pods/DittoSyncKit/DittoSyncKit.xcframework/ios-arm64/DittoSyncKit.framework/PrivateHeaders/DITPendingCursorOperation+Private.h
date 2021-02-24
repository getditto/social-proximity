//
//  DITPendingCursorOperation+Private.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 31/01/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#import "dittoffi.h"

@class DittoHandleWrapper;
@class DocumentHandleWrapper;
@class DITLiveQuery;
@class DITLiveQueryEvent;
@class DITLiveQueryMove;
@class DITSubscription;

NS_ASSUME_NONNULL_BEGIN

@interface DITPendingCursorOperation ()
@property (nonatomic, readonly) DittoHandleWrapper *dittoHandleWrapper;
@property (nonatomic, readonly) NSString *collectionName;
@property (nonatomic, readonly) NSString *query;
@property (nonatomic, readwrite) int limit;
@property (nonatomic, readwrite) uint offset;
// orderDefinitions will eventually be replaced with orderBy, but has been kept for now to
// facilitate incremental refactoring.
@property (nonatomic, readwrite, nullable) COrderDefinition_t *orderDefinitions;
@property (nonatomic, readwrite) uint orderDefinitionsCount;
@property (nonatomic, readwrite, nullable) COrderByParam_t *orderBy;
@property (nonatomic, readwrite) uint orderByCount;
@property (nonatomic, readwrite, nullable) NSError *error;

- (instancetype)initWithQuery:(NSString *)query
               collectionName:(NSString *)collectionName
           dittoHandleWrapper:(DittoHandleWrapper *)dittoHandleWrapper;

// MARK: Observe (internal for Swift)

- (DITLiveQuery *)observeWithDeliveryQueue:(dispatch_queue_t)dispatchQueue
          eventHandlerUsingDocumentHandles:(void (^)(BOOL,
                                                     NSArray<DocumentHandleWrapper *> *,
                                                     NSArray<DocumentHandleWrapper *> *,
                                                     NSArray<NSNumber *> *,
                                                     NSArray<NSNumber *> *,
                                                     NSArray<NSNumber *> *,
                                                     NSArray<DITLiveQueryMove *> *))eventHandler;

- (DITLiveQuery *)observeLocalWithDeliveryQueue:(dispatch_queue_t)dispatchQueue
               eventHandlerUsingDocumentHandles:
                   (void (^)(BOOL,
                             NSArray<DocumentHandleWrapper *> *,
                             NSArray<DocumentHandleWrapper *> *,
                             NSArray<NSNumber *> *,
                             NSArray<NSNumber *> *,
                             NSArray<NSNumber *> *,
                             NSArray<DITLiveQueryMove *> *))eventHandler;

- (DITLiveQuery *)observeWithNextSignalAndDeliveryQueue:(dispatch_queue_t)dispatchQueue
                       eventHandlerUsingDocumentHandles:(void (^)(BOOL,
                                                     NSArray<DocumentHandleWrapper *> *,
                                                     NSArray<DocumentHandleWrapper *> *,
                                                     NSArray<NSNumber *> *,
                                                     NSArray<NSNumber *> *,
                                                     NSArray<NSNumber *> *,
                                                     NSArray<DITLiveQueryMove *> *, void(^_Nullable)(void)))eventHandler NS_SWIFT_NAME(observeWithNextSignal(deliveryQueue:eventHandlerUsingDocumentHandles:));

- (DITLiveQuery *)observeLocalWithNextSignalAndDeliveryQueue:(dispatch_queue_t)dispatchQueue
                            eventHandlerUsingDocumentHandles:
                   (void (^)(BOOL,
                             NSArray<DocumentHandleWrapper *> *,
                             NSArray<DocumentHandleWrapper *> *,
                             NSArray<NSNumber *> *,
                             NSArray<NSNumber *> *,
                             NSArray<NSNumber *> *,
                             NSArray<DITLiveQueryMove *> *, void(^_Nullable)(void)))eventHandler NS_SWIFT_NAME(observeLocalWithNextSignal(deliveryQueue:eventHandlerUsingDocumentHandles:));

- (DITLiveQuery *)observeWithSubscription:(nullable DITSubscription *)subscription
                            deliveryQueue:(dispatch_queue_t)deliveryQueue
                             availability:(LiveQueryAvailability_t)availability
         eventHandlerUsingDocumentHandles:
                (void (^)(BOOL,
                          NSArray<DocumentHandleWrapper *> *,
                          NSArray<DocumentHandleWrapper *> *,
                          NSArray<NSNumber *> *,
                          NSArray<NSNumber *> *,
                          NSArray<NSNumber *> *,
                          NSArray<DITLiveQueryMove *> *, void(^_Nullable)(void)))eventHandler;

// MARK: Other internal

- (NSArray<DocumentHandleWrapper *> *)execReturningDocumentHandles;

@end

NS_ASSUME_NONNULL_END
