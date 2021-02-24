//
//  DITTransportDiagnostics.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 06/02/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#import <Foundation/Foundation.h>

@class DITTransportSnapshot;

NS_ASSUME_NONNULL_BEGIN

/**
 Provides a view into the state of the transports being used by DittoSyncKit at a point in time.
 */
@interface DITTransportDiagnostics : NSObject

/**
 The transport snapshots that were accurate when the transport diagnostics were obtained.
 */
@property (nonatomic, readonly) NSArray<DITTransportSnapshot *> *transports;

@end

NS_ASSUME_NONNULL_END
