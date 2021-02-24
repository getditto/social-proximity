//
//  DITLiveQuery+Private.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 31/01/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#import "dittoffi.h"

@class DittoHandleWrapper;
@class DocumentHandleWrapper;
@class DITDocument;
@class DITLiveQueryEvent;
@class DITLiveQueryMove;
@class DITSubscription;

NS_ASSUME_NONNULL_BEGIN

@interface DITLiveQuery ()
@property (nonatomic, readonly) DittoHandleWrapper *dittoHandleWrapper;
@property (nonatomic, readonly) int limit;
@property (nonatomic, readonly) uint offset;
@property (nonatomic, readonly, nullable) DITSubscription *subscription;
@property (nonatomic, readonly) int64_t lqID;
@property (nonatomic, readonly) dispatch_queue_t deliveryDispatchQueue;
@property (nonatomic, readonly, nullable) void (^eventHandler)
    (NSArray<DITDocument *> *, DITLiveQueryEvent *, void (^_Nullable)(void));
@property (nonatomic, readonly, nullable) void (^documentHandleEventHandler)
    (BOOL,
     NSArray<DocumentHandleWrapper *> *,
     NSArray<DocumentHandleWrapper *> *,
     NSArray<NSNumber *> *,
     NSArray<NSNumber *> *,
     NSArray<NSNumber *> *,
     NSArray<DITLiveQueryMove *> *,
     void (^_Nullable)(void));
@property (nonatomic, readonly, nullable) void (^signalNextBlock)(void);

- (instancetype)initWithQuery:(NSString *)query
               collectionName:(NSString *)collectionName
             orderDefinitions:(COrderDefinition_t *)orderDefinitions
        orderDefinitionsCount:(uint)orderDefinitionsCount
                        limit:(int)limit
                       offset:(uint)offset
                 availability:(LiveQueryAvailability_t)availability
                 subscription:(nullable DITSubscription *)subscription
           dittoHandleWrapper:(DittoHandleWrapper *)dittoHandleWrapper
        deliveryDispatchQueue:(dispatch_queue_t)dispatchQueue
                 eventHandler:(void (^)(NSArray<DITDocument *> *, DITLiveQueryEvent *, void (^_Nullable)(void)))eventHandler;

- (instancetype)initWithQuery:(NSString *)query
                collectionName:(NSString *)collectionName
              orderDefinitions:(nullable COrderDefinition_t *)orderDefinitions
         orderDefinitionsCount:(uint)orderDefinitionsCount
                         limit:(int)limit
                        offset:(uint)offset
                  availability:(LiveQueryAvailability_t)availability
                  subscription:(nullable DITSubscription *)subscription
            dittoHandleWrapper:(DittoHandleWrapper *)dittoHandleWrapper
         deliveryDispatchQueue:(dispatch_queue_t)dispatchQueue
    documentHandleEventHandler:(void (^)(BOOL,
                                         NSArray<DocumentHandleWrapper *> *,
                                         NSArray<DocumentHandleWrapper *> *,
                                         NSArray<NSNumber *> *,
                                         NSArray<NSNumber *> *,
                                         NSArray<NSNumber *> *,
                                         NSArray<DITLiveQueryMove *> *, void (^_Nullable)(void)))documentHandleEventHandler;

- (instancetype)initWithQuery:(NSString *)query
                collectionName:(NSString *)collectionName
              orderDefinitions:(COrderDefinition_t *)orderDefinitions
         orderDefinitionsCount:(uint)orderDefinitionsCount
                         limit:(int)limit
                        offset:(uint)offset
                  availability:(LiveQueryAvailability_t)availability
                  subscription:(nullable DITSubscription *)subscription
            dittoHandleWrapper:(DittoHandleWrapper *)dittoHandleWrapper
         deliveryDispatchQueue:(dispatch_queue_t)dispatchQueue
                 eventHandler:(void (^_Nullable)(NSArray<DITDocument *> *, DITLiveQueryEvent *, void (^_Nullable)(void)))eventHandler
    documentHandleEventHandler:(void (^_Nullable)(BOOL,
                                                 NSArray<DocumentHandleWrapper *> *,
                                                 NSArray<DocumentHandleWrapper *> *,
                                                 NSArray<NSNumber *> *,
                                                 NSArray<NSNumber *> *,
                                                 NSArray<NSNumber *> *,
                                                               NSArray<DITLiveQueryMove *> *, void (^_Nullable)(void)))documentHandleEventHandler;

+ (NSArray<DITDocument *> *)
    documentsFrom:(Vec_CDocument_ptr_t)documents_vec;
+ (NSArray<NSNumber *> *)indexesFrom:(slice_boxed_size_t) idxs_boxed;
+ (NSArray<DocumentHandleWrapper *> *)
   documentHandlesFrom:(Vec_CDocument_ptr_t)documents_vec;
@end

NS_ASSUME_NONNULL_END
