//
//  DITTransportSnapshot+Private.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 06/02/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

NS_ASSUME_NONNULL_BEGIN

@interface DITTransportSnapshot ()
- (instancetype)initWithConnectionType:(NSString *)connection_type
                            connecting:(NSArray<NSNumber *> *)connecting
                             connected:(NSArray<NSNumber *> *)connected
                         disconnecting:(NSArray<NSNumber *> *)disconnecting
                          disconnected:(NSArray<NSNumber *> *)disconnected;
@end

NS_ASSUME_NONNULL_END
