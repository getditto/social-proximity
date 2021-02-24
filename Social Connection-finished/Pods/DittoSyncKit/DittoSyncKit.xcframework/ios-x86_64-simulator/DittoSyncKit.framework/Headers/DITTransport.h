//
//  DittoTransport.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 22/01/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#import <Foundation/Foundation.h>

@class DITTransportBluetooth;
@class DITTransportWiFi;
@class DITTransportAWDL;
@class DITTransportTCPServer;
@class DITTransportWiFiFixedPort;
@class DITTransportWebServer;

/**
 The types of transport that can be used by DittoSyncKit to communicate with other devices.
*/
typedef NS_ENUM(NSUInteger, DITTransportType) {
    DITTransportTypeBluetooth = 1 << 0,
    DITTransportTypeWiFi = 1 << 1,
    DITTransportTypeAWDL = 1 << 2,
    DITTransportTypeTCPServer = 1 << 3,
    DITTransportTypeWiFiFixedPort = 1 << 4,
    DITTransportTypeWebServer = 1 << 5,
};

NS_ASSUME_NONNULL_BEGIN

/**
 An abstract class that is used to represent any of the transports that Ditto can use.
 */
@interface DITTransport : NSObject

/**
 The type of the transport.
 */
@property (nonatomic, readonly) DITTransportType type;

/**
 Creates an instance of the Bluetooth transport identifier.

 @return An instance of the Bluetooth transport identifier.
 */
+ (DITTransportBluetooth *)Bluetooth;

/**
 Creates an instance of the WiFi transport identifier.

 @return An instance of the WiFi transport identifier.
*/
+ (DITTransportWiFi *)WiFi;

/**
 Creates an instance of the AWDL transport identifier.

 @return An instance of the AWDL transport identifier.
*/
+ (DITTransportAWDL *)AWDL;

/**
 Creates an instance of the TCPServer transport identifier, with the provided server address.

 @param serverAddress The host:port of the TCP server to connect to.

 @return An instance of the TCPServer transport identifier.
*/
+ (DITTransportTCPServer *)TCPServerWithAddress:(NSString *)serverAddress;

/**
 Creates an instance of the WiFiFixedPort transport identifier, with the provided listen port.

 @param listenPort The port number that this device should listen on.

 @return An instance of the WiFiFixedPort transport identifier.
*/
+ (DITTransportWiFiFixedPort *)WiFiFixedPort:(uint16_t)listenPort;

/**
 Creates an instance of the WebServer transport identifier, with the provided server URL.

 @param serverURL The base URL of the HTTP/WebSocket server to connect to. Example: ws://ditto.example.com/

 @return An instance of the WebServer transport identifier.
*/
+ (DITTransportWebServer *)WebServerWithAddress:(NSString *)serverURL;

@end

/**
 Used in `start` and `stop` calls on the `DITDittoSyncKit` object to start or stop using Bluetooth as a
 transport.
 */
@interface DITTransportBluetooth : DITTransport
@end

/**
 Used in `start` and `stop` calls on the `DITDittoSyncKit` object to start or stop using WiFi as a
 transport.
*/
@interface DITTransportWiFi : DITTransport
@end

/**
 Used in `start` and `stop` calls on the `DITDittoSyncKit` object to start or stop using AWDL as a
 transport.
*/
@interface DITTransportAWDL : DITTransport
@end

/**
 Used in `start` and `stop` calls on the `DITDittoSyncKit` object to start or stop using a TCP server as a
 transport.
*/
@interface DITTransportTCPServer : DITTransport

/**
 The address of the server to connect to.
*/
@property (nonatomic, readonly) NSString *serverAddress;

@end

/**
 Used in `start` and `stop` calls on the `DITDittoSyncKit` object to start or stop using WiFi as a
 transport with a fixed listening port.
*/
@interface DITTransportWiFiFixedPort : DITTransport

@property (nonatomic, readonly) uint16_t port;

@end

/**
 Used in `start` and `stop` calls on the `DITDittoKit` object to start or stop using a WebSocket server as a
 transport.
*/
@interface DITTransportWebServer : DITTransport

/**
 The URL of the server to connect to.
*/
@property (nonatomic, readonly) NSString *serverURL;

@end

NS_ASSUME_NONNULL_END
