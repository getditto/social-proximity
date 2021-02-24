//
//  DITTransportCondition.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 22/01/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#ifndef DITTransportCondition_h
#define DITTransportCondition_h

#import <Foundation/Foundation.h>

// TODO: Come up with a way to synchronise this directly from safer_ffi constants?

/**
 The different conditions that a transport can be in at a point in time.
 */
typedef NS_ENUM(NSUInteger, DITTransportCondition) {
    DITTransportConditionUnknown = 0,
    DITTransportConditionOk = 1,
    DITTransportConditionGenericFailure = 2,
    DITTransportConditionAppInBackground = 3,
    DITTransportConditionMdnsFailure = 4,
    DITTransportConditionTcpListenFailure = 5,
    DITTransportConditionNoBleCentralPermission = 6,
    DITTransportConditionNoBlePeripheralPermission = 7,
    DITTransportConditionCannotEstablishConnection = 8,
    DITTransportConditionBleDisabled = 9,
    DITTransportConditionNoBleHardware = 10,
    DITTransportConditionWifiDisabled = 11,
    DITTransportConditionTemporarilyUnavailable = 12,
};

/**
 The subsystem which is reporting a condition change.
 */
typedef NS_ENUM(NSUInteger, DITConditionSource) {
    DITConditionSourceBluetooth = 0,
    DITConditionSourceTcp = 1,
    DITConditionSourceAwdl = 2,
    DITConditionSourceMdns = 3,
};

#endif
