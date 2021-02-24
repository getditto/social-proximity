//
//  DITDittoSyncKit.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 20/01/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <DittoSyncKit/DITLogLevel.h>

#import <DittoSyncKit/DITTransport.h>

@class DITIdentity;
@class DITPeersObserver;
@class DITRemotePeer;
@class DITStore;
@class DITTransportDiagnostics;

@protocol DITDittoSyncKitDelegate;

NS_ASSUME_NONNULL_BEGIN

/**
 The entrypoint to the DittoSyncKit SDK.

 For a `DITDittoSyncKit` instance to continue to connect to other devices it must be kept in scope.
 */
@interface DITDittoSyncKit : NSObject

/**
 Configure a custom identifier for the current device.

 When using `observePeers`, each remote peer is represented by a short UTF-8 "device name".

 By default this will be a truncated version of the device's hostname. It does not need to be unique
 among peers.

 Configure the device name before calling `start`. If it is too long it will be truncated.
 */
@property (class, nonatomic) NSString *deviceName;

/**
 Provides access to the SDK's store functionality.
 */
@property (atomic, readonly) DITStore *store;

/**
 The site ID that the instance of `DITDittoSyncKit` is using as part of its identity.
 */
@property (nonatomic, readonly) uint32_t siteID;

/**
 An optional delegate that will be called with SDK lifecycle information if defined.
 */
@property (nonatomic, weak) id<DITDittoSyncKitDelegate> delegate;

/**
 The dispatch queue that will be used to deliver delegate events. Defaults to the main queue.
 */
@property (nonatomic) dispatch_queue_t delegateEventQueue;

/**
 Initializes a new `DITDittoSyncKit`.

 This will initialize an instance of `DITDittoSyncKit` with the default configuration.
 */
- (instancetype)init;

/**
 Initializes a new `DITDittoSyncKit`.

 @param identity Provide the identity of the entity that is interacting with DittoSyncKit.
 */
- (instancetype)initWithIdentity:(DITIdentity *)identity;

/**
 Initializes a new `DITDittoSyncKit`.

 @param identity Provide the identity of the entity that is interacting with DittoSyncKit.
 @param directory The directory that will be used to persist DittoSyncKit data.
 */
- (instancetype)initWithIdentity:(DITIdentity *)identity
            persistenceDirectory:(nullable NSURL *)directory;

/**
 Starts all of the transports used by DittoSyncKit to connect to other devices.

 This has no effect for any transports that have already been started.
 */
- (void)start;

/**
 Start a set of transports used by DittoSyncKit to connect to other devices.

 This has no effect if a provided transport is already started.

 @param transports The set of transports to be started.
 */
- (void)start:(NSArray<DITTransport *> *)transports;

/**
 Stops all of the transports used by DittoSyncKit to connect to other devices.

 This has no effect for any transports that have already been stopped.
 */
- (void)stop;

/**
 Stop a set of transports being used by DittoSyncKit to connect to other devices.

 This has no effect for any transports that have already been started.

 @param transports The set of transports to be stopped.
 */
- (void)stop:(NSArray<DITTransport *> *)transports;

/**
 Starts an HTTP server that other devices will be able to connect to.

 @param address The address that the WebSocket server should run at. e.g. "0.0.0.0:4040"
 @param enableWebsocket Whether to accept Ditto sync connections on this port.
 @param staticPath An absolute path to a directory of static files that should be served. May be NULL.
 @param certPath If using TLS, an absolute path to a file containing this server's certificate. Otherwise NULL.
 @param keyPath If using TLS, an absolute path to a file containing this server's private key. Otherwise NULL.
 */
- (void)startHTTPServer:(NSString *)address
        enableWebsocket:(BOOL)enableWebsocket
             staticPath:(nullable NSString *)staticPath
            tlsCertPath:(nullable NSString *)certPath
             tlsKeyPath:(nullable NSString *)keyPath;

/**
 Activate a `DITDittoSyncKit` instance by setting an access license. You cannot meaningfully interact
 with a `DITDittoSyncKit` instance before you have activated it.

 @param license The license to activate the `DITDittoSyncKit` instance with.
 */
- (void)setAccessLicense:(NSString *)license;

/**
 Clears the cached site ID, if one had been cached.
 */
- (void)clearSiteID;

/**
 Request bulk status information about the transports.

 This is mostly intended for statistical or debugging purposes.

 @param error On input, a pointer to an error object. If an error occurs, this pointer
 is set to an actual error object containing the error information. You may specify nil for this
 parameter if you do not want the error information.

 @return An instance of `DITTransportDiagnostics` or `nil` if there was an error.
 */
- (nullable DITTransportDiagnostics *)transportDiagnostics:(NSError **)error;

/**
 Request information about Ditto peers in range of this device.

 This method returns an observer which should be held as long as updates are required. A newly
 registered observer will have a peers update delivered to it immediately. From then on it will be
 invoked repeatedly when Ditto devices come and go, or the active connections to them change.
 */
- (DITPeersObserver *)observePeers:(void (^)(NSArray<DITRemotePeer *> *))callback;

/**
 Returns a string identifying the version of the DittoSyncKit SDK.
 */
- (NSString *)sdkVersion;

@end

NS_ASSUME_NONNULL_END
