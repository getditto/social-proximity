//
//  DITCollection+Private.h
//  DittoSyncKit
//
//  Created by Hamilton Chapman on 31/01/2020.
//  Copyright © 2020 Ditto. All rights reserved.
//

#import <DittoSyncKit/DITCollection.h>

#import "dittoffi.h"

@class DittoHandleWrapper;

struct Ditto_WriteTransaction;

NS_ASSUME_NONNULL_BEGIN

@interface DITCollection ()
@property (nonatomic, readonly) DittoHandleWrapper *dittoHandleWrapper;
@property (nonatomic, readonly) uint32_t siteID;

- (instancetype)initWithDittoHandleWrapper:(DittoHandleWrapper *)dittoHandleWrapper
                                      name:(NSString *)name
                                    siteID:(uint32_t)siteID;
- (nullable NSString *)insert:(NSDictionary<NSString *, id> *)content
                       withID:(nullable NSString *)id
                    isDefault:(BOOL)isDefault
                     writeTxn:(CWriteTransaction_t *)writeTxn
                        error:(NSError *_Nullable __autoreleasing *)error;
- (nullable NSString *)insertCBORData:(NSData *)data
                               withID:(nullable NSString *)id
                            isDefault:(BOOL)isDefault
                             writeTxn:(CWriteTransaction_t *)writeTxn;
- (nullable NSString *)insertCBORData:(NSData *)data
                               withID:(nullable NSString *)id
                            isDefault:(BOOL)isDefault
                                error:(NSError *_Nullable __autoreleasing *)error;
@end

NS_ASSUME_NONNULL_END
