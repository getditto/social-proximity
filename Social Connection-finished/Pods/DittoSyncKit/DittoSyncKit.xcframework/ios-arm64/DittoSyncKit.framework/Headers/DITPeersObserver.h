//
//  DITPeersObserver.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 06/02/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A token returned by calling `observePeers` on a `DITDittoSyncKit` object.

 Retain this object to continue receiving callback updates.
 */
@interface DITPeersObserver : NSObject

- (void)stop;

@end

NS_ASSUME_NONNULL_END
