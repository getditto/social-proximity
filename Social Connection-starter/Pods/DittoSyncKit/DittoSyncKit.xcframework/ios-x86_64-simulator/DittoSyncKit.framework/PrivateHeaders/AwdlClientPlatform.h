//
//  AwdlClientPlatform.h
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

/*
 This is the platform implementation for peer-to-peer Wifi, or AWDL.
 We use the platform APIs: NetService and NetServiceBrowser to
 initiate the discovery and connection. This is the same high-level
 API from the platform that is used with mDNS as well. We have a
 duplicate implementation because the underlying socket from AWDL
 uses a private socket option called SO_RECV_ANYIF and is defined
 in sys/socket.h on Darwin as 0x1104 (but unavailable in iOS).
 Instead, the only way to get access to the socket is from high-
 level APIs, specifically getInputStream(_:outputStream:) from
 NetService or NWBrowser and NWConnection in the Network Framework,
 (available >=iOS 12).

 We confirmed with Apple DTS that it is ok to run two NetService
 instances:

 "Nothing sticks out to me here as being an issue besides the
 technical overhead of managing the two sets of services and
 browsers."
 */
@class AwdlClientPeer;

NS_ASSUME_NONNULL_BEGIN

@interface AwdlClientPlatform : NSObject <NSNetServiceBrowserDelegate, NSNetServiceDelegate>

@property(nonatomic, assign, readonly) void *dittoHandle;
@property(nonatomic, strong, nullable) TransportHandleWrapper *handleWrapper;
@property(nonatomic, strong, readonly) dispatch_queue_t peersQueue;
@property(nonatomic, strong, nullable) NSNetServiceBrowser *browser;
@property(nonatomic, strong) NSMutableDictionary<NSString *, AwdlClientPeer *> *peers;
@property(nonatomic, strong) NSString *prefix;
@property(nonatomic, strong) NSString *announce;
@property(nonatomic, assign) OnlineState_t searching;

// For ClientPlatformProtocol
@property (nonatomic, assign) bool isWifiEnabled;
@property (nonatomic, strong, nullable) NSTimer *wifiCheckTimer;

+ (AwdlClientCallbacks_t)callbacks;

- (instancetype)initWithDittoHandle:(void *)dittoHandle;
- (void)netServiceBrowser:(NSNetServiceBrowser *)browser didNotSearch:(NSDictionary<NSString *, NSNumber *> *)errorDict;
- (void)netServiceBrowser:(NSNetServiceBrowser *)browser didFindService:(NSNetService *)service moreComing:(BOOL)moreComing;
- (void)netServiceBrowser:(NSNetServiceBrowser *)browser didRemoveService:(NSNetService *)service moreComing:(BOOL)moreComing;
- (void)startSearching:(NSString *)announce hashedAppName:(NSString *)hashedAppName;
- (void)stopSearching;
- (void)shutdown;

@end

NS_ASSUME_NONNULL_END
