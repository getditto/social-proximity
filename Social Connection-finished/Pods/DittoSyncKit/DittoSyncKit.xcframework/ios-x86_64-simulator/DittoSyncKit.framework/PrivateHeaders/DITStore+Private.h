//
//  DITStore+Private.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 31/01/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

@class DittoHandleWrapper;

NS_ASSUME_NONNULL_BEGIN

@interface DITStore ()
@property (nonatomic, readonly) DittoHandleWrapper *dittoHandleWrapper;
@property (nonatomic, readonly) uint32_t siteID;

- (instancetype)initWithDittoHandleWrapper:(DittoHandleWrapper *)dittoHandleWrapper
                                    siteID:(uint32_t)siteID;
@end

NS_ASSUME_NONNULL_END
