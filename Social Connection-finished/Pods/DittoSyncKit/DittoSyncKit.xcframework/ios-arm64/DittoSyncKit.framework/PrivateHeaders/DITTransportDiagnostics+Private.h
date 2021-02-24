//
//  DITTransportDiagnostics+Private.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 06/02/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

@class DITTransportSnapshot;

NS_ASSUME_NONNULL_BEGIN

@interface DITTransportDiagnostics ()
- (instancetype)initWithSnapshots:(NSArray<DITTransportSnapshot *> *)snapshots;
@end

NS_ASSUME_NONNULL_END
