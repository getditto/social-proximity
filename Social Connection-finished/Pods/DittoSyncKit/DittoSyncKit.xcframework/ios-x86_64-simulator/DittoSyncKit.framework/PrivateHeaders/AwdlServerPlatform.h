//
//  AwdlServerPlatform.h
//  DittoTransportsObjC
//
//  Created by Hamilton Chapman on 30/10/2019.
//  Copyright © 2019 Ditto. All rights reserved.
//

#import <Foundation/Foundation.h>
#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
#import <UIKit/UIKit.h>
#elif TARGET_OS_MAC
#import <AppKit/AppKit.h>
#endif

#import "TransportHandleWrapper.h"
#import "dittoffi.h"

@class AwdlServerPeer;

NS_ASSUME_NONNULL_BEGIN

@interface AwdlServerPlatform : NSObject <NSNetServiceBrowserDelegate, NSNetServiceDelegate>

@property(nonatomic, assign, readonly) void *dittoHandle;
@property(nonatomic, strong, nullable) TransportHandleWrapper *handleWrapper;
@property(nonatomic, strong, readonly) dispatch_queue_t peersQueue;
@property(nonatomic, strong, readonly) dispatch_queue_t startStopQueue;
@property(nonatomic, strong, nullable) NSNetService *advertisingService;
@property(nonatomic, assign) int64_t peerIDCounter;
@property(nonatomic, strong) NSMutableDictionary<NSNumber *, AwdlServerPeer *> *peers;
@property(nonatomic, strong) NSString *prefix;
@property(nonatomic, strong) NSString *announce;
@property(nonatomic, assign) OnlineState_t advertising;
@property(nonatomic, strong, readonly, nullable) NSString* serviceName;

+ (AwdlServerCallbacks_t)callbacks;

- (instancetype)initWithDittoHandle:(void *)dittoHandle;
- (void)netServiceDidPublish:(NSNetService *)sender;
- (void)netService:(NSNetService *)sender didNotPublish:(NSDictionary<NSString *, NSNumber *> *)errorDict;
- (void)netService:(NSNetService *)sender didAcceptConnectionWithInputStream:(NSInputStream *)inputStream outputStream:(NSOutputStream *)outputStream;
- (void)startAdvertising:(NSString *)announce hashedAppName:(NSString *)hashedAppName;
- (void)stopAdvertising;
- (void)dropPeer:(NSNumber *)peerID;
- (void)shutdown;

@end

NS_ASSUME_NONNULL_END
