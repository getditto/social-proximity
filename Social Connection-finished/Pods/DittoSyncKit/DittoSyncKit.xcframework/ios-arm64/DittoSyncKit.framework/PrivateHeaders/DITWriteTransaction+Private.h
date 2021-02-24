//
//  DITWriteTransaction+Private.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 03/02/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#import "dittoffi.h"

@class DittoHandleWrapper;
@class DITWriteTransactionResult;

NS_ASSUME_NONNULL_BEGIN

@interface DITWriteTransaction ()
@property (nonatomic, readonly) DittoHandleWrapper *dittoHandleWrapper;
@property (nonatomic, readonly) uint32_t siteID;
@property (nonatomic, readonly) CWriteTransaction_t *writeTxn;
@property (nonatomic, readonly) NSMutableArray<DITWriteTransactionResult *> *results;

- (instancetype)initWithDittoHandleWrapper:(DittoHandleWrapper *)dittoHandleWrapper
                                    siteID:(uint32_t)siteID
                                  writeTxn:(CWriteTransaction_t *)writeTxn;
@end

NS_ASSUME_NONNULL_END
