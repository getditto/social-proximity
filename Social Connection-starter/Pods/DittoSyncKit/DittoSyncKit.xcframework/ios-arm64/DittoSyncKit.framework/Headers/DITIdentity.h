//
//  DITIdentity.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 20/01/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The identity types you can use with DittoSyncKit.

 A development identity should be used while in development when you want to control either or both
 of the app name and the site ID of the peer.

 A production identity should be used when in production. This accepts a certificate bundle, which
 includes identity information as a base 64 encoded string.
 */
typedef NS_ENUM(NSUInteger, DITIdentityType) {
    DittoDevelopmentIdentity = 0,
    DittoSharedKeyIdentity,
    DittoProductionIdentity,
};

/**
 Used to identify a given peer in your network. In practice a peer may be a user, a device, or it
 might be some other entity in your system.

 You can get up and running quickly by using a development identity and then change to using a
 production identity when you are preparing to deploying DittoSyncKit to production.
 */
@interface DITIdentity : NSObject

/**
 The type of the identity.
 */
@property (nonatomic, readonly) enum DITIdentityType type;

// Development identity properties

/**
 The app name.

 Use this to ensure that connections between devices are only established if they share the same app
 name.

 Note that this is only set if the identity is a development identity.
 */
@property (nonatomic, readonly) NSString *appName;

/**
 The site ID.

 Use this to identity different users or devices. Site IDs are persisted between sessions if using a
 development identity.

 Site IDs should be unique and not reused by different users or devices.

 Note that this is only set if the identity is a development identity.
 */
@property (nonatomic, readonly) uint32_t siteID;

// Production identity properties

/**
 A base64 encoded DER representation of a private key, which is shared between devices for a single app.
 
  Note that this is only set if the identity is a shared key identity.
 */
@property (nonatomic, readonly, nullable) NSString *sharedKey;

/**
 A base64 encoded string representation of a certificate bundle.

 Note that this is only set if the identity is a production identity.
 */
@property (nonatomic, readonly, nullable) NSString *certificateConfig;

// Development identity inits

/**
 Creates a development identity with the default app name and a random site ID.

 @return The default development identity.
 */
- (instancetype)init;

/**
 Creates a development identity with the provided app name and provided site ID.

 @return A development identity using either the provided app name or the default one, and the
 provided site ID.
 */
- (instancetype)initWithAppName:(nullable NSString *)appName siteID:(uint32_t)siteID;

/**
 Creates a shared key identity with the provided app name, site ID and private key.

 @return A shared key identity
 */
- (instancetype)initWithAppName:(NSString *)appName sharedKey:(NSString *)sharedKey siteID:(uint32_t)siteID;

/**
 Creates a development identity with the provided site ID and the default app name.

 @return A development identity using the default app name and the provided site ID.
 */
- (instancetype)initWithSiteID:(uint32_t)siteID;

/**
 Creates a development identity with the provided app name and a random site ID.

 @return A development identity using the provided app name and a random site ID.
 */
- (instancetype)initWithAppName:(NSString *)appName;

// Production identity inits

/**
 Creates a production identity using the provided certificate config.

 @return A production identity using the provided certificate config.
 */
- (instancetype)initWithCertificateConfig:(NSString *)certificateConfig;

@end

NS_ASSUME_NONNULL_END
