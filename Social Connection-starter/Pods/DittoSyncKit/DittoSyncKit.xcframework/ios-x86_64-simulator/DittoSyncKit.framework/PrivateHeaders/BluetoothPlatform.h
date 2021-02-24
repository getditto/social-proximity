//
//  BluetoothPlatform.h
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
#import <CoreBluetooth/CoreBluetooth.h>

#import "TransportHandleWrapper.h"
#import "dittoffi.h"

@class PeerCache;

NS_ASSUME_NONNULL_BEGIN

// REFACTORING NOTE: In future this class should be split into two platforms registered independently, the same as
// AWDL Client and AWDL Server. This split has already been done at the transport level. They are completely
// different classes with different connection patterns and it will be much more maintainable if they're not both
// in the same file.

/// Implements iOS-specific Bluetooth functionality. It is assumed there is only one instance.
@interface BluetoothPlatform : NSObject <CBCentralManagerDelegate, CBPeripheralDelegate, CBPeripheralManagerDelegate>

@property(nonatomic, assign, readonly) void *dittoHandle;
@property(nonatomic, strong, nullable) TransportHandleWrapper *clientHandleWrapper;
@property(nonatomic, strong, nullable) TransportHandleWrapper *serverHandleWrapper;

// Central Manager lasts full duration from startScanning to stopScanning
// The delegate messages about updated state - "powered on" vs disabled/no permission/etc. are reliable
@property(nonatomic, strong, nullable) CBCentralManager *centralManager;
// Same, but between startAdvertising and stopAdvertising
@property(nonatomic, strong, nullable) CBPeripheralManager *peripheralManager;

// Synchronised dicts of CBCentrals/CBPeripherals so we can get them when Rust needs them
@property(nonatomic, strong, readonly) PeerCache *peerCache;

// The platform is responsible for trying to go online and stay online,
// even if there are outages due to bluetooth being turned off or other issues.
// These variables track whether we are currently "trying" to be online
@property(nonatomic, assign, readonly) bool scanning;
@property(nonatomic, assign, readonly) bool advertising;

// The announce string that we will advertise
// This will later be changed so that it can be changed "during" an advertising session
@property(nonatomic, strong) NSData *advertisingAnnounce;

// The announce string that we provide when connecting to a peer to say who we are
// (We know who they are from the advertisement, but they know nothing about us!)
// The Chooser on the remote peer will use the announce to decide whether to talk to us.
// This is probably the same as advertisingAnnounce, though not strictly required.
@property(nonatomic, strong) NSData *scanningAnnounce;

// Backing data for the "hack" described above
// When you are a central, each peripheral has its own delegate/queue
// When you are a peripheral, the queue for notifications is shared between all connected centrals
@property(nonatomic, strong) NSMutableDictionary<NSUUID *, NSNumber *> *peripheralIsReadyToSend;
@property(nonatomic, assign) double centralsReadyToSend;

// Cache whether or not we are currently in the foreground
// We have to be able to answer this question frequently so be efficient
@property(nonatomic, assign) BOOL inForeground;

@property(nonatomic, assign, readonly) uint32_t NOT_ACCEPTED_NO_DELAY; // failure result for a write command (to Rust)

// These UUIDs are just random, which is okay so long as we stay out of the registered range.
// These should be pushed down from Rust. Sending a tree of services/characteristics and their
// desired properties over raw FFI is a major hassle so we didn't bother and instead hardcoded
// them in both iOS and Android.
// Once we have DittoMPC we should make an effort to pack this information into the payload C
// struct for the "start scanning" and "start advertising" messages.
@property(nonatomic, strong, readonly) CBUUID *CHAR_UUID_WRITE; // Central writes to this to tell the peripheral mesh data
@property(nonatomic, strong, readonly) CBUUID *CHAR_UUID_CONTROL_WRITE; // Central writes to this to send control messages to the peripheral
@property(nonatomic, strong, readonly) CBUUID *CHAR_UUID_READ; // Central subscribes to notifications on this, and the peripheral posts mesh data
@property(nonatomic, strong, readonly) CBUUID *CHAR_UUID_CONTROL_READ; // Central subscribes to notifications on this, and the peripheral posts control messages
@property(nonatomic, strong, readonly) CBUUID *CHAR_UUID_ANNOUNCE; // Central writes to this after connecting to inform peripheral what its announce string is
@property(nonatomic, strong, nullable) CBUUID *SERVICE_UUID;

