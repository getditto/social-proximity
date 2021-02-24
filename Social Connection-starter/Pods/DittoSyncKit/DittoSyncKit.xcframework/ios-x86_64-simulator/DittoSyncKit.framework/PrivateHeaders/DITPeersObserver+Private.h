//
//  DITPeersObserver+Private.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 07/02/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

@class PresenceManager;
@class DITRemotePeer;

NS_ASSUME_NONNULL_BEGIN

@interface DITPeersObserver ()
@property (nonatomic, readonly) PresenceManager *manager;
@property (nonatomic) void (^callback)(NSArray<DITRemotePeer *> *);
@property (nonatomic, readonly) dispatch_queue_t queue;

- (instancetype)initWithPresenceManager:(PresenceManager *)manager
                               callback:(void (^)(NSArray<DITRemotePeer *> *))callback
                                  queue:(dispatch_queue_t)queue;
- (void)invoke:(NSArray<DITRemotePeer *> *)data;
@end

NS_ASSUME_NONNULL_END
