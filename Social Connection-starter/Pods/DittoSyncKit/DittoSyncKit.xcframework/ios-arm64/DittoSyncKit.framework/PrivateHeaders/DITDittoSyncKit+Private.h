//
//  DITDittoSyncKit+Private.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 31/01/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

@class DittoHandleWrapper;
@class PresenceManager;

@class TransportHandleWrapper;
@class AwdlClientPlatform;
@class AwdlServerPlatform;
@class BluetoothPlatform;
@class MdnsPlatform;
@class DITStatus;

NS_ASSUME_NONNULL_BEGIN

@interface DITDittoSyncKit ()
@property (nonatomic, readonly) DittoHandleWrapper *dittoHandleWrapper;
@property (nonatomic, readwrite) BOOL activated;
@property (nonatomic, readonly) DITStore *privateStore;
@property (nonatomic, readonly) PresenceManager *presence;
@property (nonatomic) BOOL transportConditionCallbackRegistered;

@property (nonatomic, nullable) MdnsPlatform *mdnsPlatform;
@property (nonatomic, nullable) BluetoothPlatform *bluetoothPlatform;
@property (nonatomic, nullable) AwdlClientPlatform *awdlClientPlatform;
@property (nonatomic, nullable) AwdlServerPlatform *awdlServerPlatform;
@property (nonatomic, nullable)
    NSMutableDictionary<NSString *, TransportHandleWrapper *> *staticTcpClients;
@property (nonatomic, nullable)
    NSMutableDictionary<NSString *, TransportHandleWrapper *> *staticWebClients;

@property (nonatomic) DITStatus *status;

+ (NSURL *)defaultDittoDirectory:(NSFileManager *)fileManager;
- (void)initSdkVersion;

@end

NS_ASSUME_NONNULL_END