// A reference to our characteristics when we are acting as a peripheral
@property(nonatomic, strong, readonly) CBMutableCharacteristic *readChar;
@property(nonatomic, strong, readonly) CBMutableCharacteristic *controlReadChar;
@property(nonatomic, strong, readonly) CBMutableCharacteristic *writeChar;
@property(nonatomic, strong, readonly) CBMutableCharacteristic *controlWriteChar;
@property(nonatomic, strong, readonly) CBMutableCharacteristic *announceChar;

// If a peripheral UUID is in this map a connection attempt is in progress which started at "Date"
@property(nonatomic, strong) NSMutableDictionary<NSUUID *, NSDate *> *connectWatchdogs;

@property(nonatomic, strong, readonly) dispatch_queue_t serialQueue;

+ (BleServerCallbacks_t)serverCallbacks;
+ (BleClientCallbacks_t)clientCallbacks;

- (instancetype)initWithDittoHandle:(void *)dittoHandle;
- (void)peripheralManagerIsReadyToUpdateSubscribers:(CBPeripheralManager *)peripheral;
- (void)centralManagerDidUpdateState:(CBCentralManager *)centralManager;
- (void)peripheralManagerDidUpdateState:(CBPeripheralManager *)peripheralManager;
- (void)peripheralManagerDidStartAdvertising:(CBPeripheralManager *)peripheral error:(NSError * _Nullable)error;
- (void)centralManager:(CBCentralManager *)central didDiscoverPeripheral:(CBPeripheral *)peripheral advertisementData:(NSDictionary<NSString *, id> *)advertisementData RSSI:(NSNumber *)RSSI;
- (void)peripheralManager:(CBPeripheralManager *)peripheral didAddService:(CBService *)service error:(NSError * _Nullable)error;
- (void)centralManager:(CBCentralManager *)central didConnectPeripheral:(CBPeripheral *)peripheral;
- (void)centralManager:(CBCentralManager *)central didFailToConnectPeripheral:(CBPeripheral *)peripheral error:(NSError * _Nullable)error;
- (void)peripheral:(CBPeripheral *)peripheral didDiscoverServices:(NSError * _Nullable)error;
- (void)peripheral:(CBPeripheral *)peripheral didDiscoverCharacteristicsForService:(CBService *)service error:(NSError * _Nullable)error;
- (void)peripheral:(CBPeripheral *)peripheral didWriteValueForCharacteristic:(CBCharacteristic *)characteristic error:(NSError * _Nullable)error;
- (void)peripheral:(CBPeripheral *)peripheral didUpdateNotificationStateForCharacteristic:(CBCharacteristic *)characteristic error:(NSError * _Nullable)error;
- (void)centralManager:(CBCentralManager *)central didDisconnectPeripheral:(CBPeripheral *)peripheral error:(NSError * _Nullable)error;
- (void)peripheralManager:(CBPeripheralManager *)peripheral didReceiveReadRequest:(CBATTRequest *)request;
- (void)peripheralManager:(CBPeripheralManager *)peripheral didReceiveWriteRequests:(NSArray<CBATTRequest *> *)requests;
- (void)peripheral:(CBPeripheral *)peripheral didUpdateValueForCharacteristic:(CBCharacteristic *)characteristic error:(NSError * _Nullable)error;
- (void)peripheral:(CBPeripheral *)peripheral didModifyServices:(NSArray<CBService *> *)invalidatedServices;
- (void)peripheralManager:(CBPeripheralManager *)peripheral central:(CBCentral *)central didSubscribeToCharacteristic:(CBCharacteristic *)characteristic;
- (void)peripheralManager:(CBPeripheralManager *)peripheral central:(CBCentral *)central didUnsubscribeFromCharacteristic:(CBCharacteristic *)characteristic;
- (void)peripheralIsReadyToSendWriteWithoutResponse:(CBPeripheral *)peripheral;
- (void)shutdown;

@end

NS_ASSUME_NONNULL_END
